#
# The program's functions are implemented here. There is no user interaction in this file, therefore no input/print statements. Functions here
# communicate via function parameters, the return statement and raising of exceptions. 
#
from copy import deepcopy
from datetime import datetime
import pdoc

import texttable

def get_day(transaction):
    return transaction["day"]

def get_value(transaction):
    return transaction["value"]

def get_type(transaction):
    return transaction["type"]

def get_description(transaction):
    return transaction["description"]

def set_day(transaction, day):
    transaction["day"] = day

def set_value(transaction, value):
    transaction["value"] = value

def set_type(transaction, type):
    transaction["type"] = type

def set_description(transaction, description):
    transaction["description"] = description

def add_transaction_4_words(string: list):
    """
    This function adds to the list the new transaction, when the command has 4 words
    :param string: the command
    :return: the new transaction
    :raises ValueError: "The value has to be an integer", "The value has to be a positive integer",
                        "The type must be in or out!!!"
    """
    try:
        value = int(string[1])
    except ValueError:
        raise ValueError("The value has to be an integer")

    if value <= 0:
        raise ValueError("The value has to be a positive integer")

    type = string[2]
    if type != "in" and type != "out":
        raise ValueError("The type must be in or out!!!")

    description = string[3]
    current_date = datetime.now()

    transaction = {
        "day": current_date.day,
        "value": value,
        "type": type,
        "description": description
    }

    return transaction

def add_transaction_5_words(string: list):
    """
    This function adds to the list the new transaction, when the command has 5 words
    :param string: the command
    :return: the new transaction
    :raises ValueError: "The day must be a number!", "The day must be a number between 1 and 30!",
                        "The value has to be an integer", "The value has to be a positive integer",
                        "The type must be in or out!!!"
    """
    try:
        day = int(string[1])
    except ValueError:
        raise ValueError("Day must be a number!")

    if day < 1 or day > 30:
        raise ValueError("Day must be a number between 1 and 30!")

    try:
        value = int(string[2])
    except ValueError:
        raise ValueError("The value has to be an integer")

    if value <= 0:
        raise ValueError("The value has to be a positive integer")

    type = string[3]
    if type != "in" and type != "out":
        raise ValueError("The type must be in or out!!!")

    description = string[4]

    transaction = {
        "day": day,
        "value": value,
        "type": type,
        "description": description
    }

    return transaction

def remove_transaction_2_words_day(string: list, l: list):
    """
    This function removes all the transactions that took place on a specific day
    :param string: the command
    :param l: the list of transactions
    :return: None
    :raises ValueError: "Day must be an integer", "Day must be a number between 1 and 30!"
    """
    try:
        day = int(string[1])
    except ValueError:
        raise ValueError("Day must be an integer")

    if day < 1 or day > 30:
        raise ValueError("Day must be a number between 1 and 30!")

    for i in range(len(l) - 1, -1, -1):
        if get_day(l[i]) == day:
            l.pop(i)


def remove_transaction_2_words_type(string: list, l: list):
    """
    This function removes all the transactions that have a specific type, given by the user
    :param string: the command
    :param l: the list of transactions
    :return: None
    :raises ValueError: "The type must be in or out!!!"
    """
    type = string[1]
    if type != "in" and type != "out":
        raise ValueError("The type must be in or out!!!")

    for i in range(len(l) - 1, -1, -1):
        if get_type(l[i]) == type:
            l.pop(i)

def remove_transaction_4_words_interval(string: list, l: list):
    """
    This function removes all the transactions from a specific interval of days, given by the user
    :param string: the command
    :param l: the list of transactions
    :return: None
    :raises ValueError: "Every value for day must be an integer!", "This interval is not good!!!",
                        "Bad command!!!"
    """
    try:
        day1 = int(string[1])
        day2 = int(string[3])
    except ValueError:
        raise ValueError("Every value for day must be an integer!")

    if (day1 < 1 or day1 > 30) or (day2 < 1 or day2 > 30):
        raise ValueError("This interval is not good!!!")

    if day1 > day2:
        raise ValueError("This interval is not good!!!")

    if string[2] != "to":
        raise ValueError("Bad command!!!")

    for i in range(len(l) - 1, -1, -1):
        if get_day(l[i]) >= day1 and get_day(l[i]) <= day2:
            l.pop(i)

