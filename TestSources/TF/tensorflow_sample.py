# Python sample code source intended towards practice

# Just disables the warning, doesn't enable aVX/FMa
import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'

# Imports from TENSORFLOW API
print("---------------------------------------------------------------")
print("                --- Using TENSORFLOW framework ---\n")
print("---------------------------------------------------------------")
import collections
import tensorflow as tf

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

# Sets module
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
set1 = tf.SparseTensor(list(set1.keys()), list(set1.values()), dense_shape=[2, 2, 2])
set2 = tf.SparseTensor(list(set2.keys()), list(set2.values()), dense_shape=[2, 2, 4])
print("~~~\nsize of set1: ")
print(tf.sets.size(set1))
print("~~~\nintersection: ")
print(tf.sets.intersection(set1, set2))
print("~~~\nunion: ")
print(tf.sets.union(set1, set2))
print("~~~\ndifference set1-set2: ")
print(tf.sets.difference(set1, set2))

# Keras module (high-level API)
print("\n === Keras module")
sequential_model = tf.keras.models.Sequential()
sequential_model.add(tf.keras.layers.Dense(16, input_shape = (100, )))
print(sequential_model.weights)

print("\nexample of a tensor:")
x1 = tf.constant([[-2.25 + 4.75j, -5 + 1j], [-3.25 + 5.75j, 3.23 - 2j]])
print(x1)
print("its absolute value is:")
x1_abs = tf.abs(x1)
print(x1_abs)
print("its shape is:")
print(x1.shape)

# Constructing custom Model() subclass from keras Model()
class MyModel(tf.keras.Model):
  def __init__(self):
    super(MyModel, self).__init__()
    self.dense1 = tf.keras.layers.Dense(4, activation=tf.nn.relu)
    self.dense2 = tf.keras.layers.Dense(5, activation=tf.nn.softmax)

  def call(self, inputs):
    x = self.dense1(inputs)
    return self.dense2(x)

print("\n---------------------------------------------------------------")