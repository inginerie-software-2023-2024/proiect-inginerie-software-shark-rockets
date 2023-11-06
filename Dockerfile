FROM ubuntu:23.10 as build_deps

RUN apt-get update -y
RUN apt-get install -y build-essential autoconf libtool pkg-config
RUN apt-get install -y cmake
RUN apt-get install -y clang libc++-dev
RUN apt install -y git

WORKDIR /app
COPY CMakeLists_deps.txt .
RUN mv CMakeLists_deps.txt CMakeLists.txt
RUN mkdir build && cd build && cmake .. && cmake --build .


FROM ubuntu:23.10 as build_app

RUN apt-get update -y
RUN apt-get install -y build-essential autoconf libtool pkg-config
RUN apt-get install -y cmake
RUN apt-get install -y clang libc++-dev
RUN apt install -y git

WORKDIR /app
RUN mkdir build
COPY --from=build_deps /app/build /app/build

COPY . .
RUN cd build && cmake .. && cmake --build .


FROM ubuntu:23.10

WORKDIR /nfs
COPY --from=build_app /app/build .

# This is the default command - it allows us to debug the image
# It will get overridden in docker compose
CMD ["sleep", "3000"]
