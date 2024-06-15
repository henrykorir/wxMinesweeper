FROM ubuntu:latest

RUN apt-get update \
    && apt-get install -y cmake apt-utils git wget build-essential libgtk2.0-dev libgtk-3-dev

WORKDIR /wxminesweeper

COPY . .

RUN cmake -DCMAKE_BUILD_TYPE=Release . && \
    cmake --build . --parallel 8

CMD ["./wxminesweeper"]