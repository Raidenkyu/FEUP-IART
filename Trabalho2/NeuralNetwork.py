from __future__ import absolute_import, division, print_function, unicode_literals

# TensorFlow e tf.keras
import tensorflow as tf
from tensorflow import keras

# Bibliotecas de ajuda
import numpy as np
import matplotlib.pyplot as plt
from pathlib import Path
import time
from sklearn import preprocessing

import os

loss_object = tf.keras.losses.SparseCategoricalCrossentropy(
    from_logits=True)

os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'

STOP_THREAD = False


def getDatabase(filePath, columns, label):
    column_defaults = [tf.float32, tf.float32, tf.float32, tf.float32]

    for i in range(1, 114):
        column_defaults.append(tf.float32)

    batch_size = 32

    dataset = tf.data.experimental.make_csv_dataset(
        filePath,
        batch_size,
        column_names=columns,
        column_defaults=column_defaults,
        label_name=label,
        num_epochs=1)

    dataset = dataset.map(pack_features_vector)
    return dataset


def pack_features_vector(features, labels):
    """Pack the features into a single array."""
    features = tf.stack(list(features.values()), axis=1)
    return features, labels


def getModel():
    model = tf.keras.Sequential([
        tf.keras.layers.Dense(32, activation=tf.nn.relu,
                              input_shape=(116,)),  # input shape required
        tf.keras.layers.Dense(32, activation=tf.nn.relu),
        tf.keras.layers.Dense(2)
    ])

    return model


def loss(model, x, y):

    y_ = model(x)

    return loss_object(y_true=y, y_pred=y_)


def grad(model, inputs, targets):
    with tf.GradientTape() as tape:
        loss_value = loss(model, inputs, targets)
    return loss_value, tape.gradient(loss_value, model.trainable_variables)


def getTransform(labels):
    le = preprocessing.LabelEncoder()
    le.fit(labels)
    return le


def NeuralNetwork(window, trainFile, testFile):
    window.print("TensorFlow Version: " + tf.__version__)

    columns = ['won_game', 'location_id', 'game_mode', 'game_type']

    for i in range(1, 114):
        columns.append('hero'+str(i))

    label = columns[0]
    features = columns.copy()
    features.pop(0)

    class_values = [-1, 1]

    train_dataset = getDatabase(trainFile, columns, label)

    model = getModel()

    optimizer = tf.keras.optimizers.Adam(learning_rate=0.01)

    le = getTransform(class_values)

    # keep results for plotting
    train_loss_results = []
    train_accuracy_results = []

    num_epochs = 201

    start = time.time()
    for epoch in range(num_epochs):
        epoch_loss_avg = tf.keras.metrics.Mean()
        epoch_accuracy = tf.keras.metrics.SparseCategoricalAccuracy()

        # Training loop - using batches of 32
        for x, y in train_dataset:

            if window.STOP_THREAD:
                return

            # Optimize the model
            y = le.transform(y)
            loss_value, grads = grad(model, x, y)
            optimizer.apply_gradients(zip(grads, model.trainable_variables))

            # Track progress
            epoch_loss_avg(loss_value)  # add current batch loss
            # compare predicted label to actual label

            epoch_accuracy(y, model(x))

        # end epoch
        train_loss_results.append(epoch_loss_avg.result())
        train_accuracy_results.append(epoch_accuracy.result())

        window.plot(train_loss_results, train_accuracy_results)

        if epoch % 50 == 0:
            window.print("Epoch {:03d}: Loss: {:.3f}, Accuracy: {:.3%}".format(epoch,
                                                                               epoch_loss_avg.result(),
                                                                               epoch_accuracy.result()))

    end = time.time()
    window.print("Training took {} seconds".format(end-start))

    test_dataset = getDatabase(testFile, columns, label)

    test_accuracy = tf.keras.metrics.Accuracy()

    for (x, y) in test_dataset:
        y = le.transform(y)
        logits = model(x)
        prediction = tf.argmax(logits, axis=1, output_type=tf.int32)
        test_accuracy(prediction, y)

    window.print("Test set accuracy: {:.3%}".format(test_accuracy.result()))
