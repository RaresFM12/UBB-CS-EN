from imghdr import tests

from src.domain.student import Student
from src.repository.MemoryRepository import MemoryRepository


class TextFileRepository(MemoryRepository):
    def __init__(self, file_name = "students.txt"):
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
            current_line = line.split(' ')
            new_student = Student(int(current_line[0].strip()), current_line[1].strip(), int(current_line[2].strip()))
            super().add_new_student(new_student)

    def _save_file(self):
        text_output_file = open(self.__file_name, "wt")
        for student in self.get_list_with_all_students():
            student_string = str(student.id) + " " + student.name + " " + str(student.group) + "\n"
            text_output_file.write(student_string)

        text_output_file.close()

    def add_new_student(self, new_student: Student):
        """
        This function adds a new student to the list of the students, in a text file
        :param new_student: the new student we want to add to the list
        :return: None
        :raises: RepositoryException if the student is already in the list
        """
        super().add_new_student(new_student)
        self._save_file()

    def filter_students_according_to_group(self, group: int):
        super().filter_students_according_to_group(group)
        self._save_file()

    def undo_last_operation(self):
        super().undo_last_operation()
        self._save_file()


