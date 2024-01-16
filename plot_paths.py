import sys
from pathlib import Path
import numpy as np
import matplotlib.pyplot as plt


FIGSIZE = (10.0, 10.0)
OFFSET = 0.05


def load_nodes(csv_file_name):
    nodes = np.array(
        np.genfromtxt(
            csv_file_name,
            delimiter=",",
            converters={0: lambda s: s.decode()},
        ).tolist(),
        dtype=object,
    )
    return nodes


def plot_paths(nodes, csv_file_name):
    x = nodes[1:, 1:2]
    y = nodes[1:, 2:3]
    labels = nodes[1:, 0:1]
    _, ax = plt.subplots(figsize=FIGSIZE)
    ax.set_aspect("equal")
    # ax.scatter(x, y)
    # for i, label in enumerate(labels):
    #     ax.annotate(label[0], (x[i] + OFFSET, y[i] + OFFSET))

    for step, (n1, n2) in enumerate(zip(nodes[0:-1], nodes[1:])):
        x0, y0 = n1[1:]
        x1, y1 = n2[1:]
        ax.plot([x0, x1], [y0, y1])
        # ax.annotate(
        #     f"s{step}",
        #     ((x0 + x1) * 0.5 + OFFSET, (y0 + y1) * 0.5 + OFFSET),
        #     fontsize=6,
        # )
    plt.savefig(csv_file_name.parent / (csv_file_name.stem + ".png"))


def main():
    try:
        file_name = Path(sys.argv[1])
        nodes_solution = load_nodes(file_name)
    except Exception as e:
        print(f'Error code: {e}')
        exit()

    plot_paths(nodes_solution, file_name)


if __name__ == "__main__":
    main()
