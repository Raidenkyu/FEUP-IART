import numpy as np  
import matplotlib.pyplot as plt  
import pandas as pd  

from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler 
from sklearn.neighbors import KNeighborsClassifier   
from sklearn.metrics import classification_report, confusion_matrix  

import tensorflow as tf
from tensorflow import keras

from pathlib import Path

def knn_main(window, trainPath, testPath):
    window.print("TensorFlow Version: " + tf.__version__)


    # Assign colum names to the dataset
    columns = ['won_game', 'location_id', 'game_mode', 'game_type']
    for i in range(1, 114):
            columns.append('hero'+str(i))

    train_dataset = pd.read_csv(trainPath, names=columns) 
    test_dataset = pd.read_csv(testPath, names=columns) 

    X_test = test_dataset.iloc[:, :-1].values  
    y_test = test_dataset.iloc[:, 116].values  
    X_train = train_dataset.iloc[:, :-1].values  
    y_train = train_dataset.iloc[:, 116].values    

    scaler = StandardScaler()  
    scaler.fit(X_train)

    X_train = scaler.transform(X_train)  
    X_test = scaler.transform(X_test)  
    classifier = KNeighborsClassifier(n_neighbors=5)  
    classifier.fit(X_train, y_train)  

    y_pred = classifier.predict(X_test)  

    print(confusion_matrix(y_test, y_pred))  
    print(classification_report(y_test, y_pred)) 

    error = []

    # Calculating error for K values between 1 and 40
    for i in range(1, 40):  
        knn = KNeighborsClassifier(n_neighbors=i)
        knn.fit(X_train, y_train)
        pred_i = knn.predict(X_test)
        error.append(np.mean(pred_i != y_test))

    plt.figure(figsize=(12, 6))  
    plt.plot(range(1, 40), error, color='red', linestyle='dashed', marker='o',  
            markerfacecolor='blue', markersize=10)
    plt.title('Error Rate K Value')  
    plt.xlabel('K Value')  
    plt.ylabel('Mean Error')  
