FROM ubuntu:latest
LABEL Name=cppcourse-2 Version=0.0.1
RUN apt-get -y update && apt-get install -y git cmake make g++ gcc gdb
COPY ./*.cpp /usr/dev/cppcourse-2/
COPY ./*.sh  /usr/dev/cppcourse-2/
COPY ./*.txt  /usr/dev/cppcourse-2/
RUN mkdir /usr/dev/cppcourse-2/build
WORKDIR /usr/dev/cppcourse-2
# TODO these lines not necessary when running in container
#RUN "./cmake.sh" 
#CMD "./run.sh"
