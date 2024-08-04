FROM ubuntu:20.04
WORKDIR /app
COPY . .
RUN apt-get upgrade && apt-get update \
	&& apt-get install -y build-essential \
	&& apt-get install -y clang \
    && apt-get install -y libpthread-stubs0-dev \
    && apt-get install -y libasan6 libtsan0 \
	&& rm -rf /var/lib/apt/lists/*
RUN make && make clean
ENTRYPOINT ["./philo"]
