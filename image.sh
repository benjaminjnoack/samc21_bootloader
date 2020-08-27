#!/bin/bash

if [ -z "$1" ]; then
  BUILD_DIR=$(pwd)
else
  BUILD_DIR="$1"
fi

MAGIC="TechShot"
CHECKSUM=12345678
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

echo "#include \"image.h\"

struct image_hdr __attribute__((section(\".image_hdr\"))) image = {
	.checksum = 0x$CHECKSUM,
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