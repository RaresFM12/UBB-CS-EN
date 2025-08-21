import pickle

from src.repository.rental_memory_repo import RentalMemoryRepository


class RentalBinaryRepo(RentalMemoryRepository):
    def __init__(self, file_name = "rental.bin"):
        super().__init__()
        self.__most_rented_books = {}
        self.__most_active_clients = {}
        self.__rental_availability = {}
        self.__file_name = file_name
        self._load_file()

    def erase_data(self):
        super().erase_data()
        open(self.__file_name, "w").close()

    def _load_file(self):
        try:
            bin_input_file = open(self.__file_name, 'rb')
            books_from_bin_file = pickle.load(bin_input_file)
        except EOFError:
            return

        for new_book in books_from_bin_file:
            super().add(new_book)
            if new_book.book_id in self.__most_rented_books.keys():
                self.__most_rented_books[new_book.book_id] += 1
            else:
                self.__most_rented_books[new_book.book_id] = 1

            if new_book.client_id in self.__most_active_clients.keys():
                self.__most_active_clients[new_book.client_id] += 1
            else:
                self.__most_active_clients[new_book.client_id] = 1

        bin_input_file.close()

    def _save_file(self):
        bin_out_file = open(self.__file_name, "wb")
        pickle.dump(super().display_rented_books(), bin_out_file)
        bin_out_file.close()

    def rent_a_book(self, object):
        """
        This function adds a book to the rented list
        :param object: the book
        :return: None
        """
        super().rent_a_book(object)
        if object.book_id in self.__most_rented_books.keys():
            self.__most_rented_books[object.book_id] += 1
        else:
            self.__most_rented_books[object.book_id] = 1

        if object.client_id in self.__most_active_clients.keys():
            self.__most_active_clients[object.client_id] += 1
        else:
            self.__most_active_clients[object.client_id] = 1

        self._save_file()

    def get_most_active_clients_keys(self):
        return list(self.__most_active_clients.keys())

    def get_most_active_clients_values(self):
        return list(self.__most_active_clients.values())

    def get_most_rented_books_keys(self):
        return list(self.__most_rented_books.keys())

    def get_most_rented_books_values(self):
        return list(self.__most_rented_books.values())

    def delete_rental_availability(self, id):
        super().delete_rental_availability(id)

    def return_avalability(self, id):
        if id in self.__rental_availability.keys():
            return self.__rental_availability[id]
        return False

    def set_availability_true(self, id):
        self.__rental_availability[id] = True

    def set_availability_false(self, id):
        self.__rental_availability[id] = False

    def remove_rental(self, id):
        del self.__most_rented_books[id]
        super().remove_rental(id)

    def display_rented_books(self):
        return super().display_rented_books()

    def get_all_ids(self):
        return super().get_all_ids()