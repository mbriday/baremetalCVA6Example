# Basic examples to run on the CVA6

## prerequisites
Correct CVA6 installation, including, spike, verilator and the cross compiler, see the README.md file of the project, and follow instructions up to the `Running standalone simulations` section (included). Both spike and verilator should be compiled here.

To recompile simulators, go to the CVA6 dir, and run
```sh
export NUM_JOBS=8
export DV_SIMULATORS=veri-testharness,spike
source .venv/bin/activate
source verif/sim/setup-env.sh
cd verif/sim
TRACE_FAST=1 DEBUG=1 python3 cva6.py --target cv32a60x --iss=$DV_SIMULATORS --iss_yaml=cva6.yaml --c_tests ../tests/custom/hello_world/hello_world.c --linker=../../config/gen_from_riscv_config/linker/link.ld --gcc_opts="-static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g ../tests/custom/common/syscalls.c ../tests/custom/common/crt.S -lgcc -I../tests/custom/env -I../tests/custom/common"
```

if `make verilator` reports an error about the `-v` argument, the VCD trace generation is not enabled (`TRACE_FAST=1 DEBUG=1` during compilation).

the `CVA6_REPO_DIR` should be defined to the root of the CVA6 project