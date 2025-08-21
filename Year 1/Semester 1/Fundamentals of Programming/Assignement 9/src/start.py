import unittest

from src.test.test_book_file_repo import TestBookFileRepo
from src.test.test_book_memory_repo import TestBookMemoryRepo
from src.test.test_book_service import TestBookService
from src.test.test_client_file_repo import TestClientFileRepo
from src.test.test_client_service import TestClientService
from src.ui.ui import Ui

def get_repo():
    param = []
    lines_from_text_file = []
    try:
        test_file_input = open("settings.properties", "rt")
        lines_from_text_file = test_file_input.readlines()
        test_file_input.close()
    except IOError:
        pass

    for line in lines_from_text_file:
        words = line.split()
        if len(words) >= 3:
            param.append(words[2].strip())

    return param

def run_tests():
    suite = unittest.TestLoader().loadTestsFromTestCase(TestBookFileRepo)
    unittest.TextTestRunner().run(suite)

    suite = unittest.TestLoader().loadTestsFromTestCase(TestBookMemoryRepo)
    unittest.TextTestRunner().run(suite)

    suite = unittest.TestLoader().loadTestsFromTestCase(TestClientFileRepo)
    unittest.TextTestRunner().run(suite)

    suite = unittest.TestLoader().loadTestsFromTestCase(TestClientFileRepo)
    unittest.TextTestRunner().run(suite)

if __name__ == "__main__":
    run_tests()
    param = get_repo()
    ui = Ui(param)
    ui.create_menu()