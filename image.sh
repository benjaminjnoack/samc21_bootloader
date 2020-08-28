#!/bin/bash
set -e
set -u

if [ -z "$1" ]; then
  BUILD_DIR=$(pwd)
else
  BUILD_DIR="$1"
fi

DUMMY_CHECKSUM="0x12345678"
DUMMY_SIZE="0"
MAGIC="TechShot"
MAGIC_LENGTH=$(echo -n $MAGIC | wc -c)
TIMESTAMP=$(date +%s)
TAG=$(git tag -l 'v*' | tail -n 1 | tr -d v)
MAJOR_VERSION=$(echo $TAG | cut -d \. -f 1)
MINOR_VERSION=$(echo $TAG | cut -d \. -f 2)
PATCH_VERSION=$(echo $TAG | cut -d \. -f 3)

USER_SIZE=$(echo -n $USER | wc -c)
if [ $USER_SIZE -gt 255 ];then
  echo $USER is too long && exit 1
fi

HOST_SIZE=$(echo -n $HOSTNAME | wc -c)
if [ $HOST_SIZE -gt 255 ];then
  echo $USER is too long && exit 1
fi

COMMIT_SHA1=$(git log --pretty=format:"%H" -1 | cut -c 1-8)
[[ $(git diff --exit-code && git diff --cached --exit-code) ]] && CLEAN_BUILD="false" || CLEAN_BUILD="true"
DATA="$(echo -ne "$MAGIC\0$USER\0$HOSTNAME\0" | xxd -i)"

echo -n "#ifndef SAMC21_BOOTLOADER_IMAGE_H
#define SAMC21_BOOTLOADER_IMAGE_H

#include \"stdint.h\"
#include \"stdbool.h\"

#define IMAGE_DUMMY_CHECKSUM $DUMMY_CHECKSUM
#define IMAGE_MAGIC \"$MAGIC\"
#define IMAGE_MAGIC_LENGTH $MAGIC_LENGTH

struct __attribute__((packed)) image_hdr  {
	uint32_t checksum;
	uint32_t image_size;
	uint32_t timestamp;
	uint8_t user_size;
	uint8_t host_size;
	uint32_t commit_sha1;
	bool clean_build;
	uint8_t major_version;
	uint8_t minor_version;
	uint8_t patch_version;
	uint8_t data[];
};

#endif //SAMC21_BOOTLOADER_IMAGE_H
" > $BUILD_DIR/image.h

echo -n "#include \"image.h\"

const struct image_hdr __attribute__((section(\".image_hdr\"))) image = {
	.checksum = $DUMMY_CHECKSUM,
	.image_size = $DUMMY_SIZE,
	.timestamp = $TIMESTAMP,
	.user_size = $USER_SIZE,
	.host_size = $HOST_SIZE,
	.commit_sha1 = 0x$COMMIT_SHA1,
	.clean_build = $CLEAN_BUILD,
	.major_version = $MAJOR_VERSION,
	.minor_version = $MINOR_VERSION,
	.patch_version = $PATCH_VERSION,
	.data = {$DATA }
};
" > $BUILD_DIR/image.c

exit 0