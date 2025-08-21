import datetime

from src.domain.rental import Rental
from src.repository.rental_memory_repo import RentalMemoryRepository


class RentalTextFileRepo(RentalMemoryRepository):
    def __init__(self, file_name = "rental.txt"):
        super().__init__()
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

            super().rent_a_book(new_book)

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
        self._save_file()

    def return_a_book(self, id):
        super().return_a_book(id)
        self._save_file()

    def add_return_date(self, id, date):
        super().add_return_date(id, date)

    def display_rented_books(self):
        return super().display_rented_books()

    def display_returned_books(self):
        return super().display_returned_books()

    def get_all_ids(self):
        return super().get_all_ids()