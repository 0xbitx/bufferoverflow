#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/syscalls.h>
#include <linux/string.h>

// SYSCALL_TABLE_BASE_ADDR: RPi에서 아래 명령어를 입력하여 출력되는 주소 입력
// $ sudo cat /proc/kallsyms | grep sys_call_table
#define SYSCALL_TABLE_BASE_ADDR (0x8000fc28)
#define MANAGER_PERMISSION (0xff)

unsigned int ** g_puSysTableAddr = (unsigned int**)SYSCALL_TABLE_BASE_ADDR;
unsigned int g_uPrevAP = 0x00;
unsigned int g_uNewAP = MANAGER_PERMISSION;
unsigned int (* sys_write_orig)(int fd, char *byf, size_t count);

// sys_write_orig() 호출 전, pBuf의 내용 수정
unsigned int sys_write_hooked(int nFD, char * pBuf, size_t nCnt){
    if (nFD==1) {
        memset(pBuf, 0, nCnt);
        strcpy(pBuf, "Hacked!!!\n");
        return sys_write_orig(nFD, pBuf, nCnt);
    }
    else
        return sys_write_orig(nFD, pBuf, nCnt);
}

// System call handler인 sys_write() 주소를 sys_write_hooked() 주소로 변경
// __asm__: MMU Page table entry 접근 권한을 변경하는 어셈블리 코드
// g_uPrevAP: 기존 권한(Client), g_uNewAP: 최상위 권한(Manager)
int __init Hook_Init(void) {
    sys_write_orig = (void *)g_puSysTableAddr[__NR_write];

    __asm__ __volatile__("mrc p15, 0, %0, c3, c0" : "=r"(g_uPrevAP));
    __asm__ __volatile__("mcr p15, 0, %0, c3, c0" : :"r"(g_uNewAP));

    g_puSysTableAddr[__NR_write] = (unsigned int *) sys_write_hooked;

    __asm__ __volatile__("mcr p15, 0, %0, c3, c0" : :"r"(g_uPrevAP));
    return 0;
}

void __exit Hook_Exit(void) {
    __asm__ __volatile__("mrc p15, 0, %0, c3, c0" : "=r"(g_uPrevAP));
    __asm__ __volatile__("mcr p15, 0, %0, c3, c0" : :"r"(g_uNewAP));

    g_puSysTableAddr[__NR_write] = (unsigned int *) sys_write_orig;

    __asm__ __volatile__("mcr p15, 0, %0, c3, c0" : :"r"(g_uPrevAP));
}

module_init(Hook_Init);
module_exit(Hook_Exit);
