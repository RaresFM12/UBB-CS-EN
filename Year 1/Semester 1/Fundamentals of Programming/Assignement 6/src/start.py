#
# This module is used to invoke the program's UI and start it. It should not contain a lot of code.
#
from src.functions import initial_items, run_tests
from src.ui import create_menu

if __name__ == "__main__":
    run_tests()
    create_menu()
