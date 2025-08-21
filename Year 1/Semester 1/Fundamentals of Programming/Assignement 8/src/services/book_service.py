import os
import random

from faker import Faker

from src.domain.book import Book
from src.repository.book_binary_repo import BookBinaryRepo
from src.repository.book_memory_repo import BookMemoryRepository
from src.repository.book_text_file_repo import BookTextFileRepo
from src.repository.repository_exception import RepositoryException


class BookService:
    def __init__(self, repo, file_name):
        if repo == "memory":
            self.__repo = BookMemoryRepository()
            self.generate_random_books()

        elif repo == "text_file":
            self.__repo = BookTextFileRepo(file_name)
            if os.path.getsize(file_name) == 0:
                self.generate_random_books()

        elif repo == "binary_file":
            self.__repo = BookBinaryRepo(file_name)
            if os.path.getsize(file_name) == 0:
                self.generate_random_books()

        else:
            raise RepositoryException("You didn't choose the right repository!")

    def clear_books(self):
        self.__repo.erase_data()

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
        self.__repo.add_book(new_book)

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

        self.__repo.remove_book(id)

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

        new_book = Book(id, title, author)
        self.__repo.update_book(new_book)

    def display_books(self):
        """
        This function returns all the books
        :return: the list of books
        """
        return self.__repo.display_all_books()

    def search_book_by_id(self, id):
        try:
            id = int(id)
        except:
            raise RepositoryException("The id must be an integer!")

        if id <= 0:
            raise RepositoryException("The id must be a positive integer!")

        return self.__repo.search_book_by_id(id)

    def search_book_by_title(self, title):
        return self.__repo.search_book_by_title(title)

    def search_book_by_author(self, author):
        return self.__repo.search_book_by_author(author)

    def get_all_ids(self):
        return self.__repo.get_all_ids()

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




