# polynomial regression

# Importing the libraries
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

# Importing the dataset
dataset = pd.read_csv('Position_Salaries.csv')
X = dataset.iloc[:, 1:2].values
y = dataset.iloc[:, 2:3].values

# fitting linear regression to the dataset
from sklearn.linear_model import LinearRegression
linreg = LinearRegression()
linreg.fit(X, y)

# fitting polynomial regression to the dataset
from sklearn.preprocessing import PolynomialFeatures
polyreg = PolynomialFeatures(degree = 3)
X_poly = polyreg.fit_transform(X)
linreg2 = LinearRegression()
linreg2.fit(X_poly, y)

# visualising the linear regression results
plt.scatter(X, y, color='red')
plt.plot(X, linreg.predict(X), color='blue')
plt.title('Truth or Bluff (Linear Regression)')
plt.xlabel('Position level')
plt.ylabel('Salary')
plt.show()

# visualising the polynomial regression results
X_grid = np.arange(min(X), max(X), 0.1)
X_grid = X_grid.reshape((len(X_grid), 1))
plt.scatter(X, y, color='red')
plt.plot(X_grid, linreg2.predict(polyreg.fit_transform(X_grid)), color='blue')
plt.title('Truth or Bluff (Polynomial Regression)')
plt.xlabel('Position level')
plt.ylabel('Salary')
plt.show()

# predicting a new result with linear regression
linreg.predict([[6.5]])

# predicting a new result with polynomial regression
linreg2.predict(polyreg.fit_transform([[6.5]]))
