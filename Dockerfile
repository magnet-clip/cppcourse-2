FROM ubuntu:latest
LABEL Name=cppcourse-2 Version=0.0.1
RUN apt-get -y update && apt-get install -y cmake make g++ gcc
COPY ./*.cpp /usr/dev/cppcourse-2/
COPY ./*.sh  /usr/dev/cppcourse-2/
RUN mkdir /usr/dev/cppcourse-2/build
WORKDIR /usr/dev/cppcourse-2
CMD ["./cmake.sh && ./run.sh"]
