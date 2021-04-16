"""
Generates JSON files for the homework's tests.

Script input
    - test file name
    - number of producers
    - number of products
    - number of consumers
    - marketplace queue
    - min number of carts per consumer
    - max number of carts per consumer
    - is basic test
    - should have removal operations
"""
import argparse
import random
from json import loads, dumps

from tema.product import *  # pylint: disable=wildcard-import, unused-wildcard-import
from test_utils import *  # pylint: disable=wildcard-import, unused-wildcard-import


def generate_test():
    """
    Generates the test and creates the json, input and output files

    :return: nothing
    """
    random.seed(0)

    cmdline_arguments = parse_input()
    if not sanitize_inputs(cmdline_arguments):
        print("Invalid arguments")
    print(cmdline_arguments)

    products = generate_products(cmdline_arguments[ARG_PRODUCTS])
    producers = generate_producers(cmdline_arguments[ARG_PRODUCERS],
                                   products, cmdline_arguments[ARG_IS_BASIC])

    # eliminate the products not produced

    for prod_id in list(products.keys()):
        if not products[prod_id]["is_produced"]:
            del products[prod_id]

    consumers = generate_consumers(cmdline_arguments[ARG_CONSUMERS],
                                   products,
                                   cmdline_arguments[ARG_MIN_CARTS],
                                   cmdline_arguments[ARG_MAX_CARTS],
                                   cmdline_arguments[ARG_IS_BASIC],
                                   cmdline_arguments[ARG_SUPPORTS_REMOVAL])
    marketplace = generate_marketplace(cmdline_arguments[ARG_MARKETPLACE_Q])

    for prod_id in products.keys():
        del products[prod_id]["is_produced"]

    json_data = {ARG_PRODUCTS: products, ARG_PRODUCERS: producers,
                 ARG_CONSUMERS: consumers, "marketplace": marketplace}

    # write to json test file (tests/{test_name}.json)
    with open(f'{TESTS_DIR}/{cmdline_arguments[ARG_TEST_NAME]}.json', 'w') as json_file:
        print(dumps(json_data, indent=4), file=json_file)

    generate_in_out_test_files(cmdline_arguments[ARG_TEST_NAME])


def parse_input():
    """
    Parses command line input and returns a dictionary with all parameters.
    Default values are used when there is no argument.
    :return: a dict with all the arguments of the script
    """

    parser = argparse.ArgumentParser()
    parser.add_argument(ARG_TEST_NAME, type=str, default="test",
                        help="Test file name (no extension)")
    parser.add_argument(ARG_PRODUCERS, type=int, nargs='?',
                        default=DEFAULT_NUM_PRODUCERS, help="number of producers")
    parser.add_argument(ARG_CONSUMERS, type=int, nargs='?',
                        default=DEFAULT_NUM_CONSUMERS, help="number of consumers")
    parser.add_argument(ARG_PRODUCTS, type=int, nargs='?',
                        default=DEFAULT_NUM_PRODUCTS, help="number of products")
    parser.add_argument(ARG_MARKETPLACE_Q, type=int, nargs='?',
                        default=DEFAULT_MARKETPLACE_QUEUE_SIZE,
                        help="queue size in the marketplace for each producer")
    parser.add_argument(ARG_MIN_CARTS, type=int, nargs='?',
                        default=DEFAULT_MIN_NUMBER_CARTS_PER_CONSUMER,
                        help="minimum number of carts per consumer")
    parser.add_argument(ARG_MAX_CARTS, type=int, nargs='?',
                        default=DEFAULT_MIN_NUMBER_CARTS_PER_CONSUMER,
                        help="minimum number of carts per consumer")
    parser.add_argument(ARG_IS_BASIC, type=bool, nargs='?', default=True,
                        help="True if it is a simple test, False otherwise")
    parser.add_argument(ARG_SUPPORTS_REMOVAL, type=bool, nargs='?', default=True,
                        help="True if the consumer can remove products from cart, False otherwise")

    return parser.parse_args().__dict__


