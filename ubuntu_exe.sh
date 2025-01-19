#!/bin/bash

docker build -t ubuntu-irc .

docker run -it --name ubuntu-irc-container ubuntu-irc