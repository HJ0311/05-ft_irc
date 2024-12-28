FROM ubuntu:latest

RUN apt-get update -y && apt-get install -y inspircd irssi tcpflow && apt-get clean && rm -rf /var/lib/apt/lists/*

RUN mkdir /var/run/inspircd/

ENTRYPOINT [ "/bin/bash" ]