# HackRPi
## RPi Kernel configuration
- **Step 1**: Mount SD card  
```
kss@ubuntu:~/HackRPi$ sudo mkdir /mnt/raspi
kss@ubuntu:~/HackRPi$ sudo mkdir /mnt/fs
kss@ubuntu:~/HackRPi$ sudo mount /dev/sdb1 /mnt/raspi
kss@ubuntu:~/HackRPi$ sudo mount /dev/sdb2 /mnt/fs
```
- **Step 2**: Copy kernel image  
```
kss@ubuntu:~/HackRPi$ sudo cp ./linux/zImage /mnt/raspi/kernel7.img
```
- **Step 3**: Copy modules  
```
kss@ubuntu:~/HackRPi$ sudo cp -r ./linux/4.4.50-v7+/ /mnt/fs/lib/modules/
```
- **Step 4**: Copy device tree blob  
```
kss@ubuntu:~/HackRPi$ sudo cp ./linux/*.dtb /mnt/raspi/
```
- **Step 5**: Copy device tree blob overlays  
```
kss@ubuntu:~/HackRPi$ sudo cp ./linux/*.dtb* /mnt/raspi/overlays
kss@ubuntu:~/HackRPi$ sudo cp ./linux/README /mnt/raspi/overlays
```
- **Step 6**: Unmount SD card  
```
kss@ubuntu:~/HackRPi$ sudo umount /mnt/raspi
kss@ubuntu:~/HackRPi$ sudo umount /mnt/fs
```

## Buffer Overflow

## Return-Oriented Programming

## Return-To-Libc

## System call hooking
### Kernel modification attack
- **Step 1**: Build malicious module  
![image](https://user-images.githubusercontent.com/20378368/107340733-7232c000-6b01-11eb-9f16-652ee58ed41c.png)
```
kss@ubuntu:~/RPi/Hook$ make
```
- **Step 2**: Check SD card  
![image](https://user-images.githubusercontent.com/20378368/107325262-d303cd80-6aec-11eb-85fe-6e6c9f196352.png)
```
kss@ubuntu:~/RPi/Hook$ lsblk
```
- **Step 3**: Mount SD card  
```
kss@ubuntu:~/RPi/Hook$ sudo mount /dev/sdb1 /mnt/raspi
kss@ubuntu:~/RPi/Hook$ sudo mount /dev/sdb2 /mnt/fs
```
- **Step 4**: Copy malicious module  
```
kss@ubuntu:~/HackRPi/Hook$ cd ..
kss@ubuntu:~/HackRPi$ sudo cp -r ./Hook /mnt/fs/home/pi
kss@ubuntu:~/HackRPi$ sudo umount /mnt/raspi
kss@ubuntu:~/HackRPi$ sudo umount /mnt/fs
```
- **Result**  
![hook](https://user-images.githubusercontent.com/20378368/107398121-a9759100-6b42-11eb-8563-ac5b69a92a58.png)