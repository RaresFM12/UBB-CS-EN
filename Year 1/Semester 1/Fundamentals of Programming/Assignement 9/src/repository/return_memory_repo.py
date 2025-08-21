from src.repository.repository import Repository
from src.repository.repository_exception import RepositoryException


class ReturnMemoryRepository(Repository):
    def __init__(self):
        super().__init__()
        self.__returned_books = []

    def add_return_date(self, id, date):
        self.__returned_books.append([id, date])

    def remove_return(self):
        self.__returned_books.pop()

    def display_returned_books(self):
        return self.__returned_books

    def erase_data(self):
        super().delete_all()

    def get_all_ids(self):
        return super().get_all_ids()