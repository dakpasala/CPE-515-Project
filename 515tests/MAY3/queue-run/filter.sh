#!/bin/bash

TRACE_FILE="../../../m5out/trace.txt"

MEM_ONLY="mem_only2.txt"
FILTERED="filtered2.txt"
ADDRS="addrs2.txt"

echo "extracting memory"
grep -i "mem" "$TRACE_FILE" > "$MEM_ONLY"

echo "getting only ss accesses"
grep -v "SS:" "$MEM_ONLY" > "$FILTERED"

echo "getting memory addresses"
grep -o "A=0x[0-9a-fA-F]*" "$FILTERED" > "$ADDRS"