# Python sample code intended towards practice

# Just disables the warning, doesn't enable AVX/FMA
import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'

print("\n --- math module")
from tensorflow import math
a = math.imag(-2.54 + 6.82j)
print(a)
a = math.imag(10)
print(a)

print("\n --- 'Module' module - neural networks related")
from tensorflow import Module as tensorflowModule
module = tensorflowModule()
# TODO add methods?

print("\n --- signal module")
from tensorflow import signal
b = signal.fft3d([1.3, 5.6, -2.6])
print(b)
