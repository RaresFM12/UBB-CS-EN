import os
import random

from faker import Faker

from src.domain.book import Book
from src.repository.book_binary_repo import BookBinaryRepo
from src.repository.book_memory_repo import BookMemoryRepository
from src.repository.book_text_file_repo import BookTextFileRepo
from src.repository.repository_exception import RepositoryException
from src.services.undo_redo_service import CascadedOperation, FunctionCall, Operation, UndoRedoError


class BookService:
    def __init__(self, type, undo_service, rental_service, book_repo):
        self.__undo_service = undo_service
        self.__rental_service = rental_service
        self.__book_repo = book_repo

        if type == "memory":
            self.generate_random_books()

        elif type == "text_file":
            if os.path.getsize("book.txt") == 0:
                self.generate_random_books()

        elif type == "binary_file":
            if os.path.getsize("book.bin") == 0:
                self.generate_random_books()

    def clear_books(self):
        self.__book_repo.erase_data()

    def add_book(self, id, title, author):
        """
        This function adds a new book
        :param id: the id
        :param title: the title
        :param author: the author
        :return: None
        """
        try:
            id = int(id)
        except:
            raise RepositoryException("The id must be an integer!")

        if id <= 0:
            raise RepositoryException("The id must be a positive integer!")

        new_book = Book(id, title, author)
        self.__book_repo.add_book(new_book)

        fc_undo = FunctionCall(self.__book_repo.remove_book, id)
        fc_redo = FunctionCall(self.__book_repo.add_book, new_book)
        op = Operation(fc_undo, fc_redo)
        self.__undo_service.record(op)

    def remove_book(self, id):
        """
        This function removes a client
        :param id: the id
        :return: None
        """
        try:
            id = int(id)
        except:
            raise RepositoryException("The id must be an integer!")

        if id <= 0:
            raise RepositoryException("The id must be a positive integer!")

        book = self.__book_repo.get_by_id(id)
        if book is None:
            raise UndoRedoError("There is no such book!")

        self.__book_repo.remove_book(id)
        fc_undo = FunctionCall(self.__book_repo.add_book, book)
        fc_redo = FunctionCall(self.__book_repo.remove_book, id)
        operations = [Operation(fc_undo, fc_redo)]

        # Remove all rentals for this book
        rentals = self.__rental_service.filter_rentals(None, book)
        for rent in rentals:
            year = rent.rented_date.year
            month = rent.rented_date.month
            day = rent.rented_date.day
            self.__rental_service.delete_rental(rent.id)
            self.__rental_service.delete_rental_availability(rent.id)
            self.__rental_service.set_availability_true(rent.id)

            fc_undo = FunctionCall(self.__rental_service.rent_a_book, rent.id, rent.book_id, rent.client_id,
                                   year, month, day)

            fc_redo = FunctionCall(self.__rental_service.delete_rental, rent.id)
            operations.append(Operation(fc_undo, fc_redo))

        self.__undo_service.record(CascadedOperation(*operations))


    def update_book(self, id, title, author):
        """
        This function updates a book
        :param id: the id
        :param title: the title
        :param author: the author
        :return: None
        """
        try:
            id = int(id)
        except:
            raise RepositoryException("The id must be an integer!")

        if id <= 0:
            raise RepositoryException("The id must be a positive integer!")

        old_book = self.__book_repo.get_by_id(id)
        new_book = Book(id, title, author)
        self.__book_repo.update_book(new_book)

        fc_undo = FunctionCall(self.__book_repo.update_book, old_book)
        fc_redo = FunctionCall(self.__book_repo.update_book, new_book)
        op = Operation(fc_undo, fc_redo)
        self.__undo_service.record(op)

    def display_books(self):
        """
        This function returns all the books
        :return: the list of books
        """
        return self.__book_repo.display_all_books()

    def search_book_by_id(self, id):
        try:
            id = int(id)
        except:
            raise RepositoryException("The id must be an integer!")

        if id <= 0:
            raise RepositoryException("The id must be a positive integer!")

        return self.__book_repo.search_book_by_id(id)

    def search_book_by_title(self, title):
        return self.__book_repo.search_book_by_title(title)

    def search_book_by_author(self, author):
        return self.__book_repo.search_book_by_author(author)

    def get_all_ids(self):
        return self.__book_repo.get_all_ids()

    def generate_random_books(self):
        fake = Faker()
        cnt = 1
        for i in range(20):
            t = random.randrange(1, 5)
            id = cnt
            title = fake.sentence(t)
            title = title.replace(".", "")

            author = fake.name()
            self.add_book(id, title, author)
            cnt += 1




