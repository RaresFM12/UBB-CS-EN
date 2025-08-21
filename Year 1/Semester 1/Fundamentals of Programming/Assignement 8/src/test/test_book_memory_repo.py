import os
import unittest

from src.domain.book import Book
from src.repository.book_memory_repo import BookMemoryRepository
from src.repository.book_text_file_repo import BookTextFileRepo


class TestBookMemoryRepo(unittest.TestCase):
    def setUp(self):
        self.repo = BookMemoryRepository()

    def tearDown(self):
        pass

    def test_add_book(self):
        self.repo.add_book(Book(1, "fftfyt", "Cristi"))
        books = self.repo.get_all()
        self.assertEqual(len(books), 1)

    def test_remove_book(self):
        self.repo.add_book(Book(1, "fftfyt", "Cristi"))
        self.repo.add_book(Book(2, "fftfyt", "Cristi"))
        self.repo.remove_book(2)
        books = self.repo.get_all()
        self.assertEqual(len(books), 1)

    def test_update_book(self):
        self.repo.add_book(Book(1, "fftfyt", "Cristi"))
        self.repo.add_book(Book(2, "fftfyt", "Cristi"))
        self.repo.update_book(Book(2, "fftfyt", "Rares"))
        books = self.repo.get_all()
        self.assertEqual(books[1].author, "Rares")

if __name__ == "__main__":
    unittest.main()