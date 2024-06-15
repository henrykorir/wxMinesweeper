FROM ubuntu:latest

RUN apt-get update && apt-get -y install cmake build-essential libgtk2.0-dev libgtk-3-dev

WORKDIR /wxwidgets

COPY . .

RUN cmake . && cmake --build .

RUN pwd \
    && cd ./demos/forty \
    && ls -a \
    && make -f ./makefile.unx \
    && ls -a \
    && pwd

ENV DISPLAY=:1.0

CMD ["/bin/bash","-c","./demos/forty/forty"]