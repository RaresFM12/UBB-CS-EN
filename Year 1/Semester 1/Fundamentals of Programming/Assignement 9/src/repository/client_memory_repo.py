from src.repository.repository import Repository
from src.repository.repository_exception import RepositoryException


class ClientMemoryRepository(Repository):
    def __init__(self):
        super().__init__()

    def add_client(self, object):
        """
        This function adds a client to the list
        :param object: the client
        :return: None
        """
        super().add(object)

    def remove_client(self, id):
        """
        This function removes a client
        :param id: the id
        :return: None
        """
        super().remove(id)

    def update_client(self, object):
        """
        This function updates a client
        :param object: the client
        :return: None
        """
        super().update(object)

    def display_all_clients(self):
        """
        This function returns all the clients
        :return: the list of clients
        """
        return super().get_all()

    def search_client_by_id(self, id):
        return super().search_by_id(id)

    def get_by_id(self, id):
        return super().get_by_id(id)

    def search_client_by_name(self, name):
        name = name.lower()
        clients = []
        objects = super().get_all()
        for obj in objects:
            if name in obj.name.lower():
                clients.append(obj)

        if len(clients) == 0:
            raise RepositoryException("There is no such client!")

        return clients

    def erase_data(self):
        super().delete_all()

    def get_all_ids(self):
        return super().get_all_ids()