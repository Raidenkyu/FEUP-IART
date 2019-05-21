import threading
from matplotlib.figure import Figure
from matplotlib.axes import Axes
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from NeuralNetwork import NeuralNetwork
from KNearestNeighbor import knn_main
from SVM import svm_main
from tkinter import Tk, Label, Button, Entry, StringVar, DISABLED, NORMAL, END, W, E, LEFT, filedialog, Toplevel, Text
import random
import matplotlib
matplotlib.use('TkAgg')


class MainWindow:
    def __init__(self):
        self.master = Tk()

        self.master.geometry("500x300")
        self.master.resizable(0, 0)

        self.master.title("Deep Learning")
        self.title_label = Label(
            self.master, text="Dota2 Victory prevision App")
        self.title_label.grid(row=0, column=1)

        self.train_file_label = Label(
            self.master, text="Train File Path", justify=LEFT)
        self.train_file_label.grid(row=1)

        self.train_file_path = Entry(self.master)
        self.train_file_path.grid(row=2, column=0)

        self.train_file_browse = Button(
            self.master, text="Browser", command=self.browseTrain)

        self.train_file_browse.grid(row=2, column=1)

        self.test_file_label = Label(
            self.master, text="Test File Path", justify=LEFT)
        self.test_file_label.grid(row=3)

        self.test_file_path = Entry(self.master)
        self.test_file_path.grid(row=4, column=0)

        self.test_file_browse = Button(
            self.master, text="Browser", command=self.browseTest)

        self.test_file_browse.grid(row=4, column=1)

        self.NeuralNetworkButton = Button(
            self.master, text="Neural Network", command=self.startNeuralNetwork)
        self.NeuralNetworkButton.grid(row=5, column=1)

        self.KNNButton = Button(
            self.master, text="KNN", command=self.KNN)
        self.KNNButton.grid(row=6, column=1)

        self.SVMButton = Button(
            self.master, text="SVM", command=self.KNN)
        self.SVMButton.grid(row=7, column=1)

        self.C4dot5Button = Button(
            self.master, text="C4.5", command=self.C4dot5)
        self.C4dot5Button.grid(row=8, column=1)

    def run(self):
        self.master.mainloop()


    def startNeuralNetwork(self):
        win = AlgorithmWindow(self)
        win.startTask(threading.Thread(target=NeuralNetwork, args=(win, self.train_file_path.get(),
                                                                   self.test_file_path.get())))

    def KNN(self):
        win = AlgorithmWindow(self)
        win.startTask(threading.Thread(target=knn_main, args=(win, self.train_file_path.get(),
                                                                   self.test_file_path.get())))

    def SVM(self):
        win = AlgorithmWindow(self)
        win.startTask(threading.Thread(target=svm_main, args=(win, self.train_file_path.get(),
                                                                   self.test_file_path.get())))

    def C4dot5(self):
        print("c4.5")

    def browseTrain(self):
        filename = filedialog.askopenfilename()
        self.train_file_path.insert(0, filename)

    def browseTest(self):
        filename = filedialog.askopenfilename()
        self.test_file_path.insert(0, filename)

    def hide(self):
        self.master.withdraw()

    def show(self):
        self.master.update()
        self.master.deiconify()


class AlgorithmWindow:
    def __init__(self, parent):
        self.STOP_THREAD = False
        self.task = threading.Thread()
        self.master = Toplevel()
        self.parent = parent
        self.parent.hide()
        self.master.protocol("WM_DELETE_WINDOW", self.returnMain)
        self.master.geometry("500x500")
        self.master.resizable(0, 0)

        self.master.title("Deep Learning")

        self.textarea = Text(self.master, height=10, width=60)
        self.textarea.config(state=DISABLED)
        self.textarea.grid(row=0, column=0)
        self.setCanvas()

    def print(self, text):
        self.textarea.config(state=NORMAL)
        self.textarea.insert(END, text+"\n")
        self.textarea.config(state=DISABLED)

    def startTask(self, task):
        self.task = task
        self.task.start()
        self.STOP_THREAD = False

    def returnMain(self):
        self.STOP_THREAD = True
        self.task.join()
        self.parent.show()
        self.master.destroy()

    def setCanvas(self):
        self.traces = dict()

        # Define matplotlib figure
        self.f1 = Figure(figsize=(3, 3), dpi=100)
        self.f2 = Figure(figsize=(3, 3), dpi=100)
        self.axis1 = self.f1.add_subplot(111)
        self.axis2 = self.f2.add_subplot(111)
        self.axis1.set_ylabel("Loss")
        self.axis2.set_xlabel("Epoch")
        self.axis2.set_ylabel("Accuracy")

        # Tell Tkinter to display matplotlib figure
        self.canvas1 = FigureCanvasTkAgg(self.f1, master=self.master)
        self.canvas2 = FigureCanvasTkAgg(self.f2, master=self.master)
        self.canvas1.get_tk_widget().grid(row=1)
        self.canvas1.get_tk_widget().grid(row=1)
        self.canvas1.draw()
        self.canvas2.draw()

    def plot(self, train_loss_results, train_accuracy_results):
        self.axis1.plot(train_loss_results)
        self.axis2.plot(train_accuracy_results)


def main():
    app = MainWindow()
    app.run()


if __name__ == "__main__":
    main()
