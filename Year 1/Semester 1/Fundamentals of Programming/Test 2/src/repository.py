from src.domain import Address


class AddressesRepo:
    def __init__(self):
        self.__data = []
        self.__taxi_stations = []
        self.__file_name = "locations.txt"
        self.load_file()

    def load_file(self):
        lines_from_text_file = []
        try:
            test_file_input = open(self.__file_name, "rt")
            lines_from_text_file = test_file_input.readlines()
            test_file_input.close()
        except IOError:
            pass

        for line in lines_from_text_file:
            current_line = line.split(", ")
            new_adr = Address(int(current_line[0].strip()), current_line[1].strip(), int(current_line[2].strip()), int(current_line[3].strip()), int(current_line[4].strip()))
            self.add_address(new_adr)

    def _save_file(self):
        text_output_file = open(self.__file_name, "wt")
        for adr in self.get_addresses():
            adr_string = str(adr.id) + ", " + adr.name + ", " + str(adr.number) + ", " + str(adr.x) + ", " + str(adr.y) + "\n"
            text_output_file.write(adr_string)

        text_output_file.close()

    def get_addresses(self):
        """
        Returns all the addresses that are in the system
        :return: the addresses
        """
        return self.__data

    def add_address(self, adr: Address):
        if self.id_already_exists(adr.id) == True:
            raise ValueError("This id is already in!")

        if len(adr.name) < 3:
            raise ValueError("The name must contain at least 3 letters!")

        self.__data.append(adr)
        self._save_file()

    def id_already_exists(self, id):
        for adr in self.__data:
            if adr.id == id:
                return True

        return False

    def determine_new_taxi_station(self):
        X = 0
        Y = 0
        for i in self.__data:
            X += i.x
            Y += i.y

        X /= len(self.__data)
        Y /= len(self.__data)

        x1 = int(X)
        y1 = int(Y)

        if X - x1 < (x1 + 1) - X:
            X = x1
        else:
            X = x1 + 1

        if Y - y1 < (y1 + 1) - Y:
            Y = y1
        else:
            Y = y1 + 1

        if self.already_in_station_list(X, Y):
            raise ValueError("There is already a station!!!")
        else:
            self.__taxi_stations.append([X, Y])
            return X, Y


    def already_in_station_list(self, x, y):
        for i in self.__taxi_stations:
            if i[0] == x and i[1] == y:
                return True

        return False