def replace_transaction_6_words(string: list, l: list):
    """
    This function replaces the amount of money for a specific transaction
    :param string: the command
    :param l: the list of transactions
    :return: None
    :raises ValueError: "Day must be an integer!", "Day must be a number between 1 and 30!",
                        "The type must be in or out!!!", "Bad command!!!", "The new value must be an integer!"
                        "The value has to be a positive integer"
    """

    try:
        day = int(string[1])
    except ValueError:
        raise ValueError("Day must be an integer!")

    if day < 1 or day > 30:
        raise ValueError("Day must be a number between 1 and 30!")

    type = string[2]
    if type != "in" and type != "out":
        raise ValueError("The type must be in or out!!!")

    description = string[3]

    if string[4] != "with":
        raise ValueError("Bad command!!!")

    try:
        new_value = int(string[5])
    except ValueError:
        raise ValueError("The new value must be an integer!")

    if new_value <= 0:
        raise ValueError("The value has to be a positive integer")

    for i in range(len(l)):
        if get_type(l[i]) == type and get_description(l[i]) == description and get_day(l[i]) == day:
            set_value(l[i], new_value)

def display_all_transactions(string: list, l: list):
    """
    This function puts all the transactions into a texttable
    :param string: the command
    :param l: the list of all transactions
    :return: the table
    """
    table = texttable.Texttable()
    table.add_row(['Day', 'Value', 'Type', 'Description'])

    for i in l:
        table.add_row([get_day(i), get_value(i), get_type(i), get_description(i)])

    return table

def display_all_type_transactions(string: list, l: list):
    """
    This function puts all the transactions with the same type(given by the user) into a texttable
    :param string: the command
    :param l: the list of all transactions
    :return: the table
    :raises ValueError: "The type must be in or out!!!"
    """
    type = string[1]
    if type != "in" and type != "out":
        raise ValueError("The type must be in or out!!!")

    table = texttable.Texttable()
    table.add_row(['Day', 'Value', 'Type', 'Description'])

    for i in l:
        if get_type(i) == type:
            table.add_row([get_day(i), get_value(i), get_type(i), get_description(i)])

    return table


def display_account_balance(string: list, l: list):
    """
    This function computes the account’s balance at the end of the day given by the user
    :param string: the command
    :param l: the list of all transactions
    :return: account's balance
    :raises ValueError: "Day must be an integer!", "Day must be a number between 1 and 30!"
    """
    try:
        day = int(string[2])
    except ValueError:
        raise ValueError("Day must be an integer!")

    if day < 1 or day > 30:
        raise ValueError("Day must be a number between 1 and 30!")

    acc_bal = 0
    for i in l:
        if get_type(i) == "in" and get_day(i) <= day:
            acc_bal += get_value(i)
        elif get_type(i) == "out" and get_day(i) <= day:
            acc_bal -= get_value(i)

    return acc_bal

def display_all_equal_transactions(string: list, l: list):
    """
    This function displays all the transactions that have the value equal to the value of the user
    :param string: the command
    :param l: the list of all transactions
    :return: the table
    :raises ValueError: "The value has to be an integer", "The value has to be a positive integer"
    """
    try:
        value = int(string[2])
    except ValueError:
        raise ValueError("The value has to be an integer")

    if value <= 0:
        raise ValueError("The value has to be a positive integer")

    table = texttable.Texttable()
    table.add_row(['Day', 'Value', 'Type', 'Description'])

    for i in l:
        if get_value(i) == value:
            table.add_row([get_day(i), get_value(i), get_type(i), get_description(i)])

    return table

