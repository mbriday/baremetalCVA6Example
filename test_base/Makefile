PREFIX=riscv-none-elf
GCC=$(RISCV)/bin/$(PREFIX)-gcc
AS= $(RISCV)/bin/$(PREFIX)-as
OBJDUMP=$(RISCV)/bin/$(PREFIX)-objdump -D

EXEC=base.elf
SRC=main.c
SRC_ASM=

SYS_PATH = ../sys
SRC+=$(SYS_PATH)/syscalls.c
SRC_ASM+=$(SYS_PATH)/crt.S

LINKER_SCRIPT=$(SYS_PATH)/link.ld

CFLAGS = -Wextra -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -ffreestanding -march=rv32imc_zba_zbb_zbs_zbc_zicsr_zifencei -mabi=ilp32 -I$(SYS_PATH)
ASFLAGS = -march=rv32imc_zba_zbb_zbs_zbc_zicsr_zifencei -mabi=ilp32
LDFLAGS= -nostdlib
LIBS = -lgcc

## end of config
ifndef CVA6_REPO_DIR
$(error CVA6_REPO_DIR should be defined and point to the root of the cva6 dir (required for spike/verilator))
endif

OBJ=$(SRC:.c=.o)
OBJ+=$(SRC_ASM:.S=.o)

$(EXEC): $(OBJ)
	$(GCC) $(CFLAGS) $(LDFLAGS) -T $(LINKER_SCRIPT) $(OBJ) $(LIBS) -o ./$@ -Xlinker -Map=$(EXEC).map

%.o: %.c
	$(GCC) -o $@ -c $< $(CFLAGS)

%.o: %.S
	$(GCC) -o $@ -c $< $(ASFLAGS)

.PHONY: all clean mrproper dump

dump: $(EXEC).asm
	
$(EXEC).asm: $(EXEC)
	$(OBJDUMP) -d ./$^ > $(EXEC).asm

clean:
	rm -f $(OBJ)

mrproper: clean
	rm -f $(EXEC) $(EXEC).asm $(EXEC).map $(EXEC).vcd trace_hart_0.dasm trace_rvfi_hart_00.dasm spike.log

# make spike 2>tmp.log
spike: $(EXEC) $(EXEC).asm
	$(CVA6_REPO_DIR)/tools/spike/bin/spike --log-commits --isa=rv32imc_zba_zbb_zbs_zbc_zicsr_zifencei --priv=m  --param-file $(CVA6_REPO_DIR)/config/gen_from_riscv_config/cv32a60x/spike/spike.yaml -l $(EXEC) 2>spike.log

verilator: $(EXEC) $(EXEC).asm
	$(CVA6_REPO_DIR)/work-ver/Variane_testharness -v $(EXEC).vcd $(EXEC) +debug_disable=1 +ntb_random_seed=493907760 \
  ++$(EXEC) +elf_file=$(EXEC) +core_name=cv32a60x +config_file=/$(CVA6_REPO_DIR)/config/gen_from_riscv_config/cv32a60x/spike/spike.yaml +tohost_addr=80001000 +signature=$(EXEC).signature_output +UVM_TESTNAME=uvmt_cva6_firmware_test_c +report_file=$(EXEC).log.yaml

surfer:
	surfer $(EXEC).vcd