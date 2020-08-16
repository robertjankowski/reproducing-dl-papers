import matplotlib.pyplot as plt
import argparse
import pandas as pd


def parse_args():
    parser = argparse.ArgumentParser(description='Plot phase diagram of rho vs p')
    parser.add_argument('--input-file', type=str, required=True, help="""
        Input file should in format (.tsv:
        
        p   rho
        0   0.1
        0.1 0.2
    """)
    return parser.parse_args()


def load_file(filename: str) -> pd.DataFrame:
    return pd.read_csv(filename, sep='\t', header=0)


def plot_phase_diagram(data: pd.DataFrame):
    plt.rc('text', usetex=True)
    plt.rc('font', family='serif')

    plt.figure(figsize=(8, 6))
    plt.grid(True, alpha=0.3)
    plt.scatter(data.p, data.rho, label='TODO: add G, SIZE info')
    plt.xlabel('$p$', fontsize=14)
    plt.ylabel(r'$\rho$', fontsize=14)
    plt.legend(fontsize=13)
    plt.xticks(fontsize=14)
    plt.yticks(fontsize=14)
    plt.ylim([0, 1])
    plt.show()


def main():
    args = parse_args()
    data = load_file(args.input_file)
    plot_phase_diagram(data)


if __name__ == '__main__':
    main()
