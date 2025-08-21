import random
from random import randint

from src.domain.student import Student
from src.repository.MemoryRepository import RepositoryException


class StudentService:
    def __init__(self, repo):
        self.__repo = repo
        self.__operations = 0

    def clear_students(self):
        self.__repo.erase_data()

    def set_nr_operations(self, op):
        self.__operations = op

    def add_student(self, id: str, name: str, group: str):
        """
        This function adds a new student
        :param id: id of the student
        :param name: name of the student
        :param group: the group of the student
        :return: None
        :raises: ValueErrors if id or group is not a positive integer
        """
        try:
            id = int(id)
        except:
            raise ValueError("The id must be an integer!")

        if id <= 0:
            raise ValueError("The id must be a positive integer!")

        try:
            group = int(group)
        except:
            raise ValueError("The group must be an integer!")

        if group <= 0:
            raise ValueError("The group must be a positive integer!")

        new_student = Student(id, name, group)
        self.__repo.add_new_student(new_student)
        self.__operations += 1

    def get_all_students(self):
        return self.__repo.get_list_with_all_students()

    def filter_students(self, group):
        try:
            group = int(group)
        except:
            raise ValueError("The group must be an integer!")

        if group <= 0:
            raise ValueError("The group must be a positive integer!")

        self.__repo.filter_students_according_to_group(group)
        self.__operations += 1

    def undo_last_operation(self):
        if self.__operations <= 0:
            raise ValueError("There are no more undos left!")

        self.__operations -= 1
        self.__repo.undo_last_operation()


