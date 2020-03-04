#!/bin/bash

set -e
set -o pipefail

pv run MakeCompliantImage | tee IMAGE_NAME