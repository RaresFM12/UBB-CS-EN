import pickle

from src.repository.rental_memory_repo import RentalMemoryRepository


class RentalBinaryRepo(RentalMemoryRepository):
    def __init__(self, file_name = "rental.bin"):
        super().__init__()
        self.__file_name = file_name
        self._load_file()

    def erase_data(self):
        super().erase_data()
        open(self.__file_name, "w").close()

    def _load_file(self):
        try:
            bin_input_file = open(self.__file_name, 'rb')
            books_from_bin_file = pickle.load(bin_input_file)
        except EOFError:
            return

        for new_book in books_from_bin_file:
            super().rent_a_book(new_book)

        bin_input_file.close()

    def _save_file(self):
        bin_out_file = open(self.__file_name, "wb")
        pickle.dump(super().display_rented_books(), bin_out_file)
        bin_out_file.close()

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