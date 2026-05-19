import m5
from m5.objects import *
import os

# ---------------------------------------------------------------
# Cache classes
# ---------------------------------------------------------------
class L1ICache(Cache):
    assoc = 2
    tag_latency = 2
    data_latency = 2
    response_latency = 2
    mshrs = 4
    tgts_per_mshr = 20
    size = '32kB'

class L1DCache(Cache):
    assoc = 2
    tag_latency = 2
    data_latency = 2
    response_latency = 2
    mshrs = 4
    tgts_per_mshr = 20
    size = '32kB'

class L2Cache(Cache):
    assoc = 8
    tag_latency = 20
    data_latency = 20
    response_latency = 20
    mshrs = 20
    tgts_per_mshr = 12
    size = '256kB'

# ---------------------------------------------------------------
# System setup
# ---------------------------------------------------------------
system = System()

system.clk_domain = SrcClockDomain()
system.clk_domain.clock = "1GHz"
system.clk_domain.voltage_domain = VoltageDomain()

system.mem_mode = "timing"
system.mem_ranges = [AddrRange("512MiB")]

# Out-of-order CPU -- needed for prefetching to actually overlap with work
system.cpu = X86O3CPU()
system.cpu.LQEntries = 128
system.cpu.SQEntries = 128
system.cpu.numROBEntries = 256

# ---------------------------------------------------------------
# L1 caches: sit directly on the CPU
# ---------------------------------------------------------------
system.cpu.icache = L1ICache()
system.cpu.dcache = L1DCache()

system.cpu.icache.cpu_side = system.cpu.icache_port
system.cpu.dcache.cpu_side = system.cpu.dcache_port

# ---------------------------------------------------------------
# L2 bus + L2 cache
# ---------------------------------------------------------------
system.l2bus = L2XBar()

system.cpu.icache.mem_side = system.l2bus.cpu_side_ports
system.cpu.dcache.mem_side = system.l2bus.cpu_side_ports

system.l2cache = L2Cache()
system.l2cache.cpu_side = system.l2bus.mem_side_ports

# ---------------------------------------------------------------
# Memory bus and DRAM
# ---------------------------------------------------------------
system.membus = SystemXBar()
system.l2cache.mem_side = system.membus.cpu_side_ports

# Interrupts (X86)
system.cpu.createInterruptController()
system.cpu.interrupts[0].pio = system.membus.mem_side_ports
system.cpu.interrupts[0].int_requestor = system.membus.cpu_side_ports
system.cpu.interrupts[0].int_responder = system.membus.mem_side_ports

# DRAM
system.mem_ctrl = MemCtrl()
system.mem_ctrl.dram = DDR3_1600_8x8()
system.mem_ctrl.dram.range = system.mem_ranges[0]
system.mem_ctrl.port = system.membus.mem_side_ports

system.system_port = system.membus.cpu_side_ports

# ---------------------------------------------------------------
# Workload
# ---------------------------------------------------------------
binary = "/Users/dakshesh/gem5/515tests/MAY17/bench-run/bench"

system.workload = SEWorkload.init_compatible(binary)

process = Process()
process.cmd = [binary]
system.cpu.workload = process
system.cpu.createThreads()

# ---------------------------------------------------------------
# Run
# ---------------------------------------------------------------
root = Root(full_system=False, system=system)
m5.instantiate()

print("Beginning simulation!")
exit_event = m5.simulate()
print(f"Exiting @ tick {m5.curTick()} because {exit_event.getCause()}")