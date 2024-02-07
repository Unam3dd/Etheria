FROM ubuntu:22.04
WORKDIR /project/
RUN apt-get update && apt-get upgrade -y && apt-get install gcc make zsh bc libcriterion-dev git cmake -y && apt-get clean && ulimit -n 1024
STOPSIGNAL SIGTERM
ENTRYPOINT ["make", "build", "clean"]
