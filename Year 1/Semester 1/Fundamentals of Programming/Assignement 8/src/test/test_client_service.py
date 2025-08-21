import os
import unittest

from src.domain.book import Book
from src.repository.book_memory_repo import BookMemoryRepository
from src.repository.book_text_file_repo import BookTextFileRepo
from src.services.book_service import BookService
from src.services.client_service import ClientService


class TestClientService(unittest.TestCase):
    def setUp(self):
        self.service = ClientService("memory", "")

    def tearDown(self):
        pass

    def test_add_book(self):
        self.service.clear_clients()
        self.service.add_client("1", "Cristi")
        clients = self.service.display_clients()
        self.assertEqual(len(clients), 1)

    def test_remove_book(self):
        self.service.clear_clients()
        self.service.add_client("2","Cristi")
        self.service.add_client("3","Ovidiu")
        self.service.remove_client(2)
        clients = self.service.display_clients()
        self.assertEqual(len(clients), 1)

    def test_update_book(self):
        self.service.clear_clients()
        self.service.add_client("4", "Cristi")
        self.service.add_client("5", "Ovidiu")
        self.service.update_client(5, "Rares")
        clients = self.service.display_clients()
        self.assertEqual(clients[1].name, "Rares")

if __name__ == "__main__":
    unittest.main()