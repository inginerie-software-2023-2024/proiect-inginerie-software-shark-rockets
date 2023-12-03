FROM aairinei/map-reduce-base:latest as build_app

WORKDIR /app
RUN mkdir build

COPY . .
RUN cd build && cmake -DIN_DOCKER=ON .. && make -j$(nproc) 


FROM ubuntu:23.10

WORKDIR /build
COPY --from=build_app /app/package .
# move to /lib so that the dynamic loader can find the lib
RUN cp ./lib/* /lib 

WORKDIR /nfs

# This is the default command - it allows us to debug the image
# It will get overridden in docker compose
CMD ["sleep", "30000"]
