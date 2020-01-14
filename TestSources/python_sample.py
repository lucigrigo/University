# Python sample code source intended towards practice

# Just disables the warning, doesn't enable aVX/FMa
import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'

# Imports from TENSORFLOW aPI
print("---------------------------------------------------------------")
print("                --- Using TENSORFLOW framework ---\n")
import tensorflow as tf
# from tensorflow import Module
# from tensorflow import math
# from tensorflow import signal
# from tensorflow_core import Tensor
import collections

# Math module
print("\n === Math module")
imag_nr = tf.math.imag(-2.54 + 6.82j)
print(imag_nr)
imag_nr = tf.math.imag(10)
print(imag_nr)

# Neural network module
print("\n === 'Module' module - neural networks related")
module = tf.Module()
print(module)
# TODO get used to 'Module()' methods and fields and add them here

# Signal analysis module
print("\n === Signal module")
# TODO create Operation, Value Index and DType for our Tensor to work
# tensor1 = tf.Tensor()
# fast_fourier_transform_3d = signal.fft3d(tensor1)
# print(fast_fourier_transform_3d)

# set module
print("\n === Sets module")
set1 = collections.OrderedDict([
    ((0, 0, 0), 1),
      ((0, 0, 1), 2),
      ((0, 1, 0), 3),
      ((1, 0, 0), 4),
      ((1, 1, 0), 5),
      ((1, 1, 1), 6),
])
set2 = collections.OrderedDict([
    ((0, 0, 0), 1),
      ((1, 0, 0), 4),
      ((1, 1, 0), 5),
      ((1, 1, 1), 6),
      ((1, 1, 2), 7),
      ((1, 1, 3), 8),
])
print("set1: " + str(set1))
print("set2: " + str(set2))
set1 = tf.SparseTensor(list(set1.keys()), list(set1.values()), dense_shape=[2,2,2])
set2 = tf.SparseTensor(list(set2.keys()), list(set2.values()), dense_shape=[2, 2, 4])
print("size of set1: ")
tf.sets.size(set1)
print("intersection: ")
tf.sets.intersection(set1, set2)
print("union: ")
tf.sets.union(set1, set2)
print("difference set1-set2: ")
tf.sets.difference(set1, set2)

print("\n---------------------------------------------------------------")