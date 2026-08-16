import numpy as np
import matplotlib
# REMOVED: matplotlib.use('TkAgg')  <- This line was causing the crash
import matplotlib.pyplot as plt


def read_hist(filename):
    data = np.loadtxt(filename)

    intensity = data[:, 0]
    count = data[:, 1]

    return intensity, count


h1x, h1y = read_hist(
    "../images/outputs/hist_gray.txt"
)

h2x, h2y = read_hist(
    "../images/outputs/hist_dark.txt"
)

h3x, h3y = read_hist(
    "../images/outputs/hist_bright.txt"
)

h4x, h4y = read_hist(
    "../images/outputs/hist_low.txt"
)


plt.figure()
plt.bar(h1x, h1y, width=1)
plt.xlabel("Intensity")
plt.ylabel("Number of Pixels")
plt.title("Histogram - Original Grayscale")
plt.xlim(0, 255)
plt.savefig(
    "../images/outputs/plot_gray.png"
)
plt.close()


plt.figure()
plt.bar(h2x, h2y, width=1)
plt.xlabel("Intensity")
plt.ylabel("Number of Pixels")
plt.title("Histogram - Dark Image")
plt.xlim(0, 255)
plt.savefig(
    "../images/outputs/plot_dark.png"
)
plt.close()


plt.figure()
plt.bar(h3x, h3y, width=1)
plt.xlabel("Intensity")
plt.ylabel("Number of Pixels")
plt.title("Histogram - Bright Image")
plt.xlim(0, 255)
plt.savefig(
    "../images/outputs/plot_bright.png"
)
plt.close()


plt.figure()
plt.bar(h4x, h4y, width=1)
plt.xlabel("Intensity")
plt.ylabel("Number of Pixels")
plt.title("Histogram - Low Contrast Image")
plt.xlim(0, 255)
plt.savefig(
    "../images/outputs/plot_low.png"
)
plt.close()
