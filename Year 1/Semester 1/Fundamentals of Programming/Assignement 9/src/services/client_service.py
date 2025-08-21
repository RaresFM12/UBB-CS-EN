import os
from random import random

from faker import Faker

from src.domain.client import Client
from src.repository.client_binary_file import ClientBinaryRepo
from src.repository.client_memory_repo import ClientMemoryRepository
from src.repository.client_text_file_repo import ClientTextFileRepo
from src.repository.repository_exception import RepositoryException
from src.services.undo_redo_service import FunctionCall, Operation, UndoRedoError, CascadedOperation


class ClientService:
    def __init__(self, type, undo_service, rental_service, client_repo):
        self.__undo_service = undo_service
        self.__rental_service = rental_service
        self.__client_repo = client_repo

        if type == "memory":
            self.generate_random_client()

        elif type == "text_file":
            if os.path.getsize("client.txt") == 0:
                self.generate_random_client()

        elif type == "binary_file":
            if os.path.getsize("client.bin") == 0:
                self.generate_random_client()

    def clear_clients(self):
        self.__client_repo.erase_data()

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
        self.__client_repo.add_client(new_client)

        fc_undo = FunctionCall(self.__client_repo.remove_client, id)
        fc_redo = FunctionCall(self.__client_repo.add_client, new_client)
        op = Operation(fc_undo, fc_redo)
        self.__undo_service.record(op)

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

        client = self.__client_repo.get_by_id(id)
        if client is None:
            raise UndoRedoError("There is no such book!")

        self.__client_repo.remove_client(id)
        fc_undo = FunctionCall(self.__client_repo.add_client, client)
        fc_redo = FunctionCall(self.__client_repo.remove_client, id)
        operations = [Operation(fc_undo, fc_redo)]

        # Remove all rentals for this client
        rentals = self.__rental_service.filter_rentals(client, None)
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

        old_client = self.__client_repo.get_by_id(id)
        new_client = Client(id, name)
        self.__client_repo.update_client(new_client)

        fc_undo = FunctionCall(self.__client_repo.update_client, old_client)
        fc_redo = FunctionCall(self.__client_repo.update_client, new_client)
        op = Operation(fc_undo, fc_redo)
        self.__undo_service.record(op)

    def display_clients(self):
        """
        This function returns all the clients
        :return: the list of clients
        """
        return self.__client_repo.display_all_clients()

    def search_client_by_id(self, id):
        try:
            id = int(id)
        except:
            raise RepositoryException("The id must be an integer!")

        if id <= 0:
            raise RepositoryException("The id must be a positive integer!")

        return self.__client_repo.search_client_by_id(id)

    def search_client_by_name(self, name):
        return self.__client_repo.search_client_by_name(name)

    def most_active_clients(self):
        pass

    def get_all_ids(self):
        return self.__client_repo.get_all_ids()

    def generate_random_client(self):
        fake = Faker()
        cnt = 1
        for i in range(20):
            id = cnt
            name = fake.name()
            self.add_client(id, name)
            cnt += 1