with open("prefetch_addrs.txt") as f:
    addresses = [line.strip() for line in f if line.strip()]

with open("trace_addrs.h", "w") as out:
    out.write("#pragma once\n")
    out.write("#include <cstdint>\n\n")

    out.write("const uint64_t trace_addrs[] = {\n")

    for addr in addresses:
        out.write(f"    0x{addr},\n")

    out.write("};\n\n")
    out.write(f"const int trace_size = {len(addresses)};\n")