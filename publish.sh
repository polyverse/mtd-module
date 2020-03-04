#!/bin/bash

set -e

# need creds to be able to push to our ecr
aws --region $AWS_DEFAULT_REGION ecr get-login  --no-include-email | bash -s

docker push $(cat IMAGE_NAME)
echo "Pushed image $(cat IMAGE_NAME)"