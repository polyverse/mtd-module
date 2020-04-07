#!/bin/bash

set -e

# Don't publish when there are uncommitted changes.
if [ ! -z "$(git status -s -uno)" ]; then
	echo "COMMIT IS DIRTY, aborting"
	exit 1
fi

# need creds to be able to push to our ecr
aws --region $AWS_DEFAULT_REGION ecr get-login  --no-include-email | bash -s

docker push $(cat IMAGE_NAME)
echo "Pushed image $(cat IMAGE_NAME)"