def sanitize_inputs(arguments):
    """
    Simple check of the arguments given to this script, basically checks for positive integers.
    :param arguments: the command line arguments
    :return: True if all checked arguments are ok, False if at least one argument is not ok
    """
    if arguments[ARG_PRODUCERS] > 0 \
            and arguments[ARG_CONSUMERS] > 0 \
            and arguments[ARG_PRODUCTS] > 0 \
            and arguments[ARG_MARKETPLACE_Q] > 0 \
            and arguments[ARG_MIN_CARTS] > 0 \
            and arguments[ARG_MAX_CARTS] > 0 \
            and arguments[ARG_MAX_CARTS] >= arguments[ARG_MIN_CARTS]:
        return True

    return False


def generate_products(count):
    """
    Generates a dict like the one on this example:
     {
        "id1": {
            "product_type": "Coffee",
            "name": "Arabica",
            "price": 10,
            "acidity": 5.1,
            "roast_level": "medium"
        },
        "id2": {
            "product_type": "Tea",
            "name": "Earl Grey",
            "price": 10,
            "type": "Black"
        }
    }
    :param count: the number of products to generate
    :return: a dictionary of products
    """
    # let's have 50% tea, 50% coffee

    products = {}
    # to avoid random duplicates
    coffee_names_copy = list(COFFEE_NAMES)
    tea_list_copy = list(TEA_NAMES_TYPES.keys())

    for i in range(count):
        if i < count / 2:
            product = {"product_type": "Coffee"}
            name = random.choice(coffee_names_copy)
            coffee_names_copy.remove(name)
            product["name"] = name
            product["acidity"] = round(random.uniform(MIN_ACIDITY, MAX_ACIDITY), 2)
            product["roast_level"] = random.choice(ROAST_LEVEL)
        else:
            product = {"product_type": "Tea"}
            tea = random.choice(tea_list_copy)
            product["name"] = tea
            product["type"] = TEA_NAMES_TYPES[tea]
            tea_list_copy.remove(tea)

        product["price"] = random.randint(1, 10)
        product["is_produced"] = False  # temporary field used for generating carts for consumers
        products[PRODUCT_PREFIX + str(i + 1)] = product

    return products


def generate_marketplace(queue_size):
    """
    Generates the marketplace
    :type queue_size: int
    :param queue_size: the queue size for each producer
    :return dict
    :return: a dict representing the markeplace
    """
    marketplace = {"queue_size_per_producer": queue_size}
    return marketplace


def generate_producers(count, products, basic_test):
    """
    Example:
    [{
            "name": "prod1",
            ARG_PRODUCTS: [
                [ "id1", 1, 0.1 ],
                [ "id2", 1, 0.1 ]
            ],
            "republish_wait_time": 0.2
        }]

    :param count: the number of producers to generate
    :param products: all the products that can be delivered to the marketplace
    :param basic_test: True if it's a simple test, False otherwise
    :return: a list with all producers
    """
    # why?
    # scenario: 1 prod 1 cons prod produces 5 type 1 products, 5 type2. Marketplace queue size 5
    # First the producer produces 5 type2 products. Consumer requests type 1 products - deadlock
    max_quantity = 3 if basic_test else 5

    producers = []
    for i in range(count):
        producer = {"name": PRODUCER_NAME_PREFIX + str(i + 1)}

        num_products_per_producer = random.randint(1, len(products.keys()))
        products_to_produce = random.sample(products.keys(), num_products_per_producer)

        products_list = [[x, random.randint(1, max_quantity), round(random.uniform(0.05, 0.4), 2)]
                         for x in products_to_produce]

        producer[ARG_PRODUCTS] = products_list
        producer["republish_wait_time"] = round(random.uniform(0.05, 0.4), 2)
        producers.append(producer)

        # mark the products as produced
        for prod in products_list:
            products[prod[0]]["is_produced"] = True

    return producers


