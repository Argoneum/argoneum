#!/usr/bin/env bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR/..

DOCKER_IMAGE=${DOCKER_IMAGE:-argoneum/argoneumd-develop}
DOCKER_TAG=${DOCKER_TAG:-latest}

BUILD_DIR=${BUILD_DIR:-.}

rm docker/bin/*
mkdir docker/bin
cp $BUILD_DIR/src/argoneumd docker/bin/
cp $BUILD_DIR/src/argoneum-cli docker/bin/
cp $BUILD_DIR/src/argoneum-tx docker/bin/
strip docker/bin/argoneumd
strip docker/bin/argoneum-cli
strip docker/bin/argoneum-tx

docker build --pull -t $DOCKER_IMAGE:$DOCKER_TAG -f docker/Dockerfile docker
