from __future__ import absolute_import, division, print_function, unicode_literals

# TensorFlow e tf.keras
import tensorflow as tf
from tensorflow import keras

# Bibliotecas de ajuda
import numpy as np
import matplotlib.pyplot as plt

import os

print(tf.__version__)

dir_path = os.getcwd()
dataset = np.loadtxt(dir_path+'\drugsComTrain_raw.tsv', delimiter=",")

(train_data, train_labels), (test_data, test_labels) = dataset.load_data()