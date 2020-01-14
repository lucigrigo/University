# Python sample code source intended towards practice

# Just disables the warning, doesn't enable AVX/FMA
import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'

# imports from TENSORFLOW API
print("---------------------------------------------------------------")
print("                --- Using TENSORFLOW framework ---\n")
import tensorflow as tf
# from tensorflow import Module
# from tensorflow import math
# from tensorflow import signal
# from tensorflow_core import Tensor

# Math module
print("\n === Math module")
a = tf.math.imag(-2.54 + 6.82j)
print(a)
a = tf.math.imag(10)
print(a)

# Neural network module
print("\n === 'Module' module - neural networks related")
module = tf.Module()
print(module)
# TODO get used to 'Module()' methods and fields and add them here

# signal analysis module
print("\n === Signal module")
# TODO create Operation, Value Index and DType for our Tensor to work
# c = tf.Tensor()
# b = signal.fft3d(c)
# print(b)

print("\n---------------------------------------------------------------")