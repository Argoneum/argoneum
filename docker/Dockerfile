FROM debian:stretch
LABEL maintainer="Argoneum Developers <dev@argoneum.org>"
LABEL description="Dockerised ArgoneumCore, built from Travis"

RUN apt-get update && apt-get -y upgrade && apt-get clean && rm -fr /var/cache/apt/*

COPY bin/* /usr/bin/
