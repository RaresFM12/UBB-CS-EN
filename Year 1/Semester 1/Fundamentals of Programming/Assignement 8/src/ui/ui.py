from matplotlib.pyplot import title

from src.repository.repository_exception import RepositoryException
from src.services.book_service import BookService
from src.services.client_service import ClientService
from src.services.rental_service import RentalService


class Ui:
    def __init__(self, param):
        try:
            if(param[0] == "memory"):
                self.__book_service = BookService(param[0], "")
                self.__client_service = ClientService(param[0], "")
                self.__rental_service = RentalService(param[0], "")
            else:
                self.__book_service = BookService(param[0], param[1])
                self.__client_service = ClientService(param[0], param[2])
                self.__rental_service = RentalService(param[0], param[3])

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
                            print(f"The book with the id {book.book_id} was returned on {book.returned_date}")

                except RepositoryException as re:
                    print(re)

            elif cmd == "0":
                print("Goodbye!")
                return
            else:
                print("Bad command!")
