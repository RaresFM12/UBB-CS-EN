import os
import unittest

from src.domain.client import Client
from src.repository.client_text_file_repo import ClientTextFileRepo


class TestClientFileRepo(unittest.TestCase):
    def setUp(self):
        self.repo = ClientTextFileRepo()

    def tearDown(self):
        pass

    def test_add_book(self):
        self.repo.add_client(Client(1, "Cristi"))
        clients = self.repo.get_all()
        self.assertEqual(len(clients), 1)

    def test_remove_book(self):
        self.repo.add_client(Client(1, "Cristi"))
        self.repo.add_client(Client(2, "Rares"))
        self.repo.remove_client(2)
        clients = self.repo.get_all()
        self.assertEqual(len(clients), 1)

    def test_update_book(self):
        self.repo.add_client(Client(1, "Cristi"))
        self.repo.update_client(Client(1, "Alin"))
        clients = self.repo.get_all()
        self.assertEqual(clients[1].name, "Alin")

if __name__ == "__main__":
    unittest.main()