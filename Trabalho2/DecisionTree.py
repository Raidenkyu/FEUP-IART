import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from pathlib import Path
from sklearn.tree import DecisionTreeClassifier
from sklearn.metrics import classification_report, confusion_matrix
import time


def getDataset(filename, columns):
    dataset = pd.read_csv(filename, names=columns)

    y = dataset.iloc[:, 0].values
    X = dataset.iloc[:, 1:116].values

    return X, y, dataset


def DecisionTree(window, trainFile, testFile):

    # Assign colum names to the dataset
    columns = ['won_game', 'location_id', 'game_mode', 'game_type']
    for i in range(1, 114):
        columns.append('hero'+str(i))

    x_train, y_train, train_dataset = getDataset(trainFile, columns)
    x_test, y_test, test_dataset = getDataset(testFile, columns)

    classifier = DecisionTreeClassifier()
    window.print("Start Training")
    start = time.time()
    classifier.fit(x_train, y_train)
    window.print("Training finished in {} seconds".format(time.time()-start))

    y_pred = classifier.predict(x_test)

    for i in range(0, len(y_pred)):
        window.print("Predicted: {}     Real: {}".format(
            y_pred[i], y_test[i]))

    window.print(str(confusion_matrix(y_test, y_pred)))
    window.print(str(classification_report(y_test, y_pred)))
