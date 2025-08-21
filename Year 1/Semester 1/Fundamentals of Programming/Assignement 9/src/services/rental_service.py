import datetime
import os
import random

from faker import Faker

from src.domain.book import Book
from src.domain.rental import Rental
from src.repository.rental_binary_repo import RentalBinaryRepo
from src.repository.rental_memory_repo import RentalMemoryRepository
from src.repository.rental_text_file_repo import RentalTextFileRepo
from src.repository.repository_exception import RepositoryException
from src.repository.return_binary_repo import ReturnBinaryRepo
from src.repository.return_memory_repo import ReturnMemoryRepository
from src.repository.return_text_file import ReturnTextFileRepo
from src.services.undo_redo_service import FunctionCall, Operation


class RentalService:
    def __init__(self, type, undo_service, book_repo, client_repo, rental_repo, return_repo):
        self.__undo_service = undo_service
        self.__book_repo = book_repo
        self.__client_repo = client_repo
        self.__rental_repo = rental_repo
        self.__return_repo = return_repo

        if type == "memory":
            self.generate_random_rent()

        elif type == "text_file":
            if os.path.getsize("rental.txt") == 0:
                self.generate_random_rent()

        elif type == "binary_file":
            if os.path.getsize("rental.bin") == 0:
                self.generate_random_rent()

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

        if year <= 0 or (month <= 0 or month >= 13) or (day <= 0 or day >= 29):
            raise RepositoryException("This is not a valid date!")

        try:
            rent_date = datetime.datetime(year, month, day)
            return_date = datetime.datetime(1, 1, 1)

        except:
            raise RepositoryException("This is not a valid date!")

        new_rent = Rental(id, book_id, client_id, rent_date, return_date)
        self.__rental_repo.rent_a_book(new_rent)
        fc_undo = FunctionCall(self.__rental_repo.remove_rental, id)
        fc_redo = FunctionCall(self.__rental_repo.rent_a_book, new_rent)
        op = Operation(fc_undo, fc_redo)
        self.__undo_service.record(op)

        return new_rent


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

        if year <= 0 or (month <= 0 or month >= 13) or (day <= 0 or day >= 29):
            raise RepositoryException("This is not a valid date!")

        return_date = datetime.datetime(year, month, day)

        self.__return_repo.add_return_date(id, return_date)
        self.__rental_repo.set_availability_true(id)

        fc_undo = FunctionCall(self.__return_repo.remove_return, )
        fc_redo = FunctionCall(self.__return_repo.add_return_date, id, return_date)
        op = Operation(fc_undo, fc_redo)
        self.__undo_service.record(op)


    def display_rented_books(self):
        return self.__rental_repo.display_rented_books()

    def display_returned_books(self):
        return self.__return_repo.display_returned_books()

    def most_rented_books(self):
        k = self.__rental_repo.get_most_rented_books_keys()
        v = self.__rental_repo.get_most_rented_books_values()

        l = []
        for i in range(len(k)):
            l.append([k[i], v[i]])

        for i in range(len(l) - 1):
            for j in range(i + 1, len(l)):
                if l[i][1] < l[j][1]:
                    l[i], l[j] = l[j], l[i]

        return l

    def most_active_clients(self):
        k = self.__rental_repo.get_most_active_clients_keys()
        v = self.__rental_repo.get_most_active_clients_values()

        l = []
        for i in range(len(k)):
            er = random.randint(1, 2)
            l.append([k[i], 3 * v[i] + er])

        for i in range(len(l) - 1):
            for j in range(i + 1, len(l)):
                if l[i][1] < l[j][1]:
                    l[i], l[j] = l[j], l[i]

        return l

    def delete_rental(self, id):
        rental = self.__rental_repo.remove_rental(id)
        return rental

    def delete_rental_availability(self, id):
        self.__rental_repo.delete_rental_availability(id)

    def set_availability_true(self, id):
        self.__rental_repo.set_availability_true(id)

    def set_availability_false(self, id):
        self.__rental_repo.set_availability_false(id)

    def filter_rentals(self, client, book):
        result = []
        for rental in self.__rental_repo.display_rented_books():
            if client is not None and rental.client_id != client.id:
                continue
            if book is not None and rental.book_id != book.id:
                continue

            result.append(rental)
        return result

    def filter_returns(self, book):
        result = []
        for rental in self.__return_repo.display_returned_books():
            if book is not None and rental.book_id != book.id:
                continue

            result.append(rental)
        return result

    def generate_random_rent(self):
        cnt = 1
        for i in range(20):
            id = cnt
            book_id = random.randint(1, 20)
            client_id = random.randint(1, 20)
            year = random.randint(1950, 2025)
            month = random.randint(1, 12)
            day = random.randint(1, 28)
            self.rent_a_book(id, book_id, client_id, year, month, day)

            new_year = year
            new_month = month
            if day <= 26:
                new_day = day + 2
            else:
                new_day = day - 2

            self.return_a_book(book_id, new_year, new_month, new_day)
            cnt += 1

