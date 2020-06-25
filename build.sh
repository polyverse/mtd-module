#!/bin/bash

set -e
set -o pipefail

pv run MakeCompliantImage | tee IMAGE_NAME
docker tag 507760724064.dkr.ecr.us-west-2.amazonaws.com/mtd-module mtd-mod