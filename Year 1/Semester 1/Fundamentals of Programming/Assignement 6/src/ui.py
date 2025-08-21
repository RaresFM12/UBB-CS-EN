#
# This is the program's UI module. The user interface and all interaction with the user (print and input statements) are found here
#
from copy import deepcopy
from datetime import datetime
import texttable

from src.functions import add_transaction_4_words, add_transaction_5_words, remove_transaction_2_words_day, \
    remove_transaction_2_words_type, remove_transaction_4_words_interval, replace_transaction_6_words, \
    display_account_balance, get_type, get_value, display_all_transactions, display_all_type_transactions, \
    display_all_equal_transactions, display_all_larger_transactions, display_all_smaller_transactions, \
    filter_type_transactions, filter_amount_of_money_transactions, undo, initial_items


def add_transaction(string: list, l: list, undo_list: list):
    if len(string) == 4 and string[0] == "add":
        transaction = add_transaction_4_words(string)
        if len(undo_list) >= 1:
            l = deepcopy(undo_list[-1])
        else:
            l = []

        l.append(transaction)
        undo_list.append(l)
    elif len(string) == 5 and string[0] == "insert":
        transaction = add_transaction_5_words(string)
        if len(undo_list) >= 1:
            l = deepcopy(undo_list[-1])
        else:
            l = []

        l.append(transaction)
        undo_list.append(l)
    else:
        print("Bad command!!!")

def modify_transaction(string: list, l: list, undo_list: list):
    if len(string) == 2 and string[0] == "remove":
        if string[1] == "in" or string[1] == "out":
            if len(undo_list) >= 1:
                l = deepcopy(undo_list[-1])
            else:
                l = []

            remove_transaction_2_words_type(string, l)
            undo_list.append(l)
        else:
            if len(undo_list) >= 1:
                l = deepcopy(undo_list[-1])
            else:
                l = []

            remove_transaction_2_words_day(string, l)
            undo_list.append(l)

    elif len(string) == 4 and string[0] == "remove":
        if len(undo_list) >= 1:
            l = deepcopy(undo_list[-1])
        else:
            l = []

        remove_transaction_4_words_interval(string, l)
        undo_list.append(l)

    elif len(string) == 6 and string[0] == "replace":
        if len(undo_list) >= 1:
            l = deepcopy(undo_list[-1])
        else:
            l = []

        replace_transaction_6_words(string, l)
        undo_list.append(l)
    else:
        print("Bad command!!!")

def display_transactions(string: list, l: list, undo_list: list):
    if len(string) == 1:
        if len(undo_list) > 0:
            table = display_all_transactions(string, undo_list[-1])
            print(table.draw())
        else:
            print("The list of transactions is empty!!!")

    elif len(string) == 2:
        if len(undo_list) > 0:
            table = display_all_type_transactions(string, undo_list[-1])
            print(table.draw())
        else:
            print("The list of transactions is empty!!!")

    elif len(string) == 3:
        if string[1] == "balance":
            if len(undo_list) > 0:
                balance = display_account_balance(string, undo_list[-1])
                print(f"The account's balance at the end of day {string[2]}: {balance}")
            else:
                print("The list of transactions is empty!!!")

        elif string[1] == "=":
            if len(undo_list) > 0:
                table = display_all_equal_transactions(string, undo_list[-1])
                print(table.draw())
            else:
                print("The list of transactions is empty!!!")

        elif string[1] == ">":
            if len(undo_list) > 0:
                table = display_all_larger_transactions(string, undo_list[-1])
                print(table.draw())
            else:
                print("The list of transactions is empty!!!")

        elif string[1] == "<":
            if len(undo_list) > 0:
                table = display_all_smaller_transactions(string, undo_list[-1])
                print(table.draw())
            else:
                print("The list of transactions is empty!!!")

        else:
            print("Bad command!!!")
    else:
        print("Bad command!!!")

def filter_transactions(string: list, l: list, undo_list: list):
    if len(string) == 2:
        if len(undo_list) >= 1:
            l = deepcopy(undo_list[-1])
        else:
            l = []

        filter_type_transactions(string, l)
        undo_list.append(l)

    elif len(string) == 3:
        if len(undo_list) >= 1:
            l = deepcopy(undo_list[-1])
        else:
            l = []

        filter_amount_of_money_transactions(string, l)
        undo_list.append(l)

    else:
        print("Bad commnand!!!")

def create_menu():
    print("Please choose one of the following options:")
    print("A) Add transaction")
    print("B) Modify transaction")
    print("C) Display transactions having different properties")
    print("D) Filter")
    print("E) Undo")

    l = []
    undo_list = []
    initial_items(l, undo_list)

    while True:
        string = input("Write a command: ").split(" ")

        if string[0] == "add" or string[0] == "insert":
            try:
                add_transaction(string, l, undo_list)
            except ValueError as ve:
                print(ve)
        elif string[0] == "remove" or string[0] == "replace":
            try:
                modify_transaction(string, l, undo_list)
            except ValueError as ve:
                print(ve)
        elif string[0] == "list":
            try:
                display_transactions(string, l, undo_list)
            except ValueError as ve:
                print(ve)
        elif string[0] == "filter":
            try:
                filter_transactions(string, l, undo_list)
            except ValueError as ve:
                print(ve)
        elif string[0] == "undo":
            try:
                undo(undo_list)
            except ValueError as ve:
                print(ve)

        elif string[0] == "exit":
            break
        else:
            print("Bad command!!!")
