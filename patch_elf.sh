#!/bin/bash
set -e
set -u
# this script patches the Entry point address in the ELF header to the correct stack pointer address.
# for some reason, the current GCC comes up with 0x00 as the SP!
# So take the correct SP from the binary and patch it into the ELF...
ELF=$1
BIN=$2

SP=$(xxd -c 4 -l 4 -s 0x00000004 $BIN | cut -d ' ' -f 2)
# address calculated from ELF header spec
echo "00000018: $(echo -n $SP)" | xxd -r - $ELF
arm-none-eabi-readelf -h $ELF | grep "Entry point address"
exit 0
