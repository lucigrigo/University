"""
Constants used in the test generating script
"""
TESTS_DIR = "../tests/"

# Products related constants
COFFEE_NAMES = ["Arabica", "Robusta", "Brasil", "Ethiopia", "Columbia", "Costa Rica",
                "Indonezia", "Decaf"]
ROAST_LEVEL = ["DARK", "MEDIUM", "LIGHT"]
MAX_ACIDITY = 5.1
MIN_ACIDITY = 4.9

TEA_NAMES_TYPES = {"Earl Grey": "Black",
                   "English Breakfast": "Black",
                   "White Peach": "White",
                   "Summer time": "Herbal",
                   "Linden": "Herbal",
                   "Lavender": "Herbal",
                   "Camomile": "Herbal",
                   "Winter story": "Black",
                   "Cactus fig": "Green",
                   "Pai Mu Tan": "White",
                   "China Oolong": "Oolong",
                   "Vietnam Oolong": "Oolong",
                   "Milky Oolong": "Oolong",
                   "Jasmine": "Green",
                   "Wild Cherry": "Black"
                   }

# Naming/ids related constants
PRODUCER_NAME_PREFIX = "prod"
CONSUMER_NAME_PREFIX = "cons"
PRODUCT_PREFIX = "id"
ADD_TO_CART_OP = "add"
REMOVE_FROM_CART_OP = "remove"

# Default values
DEFAULT_NUM_PRODUCERS = 3
DEFAULT_NUM_CONSUMERS = 5
DEFAULT_NUM_PRODUCTS = 7
DEFAULT_MARKETPLACE_QUEUE_SIZE = 8
DEFAULT_MIN_NUMBER_CARTS_PER_CONSUMER = 1
DEFAULT_MAX_NUMBER_CARTS_PER_CONSUMER = 3

# Input arguments names for the test_generator script
ARG_TEST_NAME = "test_name"
ARG_PRODUCERS = "producers"
ARG_CONSUMERS = "consumers"
ARG_PRODUCTS = "products"
ARG_MIN_CARTS = "min_carts"
ARG_MAX_CARTS = "max_carts"
ARG_MARKETPLACE_Q = "marketplace_q"
ARG_IS_BASIC = "is_basic"
ARG_SUPPORTS_REMOVAL = "supports_removal"
