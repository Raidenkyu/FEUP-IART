import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from pathlib import Path
from sklearn.tree import DecisionTreeClassifier
from sklearn.metrics import classification_report, confusion_matrix


def getDataset(filename, columns):
    folderPath = Path("res/")
    filePath = str(folderPath / filename)
    dataset = pd.read_csv(filePath, names=columns)

    X = dataset.iloc[:, :-1].values
    y = dataset.iloc[:, 116].values

    return X, y, dataset


def main():
    trainFile = 'dota2Train.csv'
    testFile = 'dota2Test.csv'

    # Assign colum names to the dataset
    columns = ['won_game', 'location_id', 'game_mode', 'game_type']
    for i in range(1, 114):
        columns.append('hero'+str(i))

    x_train, y_train, train_dataset = getDataset(trainFile, columns)
    x_test, y_test, test_dataset = getDataset(testFile, columns)

    classifier = DecisionTreeClassifier()
    classifier.fit(x_train, y_train)

    y_pred = classifier.predict(x_test)

    print(confusion_matrix(y_test, y_pred))
    print(classification_report(y_test, y_pred))


if __name__ == "__main__":
    main()
