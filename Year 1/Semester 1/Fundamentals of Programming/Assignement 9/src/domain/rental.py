from datetime import datetime


class Rental:
    def __init__(self, rental_id: int, book_id: int, client_id: int,
                 rented_date: datetime, returned_date: datetime):
        self.__rental_id = rental_id
        self.__book_id = book_id
        self.__client_id = client_id
        self.__rented_date = rented_date
        self.__returned_date = returned_date

    @property
    def rental_id(self):
        return self.__rental_id

    @property
    def book_id(self):
        return self.__book_id

    @property
    def client_id(self):
        return self.__client_id

    @property
    def rented_date(self):
        return self.__rented_date

    @property
    def returned_date(self):
        return self.__returned_date

    @rental_id.setter
    def id(self, rentalid: int):
        self.__rental_id = rentalid

    @book_id.setter
    def book_id(self, bookid: int):
        self.__book_id = bookid

    @client_id.setter
    def client_id(self, clientid: int):
        self.__client_id = clientid

    @rented_date.setter
    def rented_date(self, renteddate: datetime):
        self.__rented_date = renteddate

    @returned_date.setter
    def returned_date(self, returneddate: datetime):
        self.__returned_date = returneddate

    def __str__(self):
        return (str(self.id) + " " + str(self.book_id) + " " + str(self.client_id)
                + " " + str(self.rented_date) + " " + str(self.returned_date))


