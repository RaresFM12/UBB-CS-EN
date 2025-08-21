from src.repository.BinaryFileRepository import BinaryFileRepository
from src.repository.MemoryRepository import MemoryRepository
from src.repository.TextFileRepository import TextFileRepository
from src.tests.tests import Test
from src.ui.ui import UI

def test_all_repo():
    memo_repo_test = MemoryRepository()
    text_repo_test = TextFileRepository("students_test.txt")
    bin_repo_test = BinaryFileRepository("students_test.bin")

    tests_memory_repository = Test(memo_repo_test)
    tests_memory_repository.test_add()
    tests_memory_repository.test_add_repo()

    tests_text_repository = Test(text_repo_test)
    tests_text_repository.test_add()
    tests_text_repository.test_add_repo()

    tests_bin_repository = Test(bin_repo_test)
    tests_bin_repository.test_add()
    tests_bin_repository.test_add_repo()

test_all_repo()
ui = UI()
ui.create_menu()