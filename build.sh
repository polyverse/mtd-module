#!/bin/bash

set -e
set -o pipefail

if [ "$(git status --porcelain)" != "" ]; then
    GIT_STATE="dirty"
else
    GIT_STATE="clean"
fi

commitsha="$(git rev-parse HEAD)"

docker build \
    --build-arg "GIT_COMMIT=$(git rev-parse HEAD)" \
    --build-arg "GIT_USERNAME=$(git config user.name)" \
    --build-arg "GIT_BRANCH=$(git branch --show-current)" \
    --build-arg "GIT_REMOTE=$(git remote get-url origin)" \
    --build-arg "GIT_STATE=$GIT_STATE" \
    -t polyverse/mtd-module:$commitsha \
    .

docker tag polyverse/mtd-module:$commitsha polyverse/mtd-module:latest

