from math import sqrt

from src.domain import Address
from src.repository import AddressesRepo


class AddressesService:
    def __init__(self):
        self.__repo = AddressesRepo()

    def add_address(self, id, name, number, x, y):
        try:
            id = int(id)
        except:
            raise ValueError("The id must be a number!")

        if id < 0:
            raise ValueError("The id must be a positive integer!")

        try:
            number = int(number)
        except:
            raise ValueError("The number must be a positive integer!")

        try:
            x = int(x)
            y = int(y)
        except:
            raise ValueError("The coordinates must be integers!")

        self.__repo.add_address(Address(id, name, number, x, y))

    def get_all_adresses_with_distance(self, x, y, d):
        """
        This function returns the list of all addresses(in increasing order) that are in a specific perimeter
        given by the (x, y) coordinates and distance d
        :param x: the x coordinate
        :param y: the y coordinate
        :param d: the distance
        :return: the sorted list of addresses
        """
        try:
            x = int(x)
            y = int(y)
        except:
            raise ValueError("The coordinates must be integers!")

        try:
            d = int(d)
        except:
            raise ValueError("The distance must be a positive integer!")

        adr = self.get_addresses()
        a = []
        for ad in adr:
            X = ad.x - x
            Y = ad.y - y
            p = sqrt(X * X + Y * Y)
            if d > p:
                a.append([ad, p])

        self.sort_by_distance(a)
        return a

    def sort_by_distance(self, l):
        """
        This function sorts a list in increasing order by the distance of each address
        :param l: the list of addresses
        :return: None
        """
        for i in range(len(l)):
            for j in range(i + 1, len(l)):
                if l[i][1] > l[j][1]:
                    l[i], l[j] = l[j], l[i]

    def determine_new_taxi_station(self):
        return self.__repo.determine_new_taxi_station()

    def get_addresses(self):
        """
        Returns all the addresses that are in the system
        :return: the list of addresses
        """
        return self.__repo.get_addresses()

