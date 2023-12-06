# Base stage for building the app
FROM aairinei/map-reduce-base:latest as build_app

ARG RUN_TESTS=false
WORKDIR /app
RUN mkdir build

COPY . .
RUN cd build \
    && cmake -DIN_DOCKER=ON -DBUILD_TESTS=$RUN_TESTS .. \
    && make -j$(nproc)

# Only execute this stage if RUN_TESTS is set to true
RUN if [ "$RUN_TESTS" = "true" ] ; then \
    set -e; \
    for test in test_master test_worker test_koala; do \
        /app/package/test/$test; \
    done; \
fi


FROM ubuntu:23.10

WORKDIR /build
COPY --from=build_app /app/package .
# move to /lib so that the dynamic loader can find the lib
RUN cp ./lib/* /lib 
# e pacat sa pui surub unde merge legat cu sarma
COPY --from=build_app /lib/x86_64-linux-gnu/libboost_program_options.so.1.74.0 /lib/libboost_program_options.so.1.74.0

WORKDIR /nfs

# This is the default command - it allows us to debug the image
# It will get overridden in docker compose
CMD ["sleep", "30000"]