def display_all_smaller_transactions(string: list, l: list):
    """
    This function displays all the transactions that have the value smaller than the value of the user
    :param string: the command
    :param l: the list of all transactions
    :return: the table
    :raises ValueError: "The value has to be an integer", "The value has to be a positive integer"
    """
    try:
        value = int(string[2])
    except ValueError:
        raise ValueError("The value has to be an integer")

    if value <= 0:
        raise ValueError("The value has to be a positive integer")

    table = texttable.Texttable()
    table.add_row(['Day', 'Value', 'Type', 'Description'])

    for i in l:
        if get_value(i) < value:
            table.add_row([get_day(i), get_value(i), get_type(i), get_description(i)])

    return table

def display_all_larger_transactions(string: list, l: list):
    """
    This function displays all the transactions that have the value larger than the value of the user
    :param string: the command
    :param l: the list of all transactions
    :return: the table
    :raises ValueError: "The value has to be an integer", "The value has to be a positive integer"
    """
    try:
        value = int(string[2])
    except ValueError:
        raise ValueError("The value has to be an integer")

    if value <= 0:
        raise ValueError("The value has to be a positive integer")

    table = texttable.Texttable()
    table.add_row(['Day', 'Value', 'Type', 'Description'])

    for i in l:
        if get_value(i) > value:
            table.add_row([get_day(i), get_value(i), get_type(i), get_description(i)])

    return table

def filter_type_transactions(string: list, l: list):
    """
    This function filters all the transactions that have the type given by the user
    :param string: the command
    :param l: the list of all transactions
    :return: None
    :raises ValueError: "The type must be in or out!!!"
    """
    type = string[1]
    if type != "in" and type != "out":
        raise ValueError("The type must be in or out!!!")

    for i in range(len(l) - 1, -1, -1):
        if get_type(l[i]) != type:
            l.pop(i)

def filter_amount_of_money_transactions(string: list, l: list):
    """
    This function filters only the transactions of a specific type and a specific value
    :param string: the command
    :param l: the list of all transactions
    :return: None
    :raises ValueError: "The type must be in or out!!!", "The value has to be an integer", "The value has to be a positive integer"
    """
    type = string[1]
    if type != "in" and type != "out":
        raise ValueError("The type must be in or out!!!")

    try:
        value = int(string[2])
    except ValueError:
        raise ValueError("The value has to be an integer")

    if value <= 0:
        raise ValueError("The value has to be a positive integer")

    for i in range(len(l) - 1, -1, -1):
        if get_type(l[i]) != type or get_value(l[i]) >= value:
            l.pop(i)

def undo(undo_list: list):
    """
    Undo function
    :param undo_list: the list where are saved the previous changes
    :return: None
    :raises ValueError: "There are no more undos left!!!"
    """
    if len(undo_list) - 1 < 0:
        raise ValueError("There are no more undos left!!!")

    undo_list.pop(len(undo_list) - 1)

def test_add_transaction_4_words():
    """
    This function tests if the function add_transaction_4_words() works as expected
    :return: None
    """
    string1 = ["add", "100", "in", "pizza"]
    transaction1 = add_transaction_4_words(string1)

    assert get_day(transaction1) == datetime.now().day
    assert get_type(transaction1) == "in"
    assert get_value(transaction1) == 100
    assert get_description(transaction1) == "pizza"

    try:
       string2 = ["add", "100", "inn", "pizza"]
       transaction2 = add_transaction_4_words(string2)
       assert False
    except ValueError:
       assert True

