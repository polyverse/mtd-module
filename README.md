# mtd-module

## Usage - Docker

```
./build.sh
docker run -it --privileged --rm mtd-mod
```

## Usage

```
make
sudo insmod mtd.ko
sudo bash -c "echo <[PT]ID> > /proc/polyverse_mtd"
sudo cat /proc/polyverse_mtd
sudo rmmod mtd.ko
dmesg
```

## References

[Various relevant web links](./WEBLINKS.md)