from src.repository.repository import Repository
from src.repository.repository_exception import RepositoryException


class BookMemoryRepository(Repository):
    def __init__(self):
        super().__init__()

    def add_book(self, object):
        """
        This functions adds a book to the list
        :param object: the book
        :return: None
        """
        super().add(object)

    def remove_book(self, id):
        """
        This function removes a book
        :param id: the id
        :return: None
        """
        super().remove(id)

    def update_book(self, object):
        """
        This function updates a book
        :param object: the book
        :return: None
        """
        super().update(object)

    def display_all_books(self):
        """
        This function returns all the books
        :return: the list of books
        """
        return super().get_all()
    
    def get_by_id(self, id):
        return super().get_by_id(id)

    def search_book_by_id(self, id):
        return super().search_by_id(id)

    def search_book_by_title(self, title):
        title = title.lower()
        books = []
        objects = super().get_all()
        for obj in objects:
            if title in obj.title.lower():
                books.append(obj)

        if len(books) == 0:
            raise RepositoryException("There is no such book!")

        return books

    def search_book_by_author(self, author):
        author = author.lower()
        books = []
        objects = super().get_all()
        for obj in objects:
            if author in obj.author.lower():
                books.append(obj)

        if len(books) == 0:
            raise RepositoryException("There is no such book!")

        return books

    def get_all_ids(self):
        return super().get_all_ids()

    def erase_data(self):
        super().delete_all()

