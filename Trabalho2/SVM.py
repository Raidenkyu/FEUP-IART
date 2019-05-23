import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.svm import SVC
from sklearn.metrics import classification_report, confusion_matrix
from pathlib import Path


def svm_main(window, trainPath, testPath):

    bankdata_train = pd.read_csv(trainPath)
    bankdata_test = pd.read_csv(trainPath)

    bankdata_train.shape
    bankdata_test.shape

    bankdata_train.head()
    bankdata_test.head()

    X_train = bankdata_train.drop('Class', axis=1)
    y_train = bankdata_train['Class']

    X_test = bankdata_test.drop('Class', axis=1)
    y_test = bankdata_test['Class']

    svclassifier = SVC(kernel='linear')
    svclassifier.fit(X_train, y_train)

    y_pred = svclassifier.predict(X_test)

    window.print(str(confusion_matrix(y_test, y_pred)))
    window.print(str(classification_report(y_test, y_pred)))
