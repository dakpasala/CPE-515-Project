#!/usr/bin/env python3
import sys
import os


DEFAULT_STATS_PATH = "../../../m5out/stats.txt"
DEFAULT_OUTPUT = "summary.txt"


KEY_STATS = [
    ("simSeconds",                              "Simulated seconds"),
    ("system.cpu.numCycles",                    "CPU cycles"),
    ("simInsts",                                "Instructions executed"),
    ("system.cpu.cpi",                          "CPI (cycles per instruction)"),
    ("system.cpu.ipc",                          "IPC (instructions per cycle)"),

    ("system.cpu.dcache.demandAccesses::total", "L1D total accesses"),
    ("system.cpu.dcache.demandMisses::total",   "L1D demand misses"),
    ("system.cpu.dcache.demandMissRate::total", "L1D demand miss rate"),
    ("system.cpu.dcache.ReadReq.missRate::total",  "L1D read miss rate"),
    ("system.cpu.dcache.WriteReq.missRate::total", "L1D write miss rate"),
    ("system.cpu.dcache.demandAvgMissLatency::total", "L1D avg miss latency (ticks)"),
    ("system.cpu.dcache.demandMshrHits::total", "L1D MSHR hits (prefetch overlap)"),

    ("system.cpu.dcache.overallMshrMissRate::total", "L1D->L2 miss rate (MSHR)"),
    ("system.l2cache.demandMissRate::total",    "L2 demand miss rate"),
    ("system.l2cache.demandMisses::total",      "L2 demand misses"),

    ("system.mem_ctrl.dram.numReads::total",    "DRAM read count"),
    ("system.mem_ctrl.dram.bytesRead::total",   "DRAM bytes read"),
    ("system.mem_ctrl.dram.bwRead::total",      "DRAM read bandwidth (B/s)"),
    ("system.mem_ctrl.dram.pageHitRate",        "DRAM row buffer hit rate"),

    ("system.cpu.iew.lsqFullEvents",            "LSQ full events"),
    ("system.cpu.iew.iqFullEvents",             "IQ full events"),
    ("system.cpu.rename.ROBFullEvents",         "ROB full events"),
]


def parse_stats(path):
    stats = {}
    with open(path) as f:
        for line in f:
            line = line.strip()
            if not line or line.startswith("-") or line.startswith("#"):
                continue
            parts = line.split(None, 1)
            if len(parts) < 2:
                continue
            name = parts[0]
            value = parts[1].split()[0]
            stats[name] = value
    return stats


def format_value(name, value):
    try:
        v = float(value)
    except ValueError:
        return value

    if "missRate" in name or "HitRate" in name or "MissRate" in name:
        if v <= 1.0:
            return f"{v:.4f} ({v*100:.2f}%)"
        else:
            return f"{v:.2f}%"

    if "bytesRead" in name or "bytesWritten" in name:
        if v >= 1024 * 1024:
            return f"{int(v):,} ({v / (1024*1024):.2f} MB)"
        elif v >= 1024:
            return f"{int(v):,} ({v / 1024:.2f} KB)"
        return f"{int(v):,}"

    if "bwRead" in name or "bwWrite" in name:
        if v >= 1024 * 1024:
            return f"{int(v):,} ({v / (1024*1024):.1f} MB/s)"
        return f"{int(v):,}"

    if v == int(v) and abs(v) >= 1000:
        return f"{int(v):,}"

    if 0.001 <= abs(v) < 10000:
        return f"{v:.6g}"

    return value


def main():
    args = sys.argv[1:]

    if len(args) == 0:
        stats_path = DEFAULT_STATS_PATH
        output_path = DEFAULT_OUTPUT
    elif len(args) == 1:
        arg = args[0]
        if "stats" in arg.lower() or "/" in arg or "\\" in arg:
            stats_path = arg
            output_path = DEFAULT_OUTPUT
        else:
            stats_path = DEFAULT_STATS_PATH
            output_path = arg
    else:
        stats_path = args[0]
        output_path = args[1]

    if not os.path.exists(stats_path):
        print(f"Error: stats file not found at '{stats_path}'")
        print(f"Tip: run this script from your config directory, or pass an explicit path.")
        sys.exit(1)

    print(f"Reading stats from: {stats_path}")
    print(f"Writing summary to: {output_path}")
    print()

    stats = parse_stats(stats_path)

    lines = []
    lines.append("=" * 70)
    lines.append(f"gem5 stats summary: {stats_path}")
    lines.append("=" * 70)
    lines.append("")

    sections = [
        ("HEADLINE", KEY_STATS[0:5]),
        ("L1 DATA CACHE (locality story)", KEY_STATS[5:12]),
        ("L2 CACHE", KEY_STATS[12:15]),
        ("DRAM (memory traffic)", KEY_STATS[15:19]),
        ("PIPELINE PRESSURE", KEY_STATS[19:22]),
    ]

    for section_name, section_stats in sections:
        lines.append(f"--- {section_name} ---")
        for stat_name, label in section_stats:
            raw = stats.get(stat_name, "N/A")
            formatted = format_value(stat_name, raw) if raw != "N/A" else "N/A"
            lines.append(f"  {label:<40} {formatted}")
        lines.append("")

    output = "\n".join(lines)
    print(output)

    with open(output_path, "w") as f:
        f.write(output)
    print(f"\nSaved to: {output_path}")


if __name__ == "__main__":
    main()
