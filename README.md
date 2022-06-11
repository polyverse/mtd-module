# DEPRECATION NOTICE

Please note that this repository has been deprecated and is no longer actively maintained by Polyverse Corporation.  It may be removed in the future, but for now remains public for the benefit of any users.

Importantly, as the repository has not been maintained, it may contain unpatched security issues and other critical issues.  Use at your own risk.

While it is not maintained, we would graciously consider any pull requests in accordance with our Individual Contributor License Agreement.  https://github.com/polyverse/contributor-license-agreement

For any other issues, please feel free to contact info@polyverse.com

---
# mtd-module

## Usage - Docker

```
./build.sh
docker run -it --privileged --rm polyverse/mtd-module
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
