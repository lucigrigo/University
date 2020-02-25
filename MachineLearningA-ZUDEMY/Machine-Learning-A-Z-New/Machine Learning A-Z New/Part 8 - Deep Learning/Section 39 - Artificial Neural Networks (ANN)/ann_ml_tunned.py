# Artificial Neural Networks

# Libraries/Modules Used: Theano, Tensorflow, Keras

# Solving system issue on MACOS
from sklearn.model_selection import GridSearchCV
from sklearn.model_selection import cross_val_score
from keras.wrappers.scikit_learn import KerasClassifier
from keras.layers import Dropout
from keras.layers import Dense
from keras.models import Sequential
import keras
from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import LabelEncoder, OneHotEncoder
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import os
os.environ['KMP_DUPLICATE_LIB_OK'] = 'True'

# Part 1 - Data Preprocessing

# Importing  libraries

# Importing the dataset
dataset = pd.read_csv('Churn_Modelling.csv')
X = dataset.iloc[:, 3: 13].values
y = dataset.iloc[:, 13].values

# Encoding categorical data
labelencoder_X_1 = LabelEncoder()
X[:, 1] = labelencoder_X_1.fit_transform(X[:, 1])
labelencoder_X_2 = LabelEncoder()
X[:, 2] = labelencoder_X_2.fit_transform(X[:, 2])
onehotencoder = OneHotEncoder(categorical_features=[1])
X = onehotencoder.fit_transform(X).toarray()
X = X[:, 1:]  # dummy variable trap removal

# Splitting the dataset into the Training set and Test set
X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=0)

# Feature Scaling
sc_X = StandardScaler()
X_train = sc_X.fit_transform(X_train)
X_test = sc_X.transform(X_test)

# Part 2 - Creating the ANN

# Importing libraries

# # ANN initialisation
# classifier = Sequential()

# # Adding the input layer and the first hidden layer with dropout
# classifier.add(Dense(units = 6, kernel_initializer = 'uniform', activation = 'relu', input_shape = (11,)))
# classifier.add(Dropout(p = 0.1))

# # Adding the second hidden layer with dropout
# classifier.add(Dense(units = 6, kernel_initializer = 'uniform', activation = 'relu'))
# classifier.add(Dropout(p = 0.1))

# # Adding the output layer
# classifier.add(Dense(units = 1, kernel_initializer = 'uniform', activation = 'sigmoid'))

# # Compiling the ANN
# classifier.compile(optimizer = 'adam', loss = 'binary_crossentropy', metrics = ['accuracy'])

# # Fitting the ANN to the Training set
# classifier.fit(X_train, y_train, batch_size = 10, epochs = 100)

# ### Part 3 - Making the predictions and evaluating the model

# # Predicting the test set results
# y_pred = classifier.predict(X_test)
# y_pred = (y_pred > 0.5)

# # Predicting specific customer possiblity to leave
# customer = np.array([[0.0, 0, 600, 1, 40, 3, 60000, 2, 1, 1, 50000]])
# customer_prediction = classifier.predict(customer)
# customer_prediction = (customer_prediction > 0.5)
# print("\nWill the customer leave the bank? ")
# print(customer_prediction)

# # Making the Confusion Matrix
# from sklearn.metrics import confusion_matrix
# cm = confusion_matrix(y_test, y_pred)

# Part 4 - Evaluating, Improving and Tuning the ANN

# Evaluating the ANN
# using k-fold cross validation


def build_classifier():
    classifier = Sequential()
    classifier.add(Dense(units=6, kernel_initializer='uniform',
                         activation='relu', input_shape=(11,)))
    classifier.add(
        Dense(units=6, kernel_initializer='uniform', activation='relu'))
    classifier.add(
        Dense(units=1, kernel_initializer='uniform', activation='sigmoid'))
    classifier.compile(
        optimizer='adam', loss='binary_crossentropy', metrics=['accuracy'])
    return classifier


classifier = KerasClassifier(
    build_fn=build_classifier, batch_size=9, epochs=100)
accuracies = cross_val_score(
    estimator=classifier, X=X_train, y=y_train, cv=10, n_jobs=-1)
mean = accuracies.mean()
variance = accuracies.std()
print("Mean=" + str(mean))
print("Variance=" + str(variance))

# Improving the ANN
# Dropout Regularization to reduce overfitting if needed

# Tunning the ANN


def build_classifier(optimizer):
    classifier = Sequential()
    classifier.add(Dense(units=6, kernel_initializer='uniform',
                         activation='relu', input_shape=(11,)))
    classifier.add(
        Dense(units=6, kernel_initializer='uniform', activation='relu'))
    classifier.add(
        Dense(units=1, kernel_initializer='uniform', activation='sigmoid'))
    classifier.compile(optimizer=optimizer,
                       loss='binary_crossentropy', metrics=['accuracy'])
    return classifier


classifier = KerasClassifier(build_fn=build_classifier)
parameters = {'batch_size': [25, 32],
              'epochs': [100, 500],
              'optimizer': ['adam', 'rmsprop']}
grid_search = GridSearchCV(estimator=classifier,
                           param_grid=parameters,
                           scoring='accuracy',
                           cv=10)
grid_search = grid_search.fit(X_train, y_test)
best_param = grid_search.best_params_
best_acc = grid_search.best_score_
