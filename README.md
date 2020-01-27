# mtd-module

## Usage

```
make
sudo insmod mtd.ko
sudo bash -c "echo <[PT]ID> > /proc/polyverse_mtd"
sudo cat /proc/polyverse_mtd
sudo rmmod mtd.ko
dmesg
```