def test_add_transaction_5_words():
    """
    This function tests if the function add_transaction_5_words() works as expected
    :return: None
    """
    string1 = ["insert", "12", "100", "in", "pizza"]
    transaction1 = add_transaction_5_words(string1)

    assert get_day(transaction1) == 12
    assert get_type(transaction1) == "in"
    assert get_value(transaction1) == 100
    assert get_description(transaction1) == "pizza"

    try:
       string2 = ["insert", "31", "100", "in", "pizza"]
       transaction2 = add_transaction_5_words(string2)
       assert False
    except ValueError:
       assert True

def test_remove_transaction_2_words_day():
    """
    This function tests if the function remove_transaction_2_words_day() works as expected
    :return: None
    """
    l = []
    string1 = ["insert", "12", "100", "in", "pizza"]
    transaction1 = add_transaction_5_words(string1)
    l.append(transaction1)

    string2 = ["insert", "13", "100", "in", "pizza"]
    transaction2 = add_transaction_5_words(string2)
    l.append(transaction2)

    remove_transaction_2_words_day(["remove", "12"], l)
    assert len(l) == 1

    try:
        remove_transaction_2_words_day(["remove", "35"], l)
        assert False
    except ValueError:
        assert True

def test_remove_transaction_2_words_type():
    """
    This function tests if the function remove_transaction_2_words_type() works as expected
    :return: None
    """
    l = []
    string1 = ["insert", "12", "100", "in", "pizza"]
    transaction1 = add_transaction_5_words(string1)
    l.append(transaction1)

    string2 = ["insert", "13", "100", "out", "pizza"]
    transaction2 = add_transaction_5_words(string2)
    l.append(transaction2)

    remove_transaction_2_words_type(["remove", "in"], l)
    assert len(l) == 1

    try:
        remove_transaction_2_words_type(["remove", "inn"], l)
        assert False
    except ValueError:
        assert True

def test_remove_transaction_4_words_interval():
    """
    This function tests if the function remove_transaction_4_words_interval() works as expected
    :return: None
    """
    l = []
    string1 = ["insert", "12", "100", "in", "pizza"]
    transaction1 = add_transaction_5_words(string1)
    l.append(transaction1)

    string2 = ["insert", "15", "100", "out", "pizza"]
    transaction2 = add_transaction_5_words(string2)
    l.append(transaction2)

    remove_transaction_4_words_interval(["remove", "10", "to", "14"], l)
    assert len(l) == 1

    try:
        remove_transaction_2_words_type(["remove", "5", "to", "35"], l)
        assert False
    except ValueError:
        assert True

def test_replace_transaction():
    """
    This function tests if the function replace_transaction() works as expected
    :return: None
    """
    l = []
    string1 = ["insert", "12", "100", "in", "pizza"]
    transaction1 = add_transaction_5_words(string1)
    l.append(transaction1)

    replace_transaction_6_words(["replace", "12", "in", "pizza", "with", "2000"], l)
    assert get_value(l[0]) == 2000

    try:
        replace_transaction_6_words(["replace", "35", "in", "pizza", "with", "2000"], l)
        assert False
    except ValueError:
        assert True

def test_filter_type_transaction():
    """
    This function tests if the function filter_type_transaction() works as expected
    :return: None
    """
    l = []
    string1 = ["insert", "12", "100", "in", "pizza"]
    transaction1 = add_transaction_5_words(string1)
    l.append(transaction1)

    string2 = ["insert", "15", "100", "out", "pizza"]
    transaction2 = add_transaction_5_words(string2)
    l.append(transaction2)

    filter_type_transactions(["filter", "in"], l)
    assert len(l) == 1

    try:
        string3 = ["insert", "15", "100", "out", "pizza"]
        transaction3 = add_transaction_5_words(string3)
        l.append(transaction3)
        filter_type_transactions(["filter", "outt"], l)
        assert False
    except ValueError:
        assert True

