class Book:
    def __init__(self, book_id: int, title: str, author: str):
        self.__book_id = book_id
        self.__title = title
        self.__author = author

    @property
    def id(self):
        return self.__book_id

    @property
    def title(self):
        return self.__title

    @property
    def author(self):
        return self.__author

    @id.setter
    def id(self, book_id: int):
        self.__book_id = book_id

    @title.setter
    def title(self, book_title: str):
        self.__title = book_title

    @author.setter
    def author(self, book_author: str):
        self.__author = book_author

    def __str__(self):
        return "\"" + self.title + "\"" + " by " + self.author + " has the id " + str(self.id)

