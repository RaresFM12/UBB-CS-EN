import datetime
import os

from faker import Faker

from src.domain.rental import Rental
from src.repository.rental_binary_repo import RentalBinaryRepo
from src.repository.rental_memory_repo import RentalMemoryRepository
from src.repository.rental_text_file_repo import RentalTextFileRepo
from src.repository.repository_exception import RepositoryException


class RentalService:
    def __init__(self, repo, file_name):
        if repo == "memory":
            self.__repo = RentalMemoryRepository()
            self.generate_random_rent()
        elif repo == "text_file":
            self.__repo = RentalTextFileRepo(file_name)
            if os.path.getsize(file_name) == 0:
                self.generate_random_rent()

        elif repo == "binary_file":
            self.__repo = RentalBinaryRepo(file_name)
            if os.path.getsize(file_name) == 0:
                self.generate_random_rent()

        else:
            raise RepositoryException("You didn't choose the right repository!")

    def rent_a_book(self, id, book_id, client_id, year, month, day):
        """
        This function adds a new book to the rent list
        :param id: the id
        :param book_id: the book id
        :param client_id: the client id
        :param year: the year
        :param month: the month
        :param day: the day
        :return: None
        """
        try:
            id = int(id)
            book_id = int(book_id)
            client_id = int(client_id)
        except:
            raise RepositoryException("The id must be an integer!")

        if id <= 0 or book_id <= 0 or client_id <= 0:
            raise RepositoryException("The id must be a positive integer!")

        try:
            year = int(year)
            month = int(month)
            day = int(day)

        except:
            raise RepositoryException("This is not a valid date!")

        if year <= 0 or (month <= 0 or month >= 13) or (day <= 0 or day >= 31):
            raise RepositoryException("This is not a valid date!")

        try:
            rent_date = datetime.datetime(year, month, day)
            return_date = datetime.datetime(1, 1, 1)

        except:
            raise RepositoryException("This is not a valid date!")

        new_rent = Rental(id, book_id, client_id, rent_date, return_date)
        self.__repo.rent_a_book(new_rent)

    def return_a_book(self, id, year, month, day):
        try:
            id = int(id)
        except:
            raise RepositoryException("The id must be an integer!")

        if id <= 0:
            raise RepositoryException("The id must be a positive integer!")

        try:
            year = int(year)
            month = int(month)
            day = int(day)

        except:
            raise RepositoryException("This is not a valid date!")

        if year <= 0 or (month <= 0 or month >= 13) or (day <= 0 or day >= 31):
            raise RepositoryException("This is not a valid date!")

        try:
            return_date = datetime.datetime(year, month, day)

        except:
            raise RepositoryException("This is not a valid date!")

        self.__repo.add_return_date(id, return_date)
        self.__repo.return_a_book(id)


    def display_rented_books(self):
        return self.__repo.display_rented_books()

    def display_returned_books(self):
        return self.__repo.display_returned_books()

    def get_all_ids(self):
        return self.__repo.get_all_ids()

    def generate_random_rent(self):
        year = 2000
        month = 3
        day = 12
        cnt = 1
        for i in range(5):
            id = cnt
            book_id = cnt * 2
            client_id = cnt
            rented_date = datetime.datetime(year, month, day)
            self.rent_a_book(id, book_id, client_id, year, month, day)
            cnt += 1
            year += 1
            month += 1
            day += 1

