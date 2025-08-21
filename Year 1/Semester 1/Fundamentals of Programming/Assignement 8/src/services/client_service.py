import os
from random import random

from faker import Faker

from src.domain.client import Client
from src.repository.client_binary_file import ClientBinaryRepo
from src.repository.client_memory_repo import ClientMemoryRepository
from src.repository.client_text_file_repo import ClientTextFileRepo
from src.repository.repository_exception import RepositoryException


class ClientService:
    def __init__(self, repo, file_name):
        if repo == "memory":
            self.__repo = ClientMemoryRepository()
            self.generate_random_client()
        elif repo == "text_file":
            self.__repo = ClientTextFileRepo(file_name)
            if os.path.getsize(file_name) == 0:
                self.generate_random_client()

        elif repo == "binary_file":
            self.__repo = ClientBinaryRepo(file_name)
            if os.path.getsize(file_name) == 0:
                self.generate_random_client()

        else:
            raise RepositoryException("You didn't choose the right repository!")

    def clear_clients(self):
        self.__repo.erase_data()

    def add_client(self, id, name):
        """
        This function adds a client
        :param id: the id
        :param name: the name
        :return: None
        """
        try:
            id = int(id)
        except:
            raise RepositoryException("The id must be an integer!")

        if id <= 0:
            raise RepositoryException("The id must be a positive integer!")

        new_client = Client(id, name)
        self.__repo.add_client(new_client)

    def remove_client(self, id):
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

        self.__repo.remove_client(id)

    def update_client(self, id, name):
        """
        This function updates a client
        :param id: the id
        :param name: the name
        :return: None
        """
        try:
            id = int(id)
        except:
            raise RepositoryException("The id must be an integer!")

        if id <= 0:
            raise RepositoryException("The id must be a positive integer!")

        new_client = Client(id, name)
        self.__repo.update_client(new_client)

    def display_clients(self):
        """
        This function returns all the clients
        :return: the list of clients
        """
        return self.__repo.display_all_clients()

    def search_client_by_id(self, id):
        try:
            id = int(id)
        except:
            raise RepositoryException("The id must be an integer!")

        if id <= 0:
            raise RepositoryException("The id must be a positive integer!")

        return self.__repo.search_client_by_id(id)

    def search_client_by_name(self, name):
        return self.__repo.search_client_by_name(name)

    def get_all_ids(self):
        return self.__repo.get_all_ids()

    def generate_random_client(self):
        fake = Faker()
        cnt = 1
        for i in range(20):
            id = cnt
            name = fake.name()
            self.add_client(id, name)
            cnt += 1