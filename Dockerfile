# syntax=docker/dockerfile:1
FROM ubuntu
#Set the default shell to be bash
SHELL ["/bin/bash", "-c"]
#Install the required dependencies
RUN apt-get update && \
  DEBIAN_FRONTEND=noninteractive \
  TZ=America/New_York  \
  apt-get install  -y \
  cmake \
  libprotobuf-dev \
  protobuf-c-compiler \
  protobuf-compiler \
  libopenmpi-dev \
  build-essential
#Copy our application into the container
WORKDIR /containerizedAppWithBOM
COPY . .
