FROM ubuntu:latest

RUN apt-get update -y && apt-get install -y inspircd irssi tcpflow && apt-get clean

RUN apt-get install make && apt-get install vim && apt-get install g++

RUN rm -rf /var/lib/apt/lists/*

RUN mkdir /var/run/inspircd/

ENTRYPOINT [ "/bin/bash" ]