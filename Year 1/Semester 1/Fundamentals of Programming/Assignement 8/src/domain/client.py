class Client:
    def __init__(self, client_id: int, name: str):
        self.__client_id = client_id
        self.__name = name

    @property
    def id(self):
        return self.__client_id

    @property
    def name(self):
        return self.__name

    @id.setter
    def id(self, client_id: int):
        self.__client_id = client_id

    @name.setter
    def name(self, client_name: str):
        self.__name = client_name

    def __str__(self):
        return self.name + " has the id " + str(self.id)
