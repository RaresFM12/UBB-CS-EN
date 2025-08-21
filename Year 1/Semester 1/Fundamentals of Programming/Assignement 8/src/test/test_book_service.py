import os
import unittest

from src.domain.book import Book
from src.repository.book_memory_repo import BookMemoryRepository
from src.repository.book_text_file_repo import BookTextFileRepo
from src.services.book_service import BookService


class TestBookService(unittest.TestCase):
    def setUp(self):
        self.service = BookService("memory", "")

    def tearDown(self):
        pass

    def test_add_book(self):
        self.service.clear_books()
        self.service.add_book("1", "fftfyt", "Cristi")
        books = self.service.display_books()
        self.assertEqual(len(books), 1)

    def test_remove_book(self):
        self.service.clear_books()
        self.service.add_book("2", "fftfyt", "Cristi")
        self.service.add_book("3", "fftfyt", "Ovidiu")
        self.service.remove_book(2)
        books = self.service.display_books()
        self.assertEqual(len(books), 1)

    def test_update_book(self):
        self.service.clear_books()
        self.service.add_book("4", "fftfyt", "Cristi")
        self.service.add_book("5", "fftfyt", "Ovidiu")
        self.service.update_book(5, "fftfyt", "Rares")
        books = self.service.display_books()
        self.assertEqual(books[1].author, "Rares")

if __name__ == "__main__":
    unittest.main()