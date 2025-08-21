from matplotlib.pyplot import title

from src.repository.book_binary_repo import BookBinaryRepo
from src.repository.book_memory_repo import BookMemoryRepository
from src.repository.book_text_file_repo import BookTextFileRepo
from src.repository.client_binary_file import ClientBinaryRepo
from src.repository.client_memory_repo import ClientMemoryRepository
from src.repository.client_text_file_repo import ClientTextFileRepo
from src.repository.rental_binary_repo import RentalBinaryRepo
from src.repository.rental_memory_repo import RentalMemoryRepository
from src.repository.rental_text_file_repo import RentalTextFileRepo
from src.repository.repository_exception import RepositoryException
from src.repository.return_binary_repo import ReturnBinaryRepo
from src.repository.return_memory_repo import ReturnMemoryRepository
from src.repository.return_text_file import ReturnTextFileRepo
from src.services.book_service import BookService
from src.services.client_service import ClientService
from src.services.rental_service import RentalService
from src.services.undo_redo_service import UndoService, UndoRedoError


class Ui:
    def __init__(self, param):
        self.__undo_service = UndoService()
        try:
            if param[0] == "memory":
                self.__book_repo = BookMemoryRepository()
                self.__client_repo = ClientMemoryRepository()
                self.__rental_repo = RentalMemoryRepository()
                self.__return_repo = ReturnMemoryRepository()

            elif param[0] == "text_file":
                self.__book_repo = BookTextFileRepo(param[1])
                self.__client_repo = ClientTextFileRepo(param[2])
                self.__rental_repo = RentalTextFileRepo(param[3])
                self.__return_repo = ReturnTextFileRepo("return.txt")

            elif param[0] == "binary_file":
                self.__book_repo = BookBinaryRepo(param[1])
                self.__client_repo = ClientBinaryRepo(param[2])
                self.__rental_repo = RentalBinaryRepo(param[3])
                self.__return_repo = ReturnBinaryRepo("return.bin")

            self.__rental_service = RentalService(param[0], self.__undo_service, self.__book_repo,
                                                  self.__client_repo, self.__rental_repo, self.__return_repo)

            self.__client_service = ClientService(param[0], self.__undo_service, self.__rental_service, self.__client_repo)
            self.__book_service = BookService(param[0], self.__undo_service, self.__rental_service, self.__book_repo)

        except RepositoryException as re:
            print(re)
            exit()

    def create_menu(self):
        while True:
            print("1) Add a book")
            print("2) Add a client")
            print("3) Remove a book")
            print("4) Remove a client")
            print("5) Update a book")
            print("6) Update a client")
            print("7) Display all the books")
            print("8) Display all the clients")
            print("9) Rent a book")
            print("10) Return a book")
            print("11) Search")
            print("12) Display the rented books")
            print("13) Display the returned books")
            print("14) Statistics")
            print("15) Undo")
            print("16) Redo")
            print("0) Exit")

            cmd = input("-> ")

            if cmd == "1":
                id = input("The id of the book: ")
                title = input("The title of the book: ")
                author = input("The author of the book: ")

                try:
                    self.__book_service.add_book(id, title, author)
                except RepositoryException as re:
                    print(re)

            elif cmd == "2":
                id = input("The id of the client: ")
                name = input("The name of the client: ")

                try:
                    self.__client_service.add_client(id, name)
                except RepositoryException as re:
                    print(re)

            elif cmd == "3":
                id = input("The id of the book: ")

                try:
                    self.__book_service.remove_book(id)
                except RepositoryException as re:
                    print(re)

            elif cmd == "4":
                id = input("The id of the client: ")

                try:
                    self.__client_service.remove_client(id)
                except RepositoryException as re:
                    print(re)

            elif cmd == "5":
                id = input("The id of the book you want to update: ")
                title = input("The new title of the book: ")
                author = input("The new author of the book: ")

                try:
                    self.__book_service.update_book(id, title, author)
                except RepositoryException as re:
                    print(re)

            elif cmd == "6":
                id = input("The id of the client you want to update: ")
                name = input("The new name of the client: ")

                try:
                    self.__client_service.update_client(id, name)
                except RepositoryException as re:
                    print(re)

            elif cmd == "7":
                try:
                    books = self.__book_service.display_books()
                    for book in books:
                        print(book)
                except RepositoryException as re:
                    print(re)

            elif cmd == "8":
                try:
                    clients = self.__client_service.display_clients()
                    for client in clients:
                        print(client)
                except RepositoryException as re:
                    print(re)

            elif cmd == "9":
                id = input("The id of the rental: ")
                book_id = input("The id of the book: ")
                client_id = input("The id of the client: ")
                date = input("The date when the book was rented(year/month/day): ").split('/')

                book_ids = self.__book_service.get_all_ids()
                client_ids = self.__client_service.get_all_ids()

                try:
                    book_id = int(book_id)
                    client_id = int(client_id)
                except:
                    print("The id must be an integer!")
                    continue

                if book_id <= 0 or client_id <= 0:
                    print("The id must be a positive integer!")
                    continue

                if book_id not in book_ids:
                    print("This book id doesn't exist!")
                elif client_id not in client_ids:
                    print("This client id doesn't exist!")
                else:
                    if len(date) != 3:
                        print("This is not a valid date!")
                    else:
                        try:
                            self.__rental_service.rent_a_book(id, book_id, client_id, date[0], date[1], date[2])

                        except RepositoryException as re:
                            print(re)

            elif cmd == "10":
                id = input("The id of the returned book: ")
                date = input("The date when the book was returned(year/month/day): ").split('/')

                book_ids = self.__book_service.get_all_ids()

                try:
                    id = int(id)
                except:
                    print("The id must be an integer!")
                    continue

                if id <= 0:
                    print("The id must be a positive integer!")
                    continue

                if id not in book_ids:
                    print("This book id doesn't exist!")
                else:
                    if len(date) != 3:
                        print("This is not a valid date!")
                    else:
                        try:
                            self.__rental_service.return_a_book(id, date[0], date[1], date[2])

                        except RepositoryException as re:
                            print(re)

            elif cmd == "11":
                while True:
                    print("a) Search for a book")
                    print("b) Search for a client")

                    cmd2 = input("-> ")

                    if cmd2 == "a":
                        while True:
                            print("1) Search a book by id: ")
                            print("2) Search a book by title: ")
                            print("3) Search a book by author: ")

                            cmd3 = input("-> ")

                            if cmd3 == "1":
                                id = input("The id will be: ")

                                try:
                                    books = self.__book_service.search_book_by_id(id)
                                    for b in books:
                                        print(b)

                                except RepositoryException as re:
                                    print(re)
                                break

                            elif cmd3 == "2":
                                title = input("The title will be: ")

                                try:
                                    books = self.__book_service.search_book_by_title(title)
                                    for b in books:
                                        print(b)

                                except RepositoryException as re:
                                    print(re)
                                break

                            elif cmd3 == "3":
                                author = input("The author will be: ")

                                try:
                                    books = self.__book_service.search_book_by_author(author)
                                    for b in books:
                                        print(b)

                                except RepositoryException as re:
                                    print(re)
                                break

                            else:
                                print("Bad command!")

                            break

                    elif cmd2 == "b":
                        while True:
                            print("1) Search a client by id: ")
                            print("2) Search a client by name: ")

                            cmd3 = input("-> ")

                            if cmd3 == "1":
                                id = input("The id will be: ")

                                try:
                                    clients = self.__client_service.search_client_by_id(id)
                                    for c in clients:
                                        print(c)

                                except RepositoryException as re:
                                    print(re)
                                break

                            elif cmd3 == "2":
                                name = input("The name will be: ")

                                try:
                                    clients = self.__client_service.search_client_by_name(name)
                                    for c in clients:
                                        print(c)

                                except RepositoryException as re:
                                    print(re)
                                break

                            else:
                                print("Bad command!")

                            break

                    else:
                        print("Bad command!")

                    break

            elif cmd == "12":
                try:
                    books = self.__rental_service.display_rented_books()
                    if len(books) != 0:
                        for book in books:
                            print(f"The rental with id {book.id}: The book with the id {book.book_id} was rented"
                                  f" by the client with id {book.client_id} on {book.rented_date}")

                except RepositoryException as re:
                    print(re)

            elif cmd == "13":
                try:
                    books = self.__rental_service.display_returned_books()
                    if len(books) != 0:
                        for book in books:
                            print(f"The book with the id {book[0]} was returned on {book[1]}")

                except RepositoryException as re:
                    print(re)

            elif cmd == "14":
                print("a) Most rented books")
                print("b) Most active clients")
                print("c) Most rented author")

                cmd4 = input("-> ")
                if cmd4 == "a":
                    books = self.__rental_service.most_rented_books()
                    all_books = self.__book_service.display_books()

                    for b in books:
                        for bk in all_books:
                            if b[0] == bk.id:
                                print(f"\"{bk.title}\" has the id {b[0]} and was rented {b[1]} times")

                elif cmd4 == "b":
                    clients = self.__rental_service.most_active_clients()
                    all_clients = self.__client_service.display_clients()

                    for c in clients:
                        for cl in all_clients:
                            if c[0] == cl.id:
                                print(f"{cl.name} has the id {c[0]} and was active for {c[1]} days")

                elif cmd4 == "c":
                    most_rented_author = {}
                    books = self.__rental_service.most_rented_books()
                    all_books = self.__book_service.display_books()

                    for bk in all_books:
                        most_rented_author[bk.author] = 0

                    for b in books:
                        for bk in all_books:
                            if b[0] == bk.id:
                                most_rented_author[bk.author] += b[1]

                    k = list(most_rented_author.keys())
                    v = list(most_rented_author.values())

                    l = []
                    for i in range(len(k)):
                        l.append([k[i], v[i]])

                    for i in range(len(l) - 1):
                        for j in range(i + 1, len(l)):
                            if l[i][1] < l[j][1]:
                                l[i], l[j] = l[j], l[i]

                    for i in l:
                        print(f"{i[0]} has {i[1]} number of rentals")

                else:
                    print("Bad command!")

            elif cmd == "15":
                try:
                    self.__undo_service.undo()
                    print("The LPO was undone!")
                except UndoRedoError as ex:
                    print(ex)

            elif cmd == "16":
                try:
                    self.__undo_service.redo()
                    print("The LPO was redone!")
                except UndoRedoError as ex:
                    print(ex)

            elif cmd == "0":
                print("Goodbye!")
                return
            else:
                print("Bad command!")
