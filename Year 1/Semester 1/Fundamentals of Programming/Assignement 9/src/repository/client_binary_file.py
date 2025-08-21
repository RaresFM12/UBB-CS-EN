import pickle

from src.repository.client_memory_repo import ClientMemoryRepository


class ClientBinaryRepo(ClientMemoryRepository):
    def __init__(self, file_name = "client.bin"):
        super().__init__()
        self.__file_name = file_name
        self._load_file()

    def erase_data(self):
        super().erase_data()
        open(self.__file_name, "w").close()

    def _load_file(self):
        try:
            bin_input_file = open(self.__file_name, 'rb')
            clients_from_bin_file = pickle.load(bin_input_file)
        except EOFError:
            return

        for new_client in clients_from_bin_file:
            super().add_client(new_client)

        bin_input_file.close()

    def _save_file(self):
        bin_out_file = open(self.__file_name, "wb")
        pickle.dump(super().display_all_clients(), bin_out_file)
        bin_out_file.close()

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

    def get_by_id(self, id):
        return super().get_by_id(id)

    def get_all_ids(self):
        return super().get_all_ids()