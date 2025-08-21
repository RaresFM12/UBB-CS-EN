from src.domain.client import Client
from src.repository.client_memory_repo import ClientMemoryRepository


class ClientTextFileRepo(ClientMemoryRepository):
    def __init__(self, file_name = "client.txt"):
        super().__init__()
        self.__file_name = file_name
        self._load_file()

    def erase_data(self):
        super().erase_data()
        open(self.__file_name, "w").close()

    def _load_file(self):
        lines_from_text_file = []
        try:
            test_file_input = open(self.__file_name, "rt")
            lines_from_text_file = test_file_input.readlines()
            test_file_input.close()
        except IOError:
            pass

        for line in lines_from_text_file:
            current_line = line.split(", ")
            new_book = Client(int(current_line[0].strip()), current_line[1].strip())
            super().add_client(new_book)

    def _save_file(self):
        text_output_file = open(self.__file_name, "wt")
        for client in super().display_all_clients():
            client_string = str(client.id) + ", " + client.name + "\n"
            text_output_file.write(client_string)

        text_output_file.close()

    def add_client(self, object):
        """
        This function adds a client to the list
        :param object: the client
        :return: None
        """
        super().add_client(object)
        self._save_file()

    def remove_client(self, id):
        """
        This function removes a client
        :param id: the id
        :return: None
        """
        super().remove_client(id)
        self._save_file()

    def update_client(self, object):
        """
        This function updates a client
        :param object: the client
        :return: None
        """
        super().update_client(object)
        self._save_file()

    def display_all_clients(self):
        """
        This function returns all the clients
        :return: the list of clients
        """
        return super().display_all_clients()

    def search_client_by_id(self, id):
        return super().search_client_by_id(id)

    def search_client_by_name(self, title):
        return super().search_client_by_name(title)

    def get_all_ids(self):
        return super().get_all_ids()