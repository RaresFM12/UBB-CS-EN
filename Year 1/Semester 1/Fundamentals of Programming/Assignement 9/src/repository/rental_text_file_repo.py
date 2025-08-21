import datetime

from src.domain.rental import Rental
from src.repository.rental_memory_repo import RentalMemoryRepository


class RentalTextFileRepo(RentalMemoryRepository):
    def __init__(self, file_name = "rental.txt"):
        super().__init__()
        self.__most_rented_books = {}
        self.__most_active_clients = {}
        self.__rental_availability = {}
        self.__file_name = file_name
        self._load_file()

    def erase_data(self):
        super().erase_data()
        open(self.__file_name, "w").close()

    def _load_file(self):
        lines_from_text_file = []
        try:
            test_file_input = open(self.__file_name, "rt")
            lines_from_text_file = test_file_input.readlines()
            test_file_input.close()
        except IOError:
            pass

        for line in lines_from_text_file:
            current_line = line.split(", ")

            array1 = current_line[3].split("-")
            s = array1[2].split(" ")
            datetime_str1 = datetime.datetime(int(array1[0]), int(array1[1]), int(s[0]))

            array2 = current_line[4].split("-")
            s = array2[2].split(" ")
            datetime_str2 = datetime.datetime(int(array2[0]), int(array2[1]), int(s[0]))

            new_book = Rental(int(current_line[0].strip()), int(current_line[1].strip()), int(current_line[2].strip()),
                              datetime_str1, datetime_str2)

            super().add(new_book)
            if new_book.book_id in self.__most_rented_books.keys():
                self.__most_rented_books[new_book.book_id] += 1
            else:
                self.__most_rented_books[new_book.book_id] = 1

            if new_book.client_id in self.__most_active_clients.keys():
                self.__most_active_clients[new_book.client_id] += 1
            else:
                self.__most_active_clients[new_book.client_id] = 1

    def get_most_rented_books_keys(self):
        return list(self.__most_rented_books.keys())

    def get_most_rented_books_values(self):
        return list(self.__most_rented_books.values())

    def get_most_active_clients_keys(self):
        return list(self.__most_active_clients.keys())

    def get_most_active_clients_values(self):
        return list(self.__most_active_clients.values())

    def _save_file(self):
        text_output_file = open(self.__file_name, "wt")
        for book in super().display_rented_books():
            book_string = (str(book.id) + ", " + str(book.book_id) + ", " + str(book.client_id) + ", " +
                           str(book.rented_date) + ", " + str(book.returned_date) + "\n")
            text_output_file.write(book_string)

        text_output_file.close()

    def rent_a_book(self, object):
        """
        This function adss a book to the rented list
        :param object: the book
        :return: None
        """
        super().rent_a_book(object)
        if object.book_id in self.__most_rented_books.keys():
            self.__most_rented_books[object.book_id] += 1
        else:
            self.__most_rented_books[object.book_id] = 1

        if object.client_id in self.__most_active_clients.keys():
            self.__most_active_clients[object.client_id] += 1
        else:
            self.__most_active_clients[object.client_id] = 1

        self._save_file()

    def delete_rental_availability(self, id):
        super().delete_rental_availability(id)

    def return_avalability(self, id):
        if id in self.__rental_availability.keys():
            return self.__rental_availability[id]
        return False

    def set_availability_true(self, id):
        self.__rental_availability[id] = True

    def set_availability_false(self, id):
        self.__rental_availability[id] = False

    def display_rented_books(self):
        return super().display_rented_books()

    def remove_rental(self, id):
        super().remove_rental(id)

    def get_all_ids(self):
        return super().get_all_ids()