def test_filter_amount_of_money():
    """
    This function tests if the function filter_amount_of_money() works as expected
    :return: None
    """
    l = []
    string1 = ["insert", "12", "100", "in", "pizza"]
    transaction1 = add_transaction_5_words(string1)
    l.append(transaction1)

    string2 = ["insert", "15", "100", "out", "pizza"]
    transaction2 = add_transaction_5_words(string2)
    l.append(transaction2)

    string3 = ["insert", "15", "200", "in", "pizza"]
    transaction3 = add_transaction_5_words(string3)
    l.append(transaction3)

    filter_amount_of_money_transactions(["filter", "in", "150"], l)
    assert len(l) == 1

    try:
        string4 = ["insert", "15", "200", "in", "pizza"]
        transaction4 = add_transaction_5_words(string4)
        l.append(transaction4)
        filter_amount_of_money_transactions(["filter", "in", "-10"], l)
        assert False
    except ValueError:
        assert True

def test_undo():
    """
    This function tests if the function undo() works as expected
    :return: None
    """
    l = []
    undo_list = []

    string1 = ["insert", "12", "100", "in", "pizza"]
    transaction1 = add_transaction_5_words(string1)
    l.append(transaction1)

    l1 = deepcopy(l)
    undo_list.append(l1)

    string2 = ["insert", "15", "100", "out", "pizza"]
    transaction2 = add_transaction_5_words(string2)
    l.append(transaction2)

    l2 = deepcopy(l)
    undo_list.append(l2)

    undo(undo_list)
    assert undo_list[0] == l1

def run_tests():
    test_add_transaction_4_words()
    test_add_transaction_5_words()
    test_remove_transaction_2_words_day()
    test_remove_transaction_2_words_type()
    test_remove_transaction_4_words_interval()
    test_replace_transaction()
    test_filter_type_transaction()
    test_filter_amount_of_money()
    test_undo()

def initial_items(l: list, undo_list: list):
    """
    This function creates the initial transactions
    :param l: the list where we add the new transaction
    :param undo_list: the list where we add the new changes
    :return: None
    """
    transaction1 = {
        "day": 1,
        "value": 100,
        "type": "in",
        "description": "pizza"
    }
    l.append(transaction1)
    l1 = deepcopy(l)
    undo_list.append(l1)

    transaction2 = {
        "day": 2,
        "value": 200,
        "type": "in",
        "description": "salary"
    }
    l.append(transaction2)
    l2 = deepcopy(l)
    undo_list.append(l2)

    transaction3 = {
        "day": 3,
        "value": 150,
        "type": "out",
        "description": "fridge"
    }
    l.append(transaction3)
    l3 = deepcopy(l)
    undo_list.append(l3)

    transaction4 = {
        "day": 3,
        "value": 350,
        "type": "out",
        "description": "books"
    }
    l.append(transaction4)
    l4 = deepcopy(l)
    undo_list.append(l4)

    transaction5 = {
        "day": 7,
        "value": 450,
        "type": "in",
        "description": "chair"
    }
    l.append(transaction5)
    l5 = deepcopy(l)
    undo_list.append(l5)

    transaction6 = {
        "day": 20,
        "value": 170,
        "type": "in",
        "description": "water"
    }
    l.append(transaction6)
    l6 = deepcopy(l)
    undo_list.append(l6)

    transaction7 = {
        "day": 7,
        "value": 100,
        "type": "out",
        "description": "ring"
    }
    l.append(transaction7)
    l7 = deepcopy(l)
    undo_list.append(l7)

    transaction8 = {
        "day": 15,
        "value": 900,
        "type": "in",
        "description": "violin"
    }
    l.append(transaction8)
    l8 = deepcopy(l)
    undo_list.append(l8)

    transaction9 = {
        "day": 13,
        "value": 150,
        "type": "out",
        "description": "piano"
    }
    l.append(transaction9)
    l9 = deepcopy(l)
    undo_list.append(l9)

    transaction10 = {
        "day": 7,
        "value": 180,
        "type": "in",
        "description": "phone"
    }
    l.append(transaction10)
    l10 = deepcopy(l)
    undo_list.append(l10)

