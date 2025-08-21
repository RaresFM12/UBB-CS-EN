import datetime

from src.repository.return_memory_repo import ReturnMemoryRepository


class ReturnTextFileRepo(ReturnMemoryRepository):
    def __init__(self, file_name = "return.txt"):
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

            array1 = current_line[1].split("-")
            s = array1[2].split(" ")
            datetime_str1 = datetime.datetime(int(array1[0]), int(array1[1]), int(s[0]))

            super().add_return_date(int(current_line[0].strip()), datetime_str1)

    def _save_file(self):
        text_output_file = open(self.__file_name, "wt")
        for book in super().display_returned_books():
            book_string = (str(book[0]) + ", " + str(book[1]) + "\n")
            text_output_file.write(book_string)

        text_output_file.close()

    def add_return_date(self, id, date):
        super().add_return_date(id, date)
        self._save_file()

    def remove_return(self):
        super().remove_return()
        self._save_file()

    def display_returned_books(self):
        return super().display_returned_books()

    def get_all_ids(self):
        return super().get_all_ids()