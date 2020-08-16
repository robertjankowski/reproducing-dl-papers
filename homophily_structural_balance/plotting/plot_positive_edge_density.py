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


def plot_metrics(filename: str, metrics: list, output_path: str = None):
    p, iterations, size, G = extract_info(filename)
    x = np.linspace(0, iterations, len(metrics))

    plt.rc('text', usetex=True)
    plt.rc('font', family='serif')
    plt.figure(figsize=(8, 5))
    plt.grid(True, alpha=0.3)
    plt.plot(x, metrics, label=f'p = {p}, N = {size}, G = {G}')
    plt.ylabel(r'$\rho$', fontsize=14)
    plt.xlabel('$t$', fontsize=14)
    plt.xticks(fontsize=14)
    plt.yticks(fontsize=14)
    plt.legend(fontsize=13)
    if output_path is not None:
        plt.savefig(output_path, bbox_inches='tight')
    else:
        plt.show()


def main():
    parser = argparse.ArgumentParser(description='Plot positive edge density (rho)')
    parser.add_argument('--metrics-file', type=str, required=True, help='Path to calculated positive edge density')
    parser.add_argument('--output-figure', type=str, required=False, default=None, help='Where to save output figure')
    args = parser.parse_args()
    metrics = load_metrics(args.metrics_file)
    plot_metrics(args.metrics_file, metrics, args.output_figure)


if __name__ == '__main__':
    main()
