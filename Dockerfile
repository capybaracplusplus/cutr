FROM debian:bookworm-slim AS builder

RUN apt-get update && apt-get install -y \
    build-essential \
    git \
    wget \
    curl \
    uuid-dev \
    zlib1g-dev \
    libssl-dev \
    libpq-dev \
    libhiredis-dev \
    pkg-config \
    cmake \
    python3 \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /opt
RUN git clone --branch v1.9.11 --recurse-submodules https://github.com/drogonframework/drogon.git && \
    cd drogon && mkdir build && cd build && \
    cmake .. -DCMAKE_BUILD_TYPE=Release \
             -DCMAKE_INSTALL_PREFIX=/usr/local \
             -DBUILD_DOC=OFF \
             -DBUILD_EXAMPLES=OFF && \
    cmake --build . --target install

WORKDIR /app
COPY . /app

RUN chmod +x generate_config.sh && ./generate_config.sh

RUN mkdir build && cd build && \
    cmake .. -DCMAKE_BUILD_TYPE=Release -DENABLE_DOXYGEN=OFF && \
    cmake --build . --target cutr

FROM debian:bookworm-slim

RUN apt-get update && apt-get install -y \
    libssl3 \
    libpq5 \
    libhiredis0.14 \
    zlib1g \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY --from=builder /usr/local /usr/local
COPY --from=builder /app/build/cutr /app/cutr
COPY --from=builder /app/config.json /app/config.json

EXPOSE 8080
CMD ["./cutr"]
