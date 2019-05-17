from __future__ import absolute_import, division, print_function, unicode_literals

# TensorFlow e tf.keras
import tensorflow as tf
from tensorflow import keras
from sklearn import preprocessing
# Bibliotecas de ajuda
import numpy as np
import matplotlib.pyplot as plt
from pathlib import Path

import os

loss_object = tf.keras.losses.SparseCategoricalCrossentropy(
    from_logits=True)

os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'


def getDatabase(datasetFile, columns, label):
    folderPath = Path("res/")

    filePath = str(folderPath / datasetFile)

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
    # model.compile(loss='categorical_crossentropy',
    #             optimizer='adam', metrics=['accuracy'])

    return model


def loss(model, x, y):

    y_ = model(x)

    return loss_object(y_true=y, y_pred=y_)


def grad(model, inputs, targets):
    with tf.GradientTape() as tape:
        loss_value = loss(model, inputs, targets)
    return loss_value, tape.gradient(loss_value, model.trainable_variables)


def main():
    print("TensorFlow Version: " + tf.__version__)

    trainFile = 'dota2Train.csv'
    testFile = 'dota2Test.csv'

    columns = ['won_game', 'location_id', 'game_mode', 'game_type']

    for i in range(1, 114):
        columns.append('hero'+str(i))

    label = columns[0]
    features = columns.copy()
    features.pop(0)

    class_values = [-1, 1]

    train_dataset = getDatabase(trainFile, columns, label)
    train_dataset = train_dataset.map(pack_features_vector)

    model = getModel()

    optimizer = tf.keras.optimizers.Adam(learning_rate=0.01)

    # keep results for plotting
    train_loss_results = []
    train_accuracy_results = []

    num_epochs = 201

    features, labels = next(iter(train_dataset))
    le = preprocessing.LabelEncoder()
    le.fit(labels)

    for epoch in range(num_epochs):
        epoch_loss_avg = tf.keras.metrics.Mean()
        epoch_accuracy = tf.keras.metrics.SparseCategoricalAccuracy()

        # Training loop - using batches of 32
        for x, y in train_dataset:
            # Optimize the model
            y = le.transform(y)
            loss_value, grads = grad(model, x, y)
            optimizer.apply_gradients(zip(grads, model.trainable_variables))

            # Track progress
            epoch_loss_avg(loss_value)  # add current batch loss
            # compare predicted label to actual label
            epoch_accuracy(y, model(x))

        # end epoch
        # train_loss_results.append(epoch_loss_avg.result())
        train_accuracy_results.append(epoch_accuracy.result())

        if epoch % 50 == 0:
            print("Epoch {:03d}: Loss: {:.3f}, Accuracy: {:.3%}".format(epoch,
                                                                        epoch_loss_avg.result(),
                                                                        epoch_accuracy.result()))


if __name__ == "__main__":
    main()
