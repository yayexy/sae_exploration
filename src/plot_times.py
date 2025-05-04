import matplotlib.pyplot as plt
import csv

sizes = []
times = []

with open("execution_times.csv", "r") as f:
    reader = csv.reader(f)
    next(reader)
    for row in reader:
        sizes.append(int(row[0]))
        times.append(float(row[1]))

plt.figure(figsize=(10, 6))
plt.plot(sizes, times, marker='o', linestyle='-', color='teal')
plt.title("Execution Time vs Number of Cities")
plt.xlabel("Number of Cities")
plt.ylabel("Time (s)")
plt.grid(True)
plt.tight_layout()
plt.savefig("execution.png")
plt.show()
