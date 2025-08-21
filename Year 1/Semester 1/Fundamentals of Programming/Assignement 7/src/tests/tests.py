from src.domain.student import Student
from src.services.StudentService import StudentService


class Test:
    def __init__(self, repo):
        self.__student_service = StudentService(repo)
        self.__repo = repo

    def test_add(self):
        """
        This function tests if the add function works as expected
        :return: None
        """
        self.__student_service.add_student(100, "Ion", 914)
        assert len(self.__student_service.get_all_students()) == 1

        self.__student_service.add_student(101, "Ana", 913)
        assert len(self.__student_service.get_all_students()) == 2

        self.__student_service.add_student(102, "Mateiut", 913)
        assert len(self.__student_service.get_all_students()) == 3

        self.clear_files()

    def test_add_repo(self):
        """
        This function tests if the add function works as expected
        :return: None
        """
        self.__repo.add_new_student(Student(100, "Ion", 914))
        assert len(self.__repo.get_list_with_all_students()) == 1

        self.__repo.add_new_student(Student(101, "Ioana", 913))
        assert len(self.__repo.get_list_with_all_students()) == 2

        self.__repo.add_new_student(Student(102, "Adela", 914))
        assert len(self.__repo.get_list_with_all_students()) == 3

        self.clear_files()

    def clear_files(self):
        self.__student_service.clear_students()