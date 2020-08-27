#!/bin/bash
set -e

if [ -z $1 ]; then
  echo missing input file && exit 1
fi

INPUT_FILE=$1
OUTPUT_DIR=$(dirname $INPUT_FILE)

OUTPUT_FILE="$OUTPUT_DIR/$(basename $INPUT_FILE .bin).crc32.bin"
cp $INPUT_FILE $OUTPUT_FILE

TEMP_FILE="$OUTPUT_DIR/temp.bin"
tail -c +5 $INPUT_FILE > $TEMP_FILE

CRC32=$(crc32 $TEMP_FILE)
echo "CRC-32: $CRC32"
rm $TEMP_FILE

if [ -z $2 ]; then
  OFFSET="00000000"
else
  OFFSET=$2
fi
echo "$OFFSET: $(echo -n $CRC32 | tac -rs ..)" | xxd -r - $OUTPUT_FILE

exit 0
