from src.repository.repository import Repository
from src.repository.repository_exception import RepositoryException


class RentalMemoryRepository(Repository):
    def __init__(self):
        super().__init__()
        self.__rented_books_id = []
        self.__rental_availability = {}
        self.__most_rented_books = {}
        self.__most_active_clients = {}

    def rent_a_book(self, object):
        """
        This function adds a book to the rented list
        :param object: the book
        :return: None
        """
        #if object.book_id in self.__rental_availability.keys():
         #   if self.return_avalability(object.book_id) == False:
          #      raise RepositoryException("This book is not available!")

        super().add(object)
        self.__rented_books_id.append([object.book_id, object.id])
        self.__rental_availability[object.book_id] = False

        if object.book_id in self.__most_rented_books.keys():
            self.__most_rented_books[object.book_id] += 1
        else:
            self.__most_rented_books[object.book_id] = 1

        if object.client_id in self.__most_active_clients.keys():
            self.__most_active_clients[object.client_id] += 1
        else:
            self.__most_active_clients[object.client_id] = 1

    def delete_rental_availability(self, id):
        if id in self.__rental_availability.keys():
            del self.__rental_availability[id]

    def get_most_active_clients_keys(self):
        return list(self.__most_active_clients.keys())

    def get_most_active_clients_values(self):
        return list(self.__most_active_clients.values())

    def get_most_rented_books_keys(self):
        return list(self.__most_rented_books.keys())

    def get_most_rented_books_values(self):
        return list(self.__most_rented_books.values())

    def return_avalability(self, id):
        if id in self.__rental_availability.keys():
            return self.__rental_availability[id]
        return False

    def set_availability_true(self, id):
        self.__rental_availability[id] = True

    def set_availability_false(self, id):
        self.__rental_availability[id] = False

    def display_rented_books(self):
        return super().get_all()

    def erase_data(self):
        super().delete_all()

    def remove_rental(self, id):
        del self.__most_rented_books[id]
        return super().remove(id)

    def get_all_ids(self):
        return super().get_all_ids()
