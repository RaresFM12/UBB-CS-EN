class Student:
    def __init__(self, id: int, name: str, group: int):
        self.__id = id
        self.__name = name
        self.__group = group

    @property
    def id(self):
        return self.__id

    @property
    def name(self):
        return self.__name

    @property
    def group(self):
        return self.__group

    @id.setter
    def id(self, new_value: int):
        self.__id = new_value

    @name.setter
    def name(self, new_value: str):
        self.__name = new_value

    @group.setter
    def group(self, new_value: int):
        self.__group

    def __str__(self):
        return self.name + " has the id = " + str(self.id) + " and is in group " + str(self.group)


