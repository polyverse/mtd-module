#!/bin/bash

set -e

# Don't publish when there are uncommitted changes.
if [ ! -z "$(git status -s -uno)" ]; then
	echo "COMMIT IS DIRTY, aborting"
	exit 1
fi


commitsha="$(git rev-parse HEAD)"

# need creds to be able to push to our ecr
docker push polyverse/mtd-module:latest
docker push polyverse/mtd-module:$commitsha