def generate_consumers(count, products, min_cart, max_cart,
                       has_remove_operation=True, basic_test=True):
    """ Example:
    [
        {
            "name": "cons1",
            "retry_wait_time": 0.1,
            "carts": [
                {
                  "ops": [
                    {"type": "add", "prod": "id1", "qty": 2},
                    {"type": "remove", "prod": "id1", "qty": 1}
                  ],
                  "expected_cart": {
                    "id1": 1
                  }
                }
            ]
        }
    ],
    :return: list of consumers
    """
    consumers = []
    max_operations_per_cart = 3 if basic_test else 10
    max_quantity = 5 if basic_test else 10

    for i in range(count):
        consumer = {"name": CONSUMER_NAME_PREFIX + str(i + 1),
                    "retry_wait_time": round(random.uniform(0.05, 0.4), 2)}

        num_carts = random.randint(min_cart, max_cart)
        consumer["carts"] = []

        for _ in range(num_carts):
            num_operations = random.randint(1, max_operations_per_cart)

            print(products.keys(), " ", num_operations)
            if len(products) < num_operations:
                num_operations = len(products)

            product_ids = random.sample(products.keys(), num_operations)
            operations = [{"type": ADD_TO_CART_OP, "product": x,
                           "quantity": random.randint(1, max_quantity)} for x in product_ids]

            # artificially insert 0 or 1 removal operations, aka not all carts will have removals
            if has_remove_operation:
                should_insert_remove_op = random.randint(0, 1)
                if should_insert_remove_op > 0:
                    index = random.randint(0, len(operations)) - 1
                    operations.append({"type": REMOVE_FROM_CART_OP,
                                       "product": operations[index]["product"],
                                       "quantity": random.choice(
                                           range(1, operations[index]["quantity"] + 1))})

            consumer["carts"].append({"ops": operations,
                                      "expected_cart": compute_expected_cart(operations)})

        consumers.append(consumer)
    return consumers


def compute_expected_cart(operations):
    """
    Generates a cart for a consumer based on the given operations
    :param operations: ADD or REMOVE from cart
    :return: a dictionary of actions (operations) representing a consumer's cart
    """
    expected_cart = {}
    for operation in operations:
        product_id = operation["product"]
        quantity = operation["quantity"] * (1 if operation["type"] is ADD_TO_CART_OP else -1)
        expected_cart[product_id] = \
            expected_cart[product_id] + quantity if product_id in expected_cart.keys() else quantity

    for product in list(expected_cart):
        if expected_cart[product] <= 0:
            del expected_cart[product]

    return expected_cart


def generate_in_out_test_files(test_name):
    """
    Creates two files for the given test: the input file and the reference output file
    :param test_name: the name (excluding the extension) given to all the files of the test
    :return: nothing
    """
    filename = f'{TESTS_DIR}/{test_name}.json'

    with open(filename) as json_file:
        conf = loads(json_file.read())

    # turn product definitions into actual products
    products = {}
    for k, prod_dict in conf['products'].items():
        params = {k: v for k, v in prod_dict.items() if k != 'product_type'}
        products[k] = globals()[prod_dict['product_type']](**params)

    # turn product ids into products in consumer order lists and expected carts
    for consumer in conf['consumers']:
        for cart in consumer['carts']:
            cart['expected_cart'] = {products[k]: v
                                     for k, v
                                     in cart['expected_cart'].items()}

    lines = []
    for consumer in conf['consumers']:
        print("consumer" + str(consumer))
        for cart in consumer['carts']:
            for product, count in cart['expected_cart'].items():
                lines += ([f'{consumer["name"]} bought {product}'] * count)

    # write to output file (tests/{test_name}.out)
    with open(f'{TESTS_DIR}/{test_name}.ref.out', 'w') as output_file:
        lines.sort()
        print('\n'.join(lines), file=output_file)

    for consumer in conf['consumers']:
        consumer['carts'] = [d['ops'] for d in consumer['carts']]

    # write to input file (tests/{test_name}.in)
    with open(f'{TESTS_DIR}/{test_name}.in', 'w') as input_file:
        print(dumps(conf, indent=4), file=input_file)


if __name__ == "__main__":
    generate_test()
