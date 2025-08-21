from src.repository.repository_exception import RepositoryException


class Repository:
    def __init__(self):
        self.__data = {}

    def check_if_present(self, id_entity):
        if id_entity in self.__data.keys():
            raise RepositoryException("This id is already in!")

    def check_if_not_present(self, id_entity):
        if id_entity not in self.__data.keys():
            raise RepositoryException("This id doesn't exist!")

    def get_element_by_id(self, id_entity):
        return self.__data[id_entity]

    def add(self, object):
        """
        This function adds an object to the list
        :param object: the object
        :return: None
        """
        self.check_if_present(object.id)
        self.__data[object.id] = object

    def remove(self, id):
        """
        This function removes an object
        :param id: the id
        :return: None
        """
        self.check_if_not_present(id)
        del self.__data[id]

    def update(self, object):
        """
        This function updates an object
        :param object: the new object
        :return: None
        """
        self.check_if_not_present(object.id)
        self.__data[object.id] = object

    def search_by_id(self, id):
        self.check_if_not_present(id)

        object_list = []
        id = str(id)

        for object in self.__data.values():
            object_id = str(object.id)
            if id == object_id:
                object_list.append(object)

        return object_list

    def get_all(self):
        """
        This fucntion returns the list of objects
        :return: the list of objects
        """
        return list(self.__data.values())

    def get_all_ids(self):
        return list(self.__data.keys())

    def delete_all(self):
        self.__data.clear()