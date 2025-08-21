from src.domain.book import Book
from src.repository.book_memory_repo import BookMemoryRepository


class BookTextFileRepo(BookMemoryRepository):
    def __init__(self, file_name = "book.txt"):
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
            new_book = Book(int(current_line[0].strip()), current_line[1].strip(), current_line[2].strip())
            super().add_book(new_book)

    def _save_file(self):
        text_output_file = open(self.__file_name, "wt")
        for book in super().display_all_books():
            book_string = str(book.id) + ", " + book.title + ", " + book.author + "\n"
            text_output_file.write(book_string)

        text_output_file.close()

    def add_book(self, object):
        """
        This function adds a book to the list
        :param object: the book
        :return: None
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