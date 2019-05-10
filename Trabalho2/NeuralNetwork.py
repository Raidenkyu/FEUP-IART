from __future__ import absolute_import, division, print_function, unicode_literals

# TensorFlow e tf.keras
import tensorflow as tf
from tensorflow import keras

# Bibliotecas de ajuda
import numpy as np
import matplotlib.pyplot as plt

import os


tf.enable_eager_execution()

os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'


def parseLine(drugNum, drugName, condition, review, rating, date, usefulCount):
    COLUMNS = ['drugNum', 'drugName', 'condition',
               'review', 'rating',
               'date', 'usefulCount']

    features = dict(
        zip(COLUMNS, [drugNum, drugName, condition, review, rating, date, usefulCount]))

    return features


def parseFile(filename):
    dataset = tf.data.experimental.CsvDataset(
        filenames=filename,
        record_defaults=[0, "", "",
                         "", 0.0, "", 0],
        field_delim="\t",
        header=True)
    return dataset.map(parseLine)


def main():
    print("TensorFlow Version: " + tf.__version__)

    filename = 'drugsComTrain_raw.tsv'

    dataset = parseFile(filename)


'''
    for data in dataset:
        tf.print(data)
'''

main()
