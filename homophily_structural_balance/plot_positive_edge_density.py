import numpy as np
import matplotlib.pyplot as plt
import argparse


def extract_name(word: str):
    return word.split('=')[-1]


def extract_info(filename: str):
    filename_splitted = filename.split('_')
    assert len(filename_splitted) == 7
    p = float(extract_name(filename_splitted[1]))
    iterations = int(extract_name(filename_splitted[2]))
    size = int(extract_name(filename_splitted[3]))
    G = int(extract_name(filename_splitted[4]))
    return p, iterations, size, G


def load_metrics(filename: str) -> list:
    with open(filename, 'r') as f:
        return [float(line.strip()) for line in f]


def plot_metrics(filename: str, metrics: list):
    p, iterations, size, G = extract_info(filename)
    x = np.linspace(0, iterations, len(metrics))

    plt.plot(x, metrics, label=f'p={p} SIZE={size} G={G}')
    plt.ylabel('rho+')
    plt.xlabel('Iteration')
    plt.legend()
    plt.show()


def main():
    parser = argparse.ArgumentParser(description='Plot positive edge density (rho)')
    parser.add_argument('--metrics-file', type=str, required=True, help='Path to calculated positive edge density')

    args = parser.parse_args()
    metrics = load_metrics(args.metrics_file)
    plot_metrics(args.metrics_file, metrics)


if __name__ == '__main__':
    main()
