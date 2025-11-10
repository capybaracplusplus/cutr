FROM ubuntu:22.04

RUN apt-get update && \
    apt-get install -y \
        build-essential \
        git \
        wget \
        curl \
        cmake \
        libssl-dev \
        libpq-dev \
        libhiredis-dev \
        doxygen \
        python3 \
        python3-pip \
        sudo \
        unzip \
        pkg-config \
        lsb-release && \
    rm -rf /var/lib/apt/lists/*

RUN wget https://github.com/Kitware/CMake/releases/download/v3.27.7/cmake-3.27.7-linux-x86_64.sh && \
    bash cmake-3.27.7-linux-x86_64.sh --skip-license --prefix=/usr/local && \
    rm cmake-3.27.7-linux-x86_64.sh

WORKDIR /opt
RUN git clone --branch v1.9.11 --recurse-submodules https://github.com/drogonframework/drogon.git && \
    cd drogon && mkdir build && cd build && \
    cmake .. -DCMAKE_BUILD_TYPE=Release && \
    cmake --build .

WORKDIR /app
COPY . .

RUN chmod +x generate_config.sh && ./generate_config.sh

RUN mkdir -p build && cd build && \
    cmake .. -DCMAKE_BUILD_TYPE=Release -DENABLE_DOXYGEN=OFF && \
    cmake --build .

EXPOSE 8080
CMD ["./build/cutr"]
