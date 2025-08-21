import random
from copy import deepcopy

from src.domain.student import Student

class RepositoryException(Exception):
    pass

class MemoryRepository:
    def __init__(self):
        self.__all_students_data = []
        self.__undo_list = []
        self.__students_id = []
        self.__undo_list_id = []

    def erase_data(self):
        self.__all_students_data.clear()
        self.__undo_list.clear()
        self.__students_id.clear()
        self.__undo_list_id.clear()

    def add_new_student(self, new_student: Student):
        """
        This function adds a new student to the list of the students, in the memory
        :param new_student: the new student we want to add to the list
        :return: None
        :raises: RepositoryException if the student is already in the list
        """
        if new_student in self.__all_students_data:
            raise RepositoryException("This student already exists!")

        if len(self.__undo_list) >= 1:
            self.__all_students_data = deepcopy(self.__undo_list[-1])
        else:
            self.__all_students_data = []

        if len(self.__undo_list_id) >= 1:
            self.__students_id = deepcopy(self.__undo_list_id[-1])
        else:
            self.__students_id = []

        if new_student.id in self.__students_id:
            raise RepositoryException("This id already exists!")

        self.__students_id.append(new_student.id)
        self.__all_students_data.append(new_student)
        self.__undo_list.append(self.__all_students_data)
        self.__undo_list_id.append(self.__students_id)

    def get_list_with_all_students(self):
        if len(self.__undo_list) == 0:
            raise RepositoryException("There are no students!")

        return self.__undo_list[-1]

    def filter_students_according_to_group(self, group: int):
        if len(self.__undo_list) >= 1:
            self.__all_students_data = deepcopy(self.__undo_list[-1])
        else:
            self.__all_students_data = []

        if len(self.__undo_list_id) >= 1:
            self.__students_id = deepcopy(self.__undo_list_id[-1])
        else:
            self.__students_id = []

        for i in range(len(self.__all_students_data) - 1, -1, -1):
            if self.__all_students_data[i].group == group:
                self.__all_students_data.pop(i)
                self.__students_id.pop(i)

        self.__undo_list.append(self.__all_students_data)
        self.__undo_list_id.append(self.__students_id)

    def undo_last_operation(self):
        if len(self.__undo_list) - 1 < 0:
            raise RepositoryException("The are no more undos left!")

        self.__undo_list.pop(len(self.__undo_list) - 1)
        self.__undo_list_id.pop(len(self.__undo_list_id) - 1)