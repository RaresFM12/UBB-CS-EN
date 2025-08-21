import unittest
import time

from src.tests.test_ai import TestAI
from src.tests.test_game import TestGame
from src.ui.ui import UI


def run_tests():
    suite = unittest.TestLoader().loadTestsFromTestCase(TestGame)
    unittest.TextTestRunner().run(suite)

    suite = unittest.TestLoader().loadTestsFromTestCase(TestAI)
    unittest.TextTestRunner().run(suite)


if __name__ == "__main__":
    run_tests()
    time.sleep(0.5)

    ui = UI()
    ui.run()
