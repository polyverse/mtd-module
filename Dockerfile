# This Dockerfile extracts the kernel headers from the kernel image
# and then compiles a simple hello world kernel module against them.
# In the last stage, it creates a package, which can be used for
# testing.

# FROM linuxkit/kernel:4.19.76 AS ksrc
# FROM docker/for-desktop-kernel:4.19.76-ea7d3632bc9a778f0150bf564f89f94503fecf3e-amd64 AS ksrc
# FROM docker/for-desktop-kernel:4.19.76-0f7878ebeaaf7aa0f05c288846efa8100300e59a-amd64 AS ksrc
FROM docker/for-desktop-kernel:4.19.76-d665d2cbc4fe70f8ab08ba2cd82d052e41d2a704-amd64 AS ksrc

# Extract headers and compile module
FROM linuxkit/alpine:3fdc49366257e53276c6f363956a4353f95d9a81 AS build
RUN apk add build-base elfutils-dev

COPY --from=ksrc /kernel-dev.tar /
RUN tar xf kernel-dev.tar

WORKDIR /kmod
COPY ./src/* ./
RUN make all

# Package
# FROM alpine:3.9 # Comment out when the RANDSTRUCT problem is solved
# COPY --from=build /kmod/mtd.ko /

RUN cat /usr/src/linux-headers-4.19.76-linuxkit/include/generated/randomize_layout_hash.h

CMD /bin/sh
