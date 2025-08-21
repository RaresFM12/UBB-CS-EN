from src.repository.repository import Repository
from src.repository.repository_exception import RepositoryException


class RentalMemoryRepository(Repository):
    def __init__(self):
        super().__init__()
        self.__rented_books_id = []
        self.__returned_books = []

    def rent_a_book(self, object):
        """
        This function adss a book to the rented list
        :param object: the book
        :return: None
        """
        ok = True
        for b in self.__rented_books_id:
            if object.book_id == b[0]:
                ok = False

        if ok == False:
            raise RepositoryException("This book is not available!")

        super().add(object)
        self.__rented_books_id.append([object.book_id, object.id])

    def return_a_book(self, id):
        if len(self.__rented_books_id) == 0:
            raise  RepositoryException("There are no more rented books!")

        ok = False
        for b in self.__rented_books_id:
            if id == b[0]:
                ok = True

        if ok == False:
            raise RepositoryException("This book was not rented!")

        rent_id = 0
        for i in range(len(self.__rented_books_id) - 1, -1, -1):
            if id == self.__rented_books_id[i][0]:
                rent_id = self.__rented_books_id[i][1]
                self.__rented_books_id.pop(i)

        super().remove(rent_id)

    def add_return_date(self, id, date):
        rented_books = super().get_all()
        for b in rented_books:
            if id == b.book_id:
                b.returned_date = date
                self.__returned_books.append(b)

    def display_rented_books(self):
        return super().get_all()

    def display_returned_books(self):
        return self.__returned_books

    def erase_data(self):
        super().delete_all()

    def get_all_ids(self):
        return super().get_all_ids()