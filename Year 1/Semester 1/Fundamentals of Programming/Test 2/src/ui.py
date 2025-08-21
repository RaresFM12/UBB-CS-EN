from src.services import AddressesService


class UI:
    def __init__(self):
        self.__service = AddressesService()

    def run(self):
        print("Choose one of the following options:")
        while True:
            print("1. Add an address")
            print("2. Determine which addresses are within a certain perimeter")
            print("3. Determine where a new taxi station should be placed")
            print("4. Exit")

            cmd = input("-> ")

            if cmd == "1":
                id = input("The id of the new address: ")
                name = input("The name of the street: ")
                number = input("The number of the street: ")
                x = input("X coordinate: ")
                y = input("Y coordinate: ")

                try:
                    self.__service.add_address(id, name, number, x, y)
                except ValueError as ve:
                    print(ve)

            elif cmd == "2":
                x = input("X: ")
                y = input("Y: ")
                d = input("Distance: ")

                adr = self.__service.get_all_adresses_with_distance(x, y, d)
                for a in adr:
                    print(a[0], end=" ")
                    print(f"has the distance = {a[1]}")

            elif cmd == "3":
                try:
                    x, y = self.__service.determine_new_taxi_station()
                    print("X: " + str(x)  + " and Y: " + str(y))
                except ValueError as ve:
                    print(ve)

            elif cmd == "4":
                break

            else:
                print("Bad command!")
