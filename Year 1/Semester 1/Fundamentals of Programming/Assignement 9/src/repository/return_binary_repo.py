import pickle

from src.repository.rental_memory_repo import RentalMemoryRepository
from src.repository.return_memory_repo import ReturnMemoryRepository


class ReturnBinaryRepo(ReturnMemoryRepository):
    def __init__(self, file_name = "return.bin"):
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
            id = new_book[0]
            date = new_book[1]
            super().add_return_date(id, date)

        bin_input_file.close()

    def _save_file(self):
        bin_out_file = open(self.__file_name, "wb")
        pickle.dump(super().display_returned_books(), bin_out_file)
        bin_out_file.close()

    def add_return_date(self, id, date):
        super().add_return_date(id, date)
        self._save_file()

    def remove_return(self):
        super().remove_return()
        self._save_file()

    def display_returned_books(self):
        return super().display_returned_books()

    def get_all_ids(self):
        return super().get_all_ids()