from collections import Counter

addresses = []

with open("addrs.txt") as f:
    for line in f:
        addr = int(line.strip().split("=")[1], 16)
        addresses.append(addr)

strides = [addresses[i + 1] - addresses[i] for i in range(len(addresses) - 1)]
stride_counts = Counter(strides)

with open("stride_counts.txt", "w") as f:
    for stride, count in stride_counts.most_common():
        f.write(f"{stride},{count}\n")

seen = set()
reuse = 0

for addr in addresses:
    if addr in seen:
        reuse += 1
    seen.add(addr)

with open("reuse.txt", "w") as f:
    f.write(f"Total addresses: {len(addresses)}\n")
    f.write(f"Reuse count: {reuse}\n")
    f.write(f"Reuse ratio: {reuse / len(addresses):.4f}\n")


runs = []
current_run = 0

for stride in strides:
    # Vector storage should mostly show up as tidy eight-byte steps.
    if stride == 8:
        current_run += 1
    else:
        if current_run > 0:
            runs.append(current_run)
        current_run = 0

if current_run > 0:
    runs.append(current_run)

avg_run = sum(runs) / len(runs) if runs else 0

with open("runs.txt", "w") as f:
    f.write(f"Total runs: {len(runs)}\n")
    f.write(f"Average run length: {avg_run:.2f}\n")
    f.write("First 20 runs:\n")
    for r in runs[:20]:
        f.write(f"{r}\n")
