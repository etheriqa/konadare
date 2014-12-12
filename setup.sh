#!/bin/bash
set -ev
VERSION=gtest-1.7.0
if [ -d "vendor/${VERSION}" ]; then exit 0; fi
curl -L -O https://googletest.googlecode.com/files/${VERSION}.zip
unzip -q ${VERSION}.zip -d vendor
rm ${VERSION}.zip
