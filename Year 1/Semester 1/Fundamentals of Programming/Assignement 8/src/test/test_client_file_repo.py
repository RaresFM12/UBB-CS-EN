import os
import unittest

from src.domain.client import Client
from src.repository.client_text_file_repo import ClientTextFileRepo


class TestClientFileRepo(unittest.TestCase):
    def setUp(self):
        self.test_file = "test_client.txt"
        with open(self.test_file, "w") as f:
            f.write("1, Travis Beasley\n2, Elizabeth Newman MD\n")
        self.repo = ClientTextFileRepo(self.test_file)

    def tearDown(self):
        if os.path.exists(self.test_file):
            os.remove(self.test_file)

    def test_add_book(self):
        self.repo.add_client(Client(3, "Cristi"))
        clients = self.repo.get_all()
        self.assertEqual(len(clients), 3)

    def test_remove_book(self):
        self.repo.remove_client(2)
        clients = self.repo.get_all()
        self.assertEqual(len(clients), 1)

    def test_update_book(self):
        self.repo.update_client(Client(2, "Cristi"))
        clients = self.repo.get_all()
        self.assertEqual(clients[1].name, "Cristi")

if __name__ == "__main__":
    unittest.main()