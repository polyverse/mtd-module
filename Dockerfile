
FROM docker/for-desktop-kernel:4.19.76-83885d3b4cff391813f4262099b36a529bca2df8-amd64 AS ksrc

ARG GIT_COMMIT
ARG GIT_REMOTE
ARG GIT_USERNAME
ARG GIT_BRANCH
ARG GIT_STATE

LABEL GIT.COMMIT="$GIT_COMMIT" GIT.REMOTE="$GIT_REMOTE" GIT.USERNAME="$GIT_USERNAME" GIT.BRANCH="$GIT_BRANCH" GIT.STATE="$GIT_STATE"

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