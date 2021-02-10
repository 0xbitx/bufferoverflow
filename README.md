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
## System call hooking
### Kernel modification attack
- **Step 1**: Check malicious module  
![image](https://user-images.githubusercontent.com/20378368/107459865-6d6e1a80-6b9a-11eb-9713-7319c7e2b622.png)
- **Step 2**: Check SD card  
![image](https://user-images.githubusercontent.com/20378368/107325262-d303cd80-6aec-11eb-85fe-6e6c9f196352.png)
```
kss@ubuntu:~/HackRPi/Hook$ lsblk
```
- **Step 3**: Mount SD card  
```
kss@ubuntu:~/HackRPi/Hook$ sudo mount /dev/sdb1 /mnt/raspi
kss@ubuntu:~/HackRPi/Hook$ sudo mount /dev/sdb2 /mnt/fs
```
- **Step 4**: Copy malicious module  
```
kss@ubuntu:~/HackRPi/Hook$ cd ..
kss@ubuntu:~/HackRPi$ sudo cp -r ./Hook /mnt/fs/home/pi
kss@ubuntu:~/HackRPi$ sudo umount /mnt/raspi
kss@ubuntu:~/HackRPi$ sudo umount /mnt/fs
```
- **Result**  
![image](https://user-images.githubusercontent.com/20378368/107399269-dbd3be00-6b43-11eb-9422-c7fb6c2589d8.png)
```
pi@raspberrypi:~/Hook$ sudo insmod hooker.ko
pi@raspberrypi:~/Hook$ sudo rmmod hooker
```
## Buffer Overflow

## Return-Oriented Programming

## Return-To-Libc
