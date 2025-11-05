#!/bin/bash
set -a
source .env
envsubst < config.template.json > config.json
set +a