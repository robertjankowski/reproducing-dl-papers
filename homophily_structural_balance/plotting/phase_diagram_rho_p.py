import matplotlib.pyplot as plt
import argparse
import pandas as pd


def parse_args():
    parser = argparse.ArgumentParser(description='Plot phase diagrams')
    parser.add_argument('--input-file', type=str, required=True, help="""
        Input file should in format (.tsv:
        
        p   rho
        0   0.1
        0.1 0.2
    """)
    parser.add_argument('--y-axis', type=str, required=True,
                        help='Whether positive density links (rho) or paradise probability (pp)')
    parser.add_argument('--G', type=int, required=True, help='Number of attributes')
    parser.add_argument('--N', type=int, required=True, help='Network size')
    parser.add_argument('--save-fig', type=str, required=False, default='')
    return parser.parse_args()


def load_file(filename: str) -> pd.DataFrame:
    return pd.read_csv(filename, sep='\t', header=0)


def plot_phase_diagram(data: pd.DataFrame, y_axis: str, G: int, N: int, save_fig: bool):
    plt.rc('text', usetex=True)
    plt.rc('font', family='serif')

    plt.figure(figsize=(8, 6))
    plt.grid(True, alpha=0.3)
    if y_axis == 'rho':
        plt.scatter(data.p, data.rho, label=f'G={G}, N={N}')
        plt.ylabel(r'$\rho$', fontsize=14)
        plt.ylim([0, 1])
    elif y_axis == 'pp':
        plt.scatter(data.p, data.Pp, label=f'G={G}, N={N}')
        plt.plot(data.p, data.Pp)
        plt.ylabel(r'$P_p(p)$', fontsize=14)
        plt.ylim([0.1, 0.5])
    plt.xlabel('$p$', fontsize=14)
    plt.legend(fontsize=13)
    plt.xticks(fontsize=14)
    plt.yticks(fontsize=14)
    if save_fig:
        plt.savefig(save_fig, bbox_inches='tight', dpi=300)
    else:
        plt.show()


def main():
    args = parse_args()
    data = load_file(args.input_file)
    plot_phase_diagram(data, args.y_axis, args.G, args.N, args.save_fig)


if __name__ == '__main__':
    main()
