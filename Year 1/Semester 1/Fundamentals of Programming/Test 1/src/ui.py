from src.functions import add_coffee, sort_the_coffees, to_string, initial_items, filter_coffees, delete_coffee


def create_menu():
    print("Please choose one of the following options")

    l = []
    initial_items(l)
    while True:
        print("1) Add a coffee")
        print("2) Display all coffees sorted alphabetically")
        print("3) Filter coffees")
        print("4) Delete all coffees originating from a given country")
        print("5) Exit the program")

        cmd = input("-> ")

        if cmd == "1":
            name = input("Choose a name: ")
            country = input("Choose a country: ")
            price = input("Choose a price: ")

            try:
                add_coffee(l, name, country, price)
            except ValueError as ve:
                print(ve)

        elif cmd == "2":
            sort_the_coffees(l)
            for c in l:
                print(to_string(c))

        elif cmd == "3":
            country = input("Choose a country: ")
            price = input("Choose a price: ")
            found = filter_coffees(l, country, price)

            if found == False:
                print("No such coffees")

        elif cmd == "4":
            country = input("Choose a country: ")
            delete_coffee(l, country)

        elif cmd == "5":
            break
        else:
            print("Bad command!")