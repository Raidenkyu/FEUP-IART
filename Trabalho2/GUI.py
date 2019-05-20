import random
from tkinter import Tk, Label, Button, Entry, StringVar, DISABLED, NORMAL, END, W, E, LEFT


class MainWindow:
    def __init__(self):
        self.master = Tk()

        self.master.geometry("500x500")
        self.master.resizable(0, 0)

        self.master.title("Deep Learning")
        self.title_label = Label(
            self.master, text="Dota2 Victory prevision App")
        self.title_label.pack()
        self.train_file_label = Label(
            self.master, text="Train File Path", justify=LEFT)
        self.train_file_label.pack()

        self.NeuralNetworkButton = Button(
            self.master, text="Neural Network", command=self.NeuralNetwork)
        self.NeuralNetworkButton.pack()

        self.KNNButton = Button(
            self.master, text="KNN", command=self.KNN)
        self.KNNButton.pack()

        self.C4dot5Button = Button(
            self.master, text="C4.5", command=self.C4dot5)
        self.C4dot5Button.pack()

    def run(self):
        self.master.mainloop()

    def NeuralNetwork(self):
        print("NeuralNetwork")

    def KNN(self):
        print("KNN")

    def C4dot5(self):
        print("c4.5")


def main():
    app = MainWindow()
    app.run()


if __name__ == "__main__":
    main()
