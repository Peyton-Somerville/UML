import numpy as np
import matplotlib.pyplot as plt


###########################
#
#   Perceptron Object
#
#
##########################
class Perceptron(object):
    def __init__(self, eta=0.1, iter=50):
        self.eta = eta
        self.iter = iter

    def fit(self, X, y):
        self.w_ = np.zeros(X.shape[1])
        self.errors_ = []

        for _ in range(self.iter):
            error = 0
            for xi, target in zip(X, y):
                update = self.eta * (target - self.predict(xi))
                self.w_[:] += update * xi
                error += int(update != 0.0)
            self.errors_.append(error)
        return self

    def predict(self, x):
        return np.where(np.dot(x, self.w_[:]) >= 0.0, 1, -1)


###########################
#
#   Linear Regression Object
#
#
##########################
class LinearRegression(object):
    def __init__(self, eta=0.1, iter=50):
        self.eta = eta
        self.iter = iter

    def fit(self, X, y):
        self.w_ = np.zeros(X.shape[1])
        self.cost_ = []

        for i in range(self.iter):
            output = self.net_input(X)
            error = y - output
            self.w_[:] += self.eta * np.dot(X.T, error)
            cost = np.dot(error.T, error) / 2.0
            self.cost_.append(cost)
        return self

    def net_input(self, X):
        return np.dot(X, self.w_[:])

    def predict(self, x):
        return np.where(np.dot(x, self.w_[:]) >= 0.0, 1, -1)


###########################
#
#   Logistic Regression Object
#
#
##########################
class LogisticRegression(object):
    def __init__(self, eta=0.1, iter=50):
        self.eta = eta
        self.iter = iter

    def fit(self, X, y):
        self.w_ = np.zeros(X.shape[1])
        self.cost_ = []

        for i in range(self.iter):
            s = np.dot(X, self.w_[:])
            grad = np.dot(X.T, y) / (1 + np.exp(np.dot(y, s.T)))
            error = -grad.sum() / len(y)
            self.w_[:] += self.eta * error
            cost = np.dot(error.T, error) / 2.0
            self.cost_.append(cost)
        return self

    def predict(self, x):
        return np.where(np.dot(x, self.w_[:]) >= 0.0, 1, -1)


###########################
#
# main()
#
#
##########################
def main():
    dataFile = './iris_VirgVersi.txt'

    X, y = formatIris(dataFile)  # X includes 1 for the bias: X = [[1,x11, x12], [1,x21,x22], .... [1,xN1, xN2]]T

    # X = np.array(([1, 5.7, 4.2], [1, 5.7, 4.1], [1, 7.1, 6.7], [1, 6.7, 5]))
    # y = np.array([1, 1, -1, 1])

    eta = 0.1  # learning rate

    X_std = np.copy(X)
    X_std[:, 1] = (X[:, 1] - X[:, 1].mean()) / X[:, 1].std()  # sepal len
    X_std[:, 2] = (X[:, 2] - X[:, 2].mean()) / X[:, 2].std()  # petal len

    # Perceptron
    ppn = Perceptron(eta)  # , iter=len(y))
    ppn.fit(X, y)

    # Linear Regression
    linR = LinearRegression(eta)
    linR.fit(X, y)

    # Logistic Regression
    logR = LogisticRegression(eta)
    logR.fit(X, y)

    plot_regions(X, y, classifier=ppn)
    plot_regions(X, y, classifier=linR)
    plot_regions(X, y, classifier=logR)


###########################
#
# iris data file
#  get sepal and petal lengths of iris-vericolor and iris-virginica
#
##########################
def formatIris(dataset):
    X = []
    y = []
    with open(dataset, 'r') as f:
        for line in f:
            sline = line.replace('\n', '')
            t = sline.split(',')
            if t[4] == 'Iris-versicolor':
                val = 1
            elif t[4] == 'Iris-virginica':
                val = -1
            else:
                val = 0

            X.append([1, float(t[0]), float(t[2])])	    # [1, sepal len, petal len]
            y.append(val)
    return np.array(X), np.array(y)


###########################
#
#  Plot regions
#
#
##########################
from matplotlib.colors import ListedColormap


def plot_regions(X, y, classifier, resolution=0.02):
    # setup marker generato and clor map
    markers = ('o', 'x', 's', '^', 'v')
    colors = ('red', 'blue', 'lightgreen', 'gray', 'cyan')
    cmap = ListedColormap(colors[:len(np.unique(y))])

    # plot the decision surface
    x1_min, x1_max = X[:, 1].min() - 1, X[:, 1].max() + 1
    x2_min, x2_max = X[:, 2].min() - 1, X[:, 2].max() + 1
    xx1, xx2 = np.meshgrid(np.arange(x1_min, x1_max, resolution), np.arange(x2_min, x2_max, resolution))

    coordinates = np.array([np.ones(len(xx1.ravel())), xx1.ravel(), xx2.ravel()])
    region = np.dot(coordinates.T, classifier.w_[:])
    Z = np.where(region >= 0.0, 1, -1)
    Z = Z.reshape(xx1.shape)
    plt.contourf(xx1, xx2, Z, alpha=0.4, cmap=cmap)

    plt.xlim(xx1.min(), xx1.max())
    plt.ylim(xx2.min(), xx2.max())
    for idx, cl in enumerate(np.unique(y)):
        plt.scatter(x=X[y == cl, 1], y=X[y == cl, 2], alpha=0.8, c=cmap(idx), marker=markers[idx], label=cl)

    plt.xlabel('sepal length')
    plt.ylabel('petal length')
    plt.legend(loc='upper right')
    plt.show()


main()
