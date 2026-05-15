#!/bin/bash

TRACE_FILE="../../../m5out/trace.txt"

MEM_ONLY="mem_only1.txt"
FILTERED="filtered1.txt"
ADDRS="addrs1.txt"

echo "extracting memory"
grep -i "mem" "$TRACE_FILE" > "$MEM_ONLY"

echo "getting only ss accesses"
grep -v "SS:" "$MEM_ONLY" > "$FILTERED"

echo "getting memory addresses"
grep -o "A=0x[0-9a-fA-F]*" "$FILTERED" > "$ADDRS"