#!/bin/bash
set -e
set -u
# this script patches the Entry point address in the ELF header to the correct program counter address.
# For some reason, the current GCC stores 0x00 in the ELF header Entry point address!
# This causes debuggers like Ozone to set the PC to 0x00; consequently, the processor starts executing garbage.
# So take the correct PC from the binary and patch it into the ELF...
ELF=$1
BIN=$2

PC=$(xxd -c 4 -l 4 -s 0x00000004 $BIN | cut -d ' ' -f 2)
# address calculated from ELF header spec
echo "00000018: $(echo -n $PC)" | xxd -r - $ELF
arm-none-eabi-readelf -h $ELF | grep "Entry point address"
exit 0
