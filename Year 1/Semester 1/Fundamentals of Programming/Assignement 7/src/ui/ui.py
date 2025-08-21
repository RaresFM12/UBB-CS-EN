import random

from src.domain.student import Student
from src.repository.BinaryFileRepository import BinaryFileRepository
from src.repository.MemoryRepository import RepositoryException, MemoryRepository
from src.repository.TextFileRepository import TextFileRepository
from src.services.StudentService import StudentService


class UI:
    def __init__(self):
        repo = self.choose_repo()
        self.__student_service = StudentService(repo)

        repo_test = MemoryRepository()
        if type(repo) == type(repo_test):
            self.generate_random_values()

    def create_menu(self):
        self.__student_service.set_nr_operations(0)

        while True:
            print("1) Add a student")
            print("2) Display the list of students")
            print("3) Filter the list")
            print("4) Undo")
            print("5) Exit")

            cmd = input("-> ")

            if cmd == "1":
                id = input("The id of the student: ")
                name = input("The name of the student: ")
                group = input("The group of the student: ")

                try:
                    self.__student_service.add_student(id, name, group)
                except RepositoryException as re:
                    print(re)
                except ValueError as ve:
                    print(ve)

            elif cmd == "2":
                try:
                    students = self.__student_service.get_all_students()
                    for stud in students:
                        print(stud)
                except RepositoryException as ve:
                    print(ve)

            elif cmd == "3":
                group = input("Choose the group: ")

                try:
                    self.__student_service.filter_students(group)
                except ValueError as ve:
                    print(ve)

            elif cmd == "4":
                try:
                    self.__student_service.undo_last_operation()
                except RepositoryException as re:
                    print(re)
                except ValueError as ve:
                    print(ve)

            elif cmd == "5":
                print("Goodbye!")
                return
            else:
                print("Bad command!")

    def choose_repo(self):
        while True:
            print("Please choose a repository:")
            print("1) Memory Repository")
            print("2) Text File Repository")
            print("3) Binary Repository")

            cmd = input("-> ")

            if cmd == "1":
                repo = MemoryRepository()
                return repo
            elif cmd == "2":
                repo = TextFileRepository()
                return repo
            elif cmd == "3":
                repo = BinaryFileRepository()
                return repo
            else:
                print("Bad command!")

    def generate_random_values(self):
        list_of_names = ["Alexandru", "Beatrice", "Cristian", "Diana", "Eduard", "Fiona", "Gabriel", "Hana",
                         "Irina", "Jovan", "Karina", "Liam", "Nadia", "Octavian", "Petra", "Radu", "Simona", "Tiberiu",
                         "Tessa", "Ursula", "Vladimir"]

        cnt = 1
        for i in range(10):
            unique_id = cnt
            name = random.choice(list_of_names)
            group = random.randint(1, 100)
            self.__student_service.add_student(unique_id, name, group)
            cnt += 1