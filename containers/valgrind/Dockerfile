FROM ubuntu:22.04
RUN apt-get update && apt-get upgrade -y && apt-get install valgrind -y && ulimit -n 1024
ENTRYPOINT ["valgrind", "--leak-check=full", "--track-fds=yes", "--show-leak-kinds=all"]
