FROM ubuntu:latest

RUN apt-get update -y && apt-get install -y inspircd irssi tcpflow && apt-get clean

RUN apt-get install make vim g++

RUN rm -rf /var/lib/apt/lists/*

RUN mkdir /var/run/inspircd/

ENTRYPOINT [ "/bin/bash" ]