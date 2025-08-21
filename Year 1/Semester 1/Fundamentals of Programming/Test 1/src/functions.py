def get_name(coffee):
    return coffee["name"]

def get_country(coffee):
    return coffee["country_of_origin"]

def get_price(coffee):
    return coffee["price"]

def set_name(coffee, name):
    coffee["name"] = name

def set_country(coffee, country):
    coffee["country_of_origin"] = country

def set_price(coffee, price):
    coffee["price"] = price

def to_string(coffee):
    price = str(get_price(coffee))
    return get_name(coffee) + " " + get_country(coffee) + " " + price


def add_coffee(l, name, country, price):
    """
    This function adds an element to the list of coffees
    :param l: the list
    :param name: name of the coffe
    :param country: the country of origin
    :param price: the price of the coffe
    :return: None
    """
    try:
        price = float(price)
    except ValueError:
        raise ValueError("The price must be a number!!!")

    if price <= 0:
        raise ValueError("The price must be greater than 0!!!")

    coffee = {
        "name": name,
        "country_of_origin": country,
        "price": price
    }


    l.append(coffee)

def sort_the_coffees(l):
    """
    This function sorts all the coffees alphabetically and if their names are the same it will sort them increasingly by their price
    :param l: the list
    :return: None
    """
    for i in range(len(l) - 1):
        for j in range (i + 1, len(l)):
            if get_country(l[i]) > get_country(l[j]):
                l[i], l[j] = l[j], l[i]

            if get_country(l[i]) == get_country(l[j]) and get_price(l[i]) > get_price(l[j]):
                l[i], l[j] = l[j], l[i]

def filter_coffees(l, country, price):
    """
    This function sorts the list of coffees by the given conditions
    :param l: the list
    :param country: the country
    :param price: the price
    :return: bool, if found or not a coffee
    """
    with_country = True
    with_price = True
    found = False
    if country == "":
        with_country = False

    if price == "":
        with_price = False
    else:
        price = float(price)

    if with_price == True and with_country == True:
        for i in range(len(l) - 1, -1, -1):
            if get_country(l[i]) != country or get_price(l[i]) > price:
                l.pop(i)
            elif get_country(l[i]) == country and get_price(l[i]) <= price:
                found = True

    elif with_price == False and with_country == True:
        for i in range(len(l) - 1, -1, -1):
            if get_country(l[i]) != country:
                l.pop(i)
            elif get_country(l[i]) == country:
                found = True

    elif with_price == True and with_country == False:
        for i in range(len(l) - 1, -1, -1):
            if get_price(l[i]) > price:
                l.pop(i)
            elif get_price(l[i]) <= price:
                found = True

    return found

def delete_coffee(l, country):
    for i in range(len(l) - 1, -1, -1):
        if get_country(l[i]) == country:
            l.pop(i)

# Tests
def test_add_coffee():
    l = []
    add_coffee(l, "cafea1", "Romania", "123.5")

    assert get_name(l[0]) == "cafea1"
    assert get_country(l[0]) == "Romania"
    assert get_price(l[0]) == 123.5

    try:
        add_coffee(l, "cafea2", "France", "-123.5")
        assert False
    except ValueError:
        assert True

def initial_items(l):
    add_coffee(l, "cafea1", "Romania", "120")
    add_coffee(l, "cafea2", "France", "12")
    add_coffee(l, "cafea3", "France", "15")
    add_coffee(l, "cafea4", "Germany", "17")
    add_coffee(l, "cafea5", "France", "10")

def run_tests():
    test_add_coffee()