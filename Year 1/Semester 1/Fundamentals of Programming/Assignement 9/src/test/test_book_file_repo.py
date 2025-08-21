import os
import unittest

from src.domain.book import Book
from src.repository.book_text_file_repo import BookTextFileRepo


class TestBookFileRepo(unittest.TestCase):
    def setUp(self):
        self.test_file = "test_book.txt"
        with open(self.test_file, "w") as f:
            f.write("1, Tv, Daniel Russell\n2, Future, William Murphy\n")
        self.repo = BookTextFileRepo(self.test_file)

    def tearDown(self):
        if os.path.exists(self.test_file):
            os.remove(self.test_file)

    def test_add_book(self):
        self.repo.add_book(Book(3, "fftfyt", "Cristi"))
        books = self.repo.get_all()
        self.assertEqual(len(books), 3)

    def test_remove_book(self):
        self.repo.remove_book(2)
        books = self.repo.get_all()
        self.assertEqual(len(books), 1)

    def test_update_book(self):
        self.repo.update_book(Book(2, "fftfyt", "Cristi"))
        books = self.repo.get_all()
        self.assertEqual(books[1].author, "Cristi")

if __name__ == "__main__":
    unittest.main()