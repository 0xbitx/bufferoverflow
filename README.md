# HackRPi
## RPi Kernel configuration
- Mount SD card
```
kss@ubuntu:~/HackRPi$ sudo mkdir /mnt/raspi
kss@ubuntu:~/HackRPi$ sudo mkdir /mnt/fs
kss@ubuntu:~/HackRPi$ sudo mount /dev/sdb1 /mnt/raspi
kss@ubuntu:~/HackRPi$ sudo mount /dev/sdb2 /mnt/fs
```
- Copy kernel image
```
kss@ubuntu:~/HackRPi$ sudo cp ./linux/zImage /mnt/raspi/kernel7.img
```
- Copy modules
```
kss@ubuntu:~/HackRPi$ sudo cp -r ./linux/4.4.50-v7+/ /mnt/fs/lib/modules/
```
- Copy device tree blob
```
kss@ubuntu:~/HackRPi$ sudo cp ./linux/*.dtb /mnt/raspi/
```
- Copy device tree blob overlays
```
kss@ubuntu:~/HackRPi$ sudo cp ./linux/*.dtb* /mnt/raspi/overlays
kss@ubuntu:~/HackRPi$ sudo cp ./linux/README /mnt/raspi/overlays
```
- Unmount SD card
```
kss@ubuntu:~/HackRPi$ sudo umount /mnt/raspi
kss@ubuntu:~/HackRPi$ sudo umount /mnt/fs
```

## Buffer Overflow

## Return-Oriented Programming

## Return-To-Libc

## System call hooking
### Kernel modification attack
- Build malicious module
![image](https://user-images.githubusercontent.com/20378368/107340733-7232c000-6b01-11eb-9f16-652ee58ed41c.png)
```
kss@ubuntu:~/RPi/Hook$ make
```
- Check SD card
![image](https://user-images.githubusercontent.com/20378368/107325262-d303cd80-6aec-11eb-85fe-6e6c9f196352.png)
```
kss@ubuntu:~/RPi/Hook$ lsblk
```
- Mount SD card
```
kss@ubuntu:~/RPi/Hook$ sudo mount /dev/sdb1 /mnt/raspi
kss@ubuntu:~/RPi/Hook$ sudo mount /dev/sdb2 /mnt/fs
```
- Copy malicious module
```
kss@ubuntu:~/RPi/Hook$ sudo cp -r . /mnt/fs/home/pi
kss@ubuntu:~/RPi/Hook$ sudo umount /mnt/raspi
kss@ubuntu:~/RPi/Hook$ sudo umount /mnt/fs
```