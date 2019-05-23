import threading
from queue import Queue
from matplotlib.figure import Figure
import matplotlib.pyplot as plt
from matplotlib.axes import Axes
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from NeuralNetwork import NeuralNetwork
from KNearestNeighbor import knn_main
from SVM import svm_main
from DecisionTree import DecisionTree
from tkinter import Tk, Label, Button, Entry, StringVar, DISABLED, NORMAL, END
from tkinter import Scrollbar, W, E, LEFT, filedialog, Toplevel, Text
import random
import matplotlib
matplotlib.use('TkAgg')


class MainWindow:
    def __init__(self):
        self.master = Tk()
        self.master.protocol("WM_DELETE_WINDOW", self.quit)
        self.master.geometry("400x290")
        self.master.resizable(0, 0)

        self.master.title("Deep Learning")
        self.title_label = Label(
            self.master, text="Dota2 Victory prevision App")
        self.title_label.grid(row=0, padx=(100, 20), pady=10)

        self.train_file_label = Label(
            self.master, text="Train File Path", justify=LEFT)
        self.train_file_label.grid(row=1, padx=(100, 20))

        self.train_file_path = Entry(self.master)
        self.train_file_path.grid(row=2, padx=(100, 0), sticky=W)

        self.train_file_browse = Button(
            self.master, text="Browse", command=self.browseTrain)

        self.train_file_browse.grid(row=2, padx=(100, 0), sticky=E)

        self.test_file_label = Label(
            self.master, text="Test File Path", justify=LEFT)
        self.test_file_label.grid(row=3, padx=(100, 0))

        self.test_file_path = Entry(self.master)
        self.test_file_path.grid(row=4,  padx=(100, 0), sticky=W)

        self.test_file_browse = Button(
            self.master, text="Browse", command=self.browseTest)

        self.test_file_browse.grid(row=4, padx=(100, 0), sticky=E)

        self.NeuralNetworkButton = Button(
            self.master, text="Neural Network", command=self.startNeuralNetwork)
        self.NeuralNetworkButton.grid(row=5, padx=(100, 0), pady=1)

        self.KNNButton = Button(
            self.master, text="K-Nearest Neighbor", command=self.KNN)
        self.KNNButton.grid(row=6, padx=(100, 0), pady=1)

        self.SVMButton = Button(
            self.master, text="Support Vector Machine", command=self.KNN)
        self.SVMButton.grid(row=7, padx=(100, 0), pady=1)

        self.DecisionTreeButton = Button(
            self.master, text="Decision Tree", command=self.startDecisionTree)
        self.DecisionTreeButton.grid(row=8, padx=(100, 0), pady=1)

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

    def startDecisionTree(self):
        win = AlgorithmWindow(self)
        win.startTask(threading.Thread(target=DecisionTree, args=(win, self.train_file_path.get(),
                                                                  self.test_file_path.get())))

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

    def quit(self):
        self.master.quit()
        self.master.destroy()


class AlgorithmWindow:
    def __init__(self, parent):
        self.STOP_THREAD = False
        self.plots = Queue()
        self.task = threading.Event()
        self.master = Toplevel()
        self.parent = parent
        self.parent.hide()
        self.master.protocol("WM_DELETE_WINDOW", self.returnMain)
        self.master.geometry("600x680")
        self.master.resizable(0, 0)

        self.master.title("Deep Learning")

        self.textarea = Text(self.master, height=10, width=60)
        self.textarea.config(state=DISABLED)
        self.textarea.grid(row=0, column=0, sticky="nsew")

        scrollb = Scrollbar(self.master, command=self.textarea.yview)
        scrollb.grid(row=0, column=1, sticky='nsew')
        self.textarea['yscrollcommand'] = scrollb.set
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
        self.parent.master.after_cancel(self._afterJob)
        self.master.destroy()

    def setCanvas(self):
        fig, axes = plt.subplots(2, sharex=True, figsize=(5, 5))
        self.axes = axes
        # Tell Tkinter to display matplotlib figure
        self.canvas = FigureCanvasTkAgg(fig, master=self.master)
        self.canvas.get_tk_widget().grid(row=1, column=0)

        fig.suptitle('Training Metrics')

        axes[0].set_ylabel("Loss", fontsize=14)
        axes[0].plot([])

        axes[1].set_ylabel("Accuracy", fontsize=14)
        axes[1].set_xlabel("Epoch", fontsize=14)
        axes[1].plot([])
        self.canvas.draw()
        self.updatePlot()

    def plot(self, train_loss_results, train_accuracy_results):
        self.plots.put([train_loss_results, train_accuracy_results])

    def updatePlot(self):
        try:  # Try to check if there is data in the queue
            result = self.plots.get_nowait()
            self.axes[0].plot(result[0])
            self.axes[1].plot(result[1])
            self.canvas.draw()
            self._afterJob = self.parent.master.after(500, self.updatePlot)
        except:
            self._afterJob = self.parent.master.after(500, self.updatePlot)


def runApp():
    app = MainWindow()
    app.run()
