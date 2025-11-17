import matplotlib.pyplot as plt

def load(filename):
    with open(filename) as f:
        return [int(x) for x in f.readlines()]

fcfs = load("fcfs_path.csv")[:200]
scan = load("scan_path.csv")[:200]
cscan = load("cscan_path.csv")[:200]

# ==== Gráfico de movimiento del cabezal ====
plt.figure(figsize=(12, 6))
plt.plot(fcfs, label="FCFS")
plt.plot(scan, label="SCAN")
plt.plot(cscan, label="C-SCAN")
plt.xlabel("Solicitud")
plt.ylabel("Cilindro")
plt.title("Head Movement (primeros 200)")
plt.legend()
plt.grid(True)
plt.savefig("head_movement.png", dpi=300)
plt.close()

# ==== Gráfico comparativo ====
r = load("resultados.csv")
names = ["FCFS", "SCAN", "C-SCAN"]

plt.figure(figsize=(7, 5))
plt.bar(names, r)
plt.ylabel("Movimiento total")
plt.title("Comparación de Algoritmos")
plt.grid(axis='y')
plt.savefig("performance_comparison.png", dpi=300)
plt.close()
