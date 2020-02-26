
FROM docker/for-desktop-kernel:4.19.76-d665d2cbc4fe70f8ab08ba2cd82d052e41d2a704-amd64 AS ksrc

# Extract headers and compile module
FROM linuxkit/alpine:3fdc49366257e53276c6f363956a4353f95d9a81 AS build
RUN apk add build-base elfutils-dev

COPY --from=ksrc /kernel-dev.tar /
RUN tar xf kernel-dev.tar

WORKDIR /kmod
COPY ./src/* ./
RUN make all

FROM alpine:3.9
COPY --from=build /kmod/mtd.ko /
CMD insmod mtd.ko