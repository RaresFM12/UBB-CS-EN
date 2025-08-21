import pickle

from src.repository.book_memory_repo import BookMemoryRepository


class BookBinaryRepo(BookMemoryRepository):
    def __init__(self, file_name = "book.bin"):
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
            super().add_book(new_book)

        bin_input_file.close()

    def _save_file(self):
        bin_out_file = open(self.__file_name, "wb")
        pickle.dump(super().display_all_books(), bin_out_file)
        bin_out_file.close()

    def add_book(self, object):
        """
        This function adds a book
        :param object: a book
        :return: none
        """
        super().add_book(object)
        self._save_file()

    def remove_book(self, id):
        """
        This function removes a book
        :param id: the id
        :return: None
        """
        super().remove_book(id)
        self._save_file()

    def update_book(self, object):
        """
        This function updates a book
        :param object: the book
        :return: None
        """
        super().update_book(object)
        self._save_file()

    def display_all_books(self):
        """
        This function returns all the books
        :return: the list of books
        """
        return super().display_all_books()

    def search_book_by_id(self, id):
        return super().search_by_id(id)

    def search_book_by_title(self, title):
        return super().search_book_by_title(title)

    def search_book_by_author(self, author):
        return super().search_book_by_author(author)

    def get_all_ids(self):
        return super().get_all_ids()