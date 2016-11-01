#pragma once
#ifndef __ASSEMBLER__
#include "apoctypes.h"
#include "apocpic.h"
#include "apocidt.h"
#include "apocgdt.h"
#include "apocpit.h"
#include "apockeyboard.h"

namespace Apoc
{
  namespace X86
  {
    //
    // Assembly instructions
    //
    static __inline void IOWait(void);
    static __inline void STI(void) __attribute__((always_inline));
    static __inline void CLI(void) __attribute__((always_inline));
    static __inline void INT3(void) __attribute__((always_inline));
    static __inline UInt8 INB(int port) __attribute__((always_inline));
    static __inline void insb(int port, void *addr, int cnt) __attribute__((always_inline));
    static __inline UInt16 INW(int port) __attribute__((always_inline));
    static __inline void insw(int port, void *addr, int cnt) __attribute__((always_inline));
    static __inline UInt32 inl(int port) __attribute__((always_inline));
    static __inline void INSL(int port, void *addr, int cnt) __attribute__((always_inline));
    static __inline void OUTB(int port, UInt8 data) __attribute__((always_inline));
    static __inline void outsb(int port, const void *addr, int cnt) __attribute__((always_inline));
    static __inline void OUTW(int port, UInt16 data) __attribute__((always_inline));
    static __inline void outsw(int port, const void *addr, int cnt) __attribute__((always_inline));
    static __inline void OUTSL(int port, const void *addr, int cnt) __attribute__((always_inline));
    static __inline void outl(int port, UInt32 data) __attribute__((always_inline));
    static __inline void invlpg(void *addr) __attribute__((always_inline));
    static __inline void LIDT(const void *p) __attribute__((always_inline));
    static __inline void lldt(UInt16 sel) __attribute__((always_inline));
    static __inline void ltr(UInt16 sel) __attribute__((always_inline));
    static __inline void lcr0(UInt32 val) __attribute__((always_inline));
    static __inline UInt32 rcr0(void) __attribute__((always_inline));
    static __inline UInt32 rcr2(void) __attribute__((always_inline));
    static __inline void lcr3(UInt32 val) __attribute__((always_inline));
    static __inline UInt32 rcr3(void) __attribute__((always_inline));
    static __inline void lcr4(UInt32 val) __attribute__((always_inline));
    static __inline UInt32 rcr4(void) __attribute__((always_inline));
    static __inline void tlbflush(void) __attribute__((always_inline));
    static __inline UInt32 read_eflags(void) __attribute__((always_inline));
    static __inline void write_eflags(UInt32 eflags) __attribute__((always_inline));
    static __inline UInt32 read_ebp(void) __attribute__((always_inline));
    static __inline UInt32 read_esp(void) __attribute__((always_inline));
    static __inline void CPUID(UInt32 info, UInt32 *eaxp, UInt32 *ebxp, UInt32 *ecxp, UInt32 *edxp);

    static __inline void IOWait(void)
    { __asm __volatile("outb %%al, $0x80" : : "a"(0)); }

    static __inline void STI(void)
    { __asm __volatile("sti"); }

    static __inline void CLI(void)
    { __asm __volatile("cli"); }

    static __inline void INT3(void)
    { __asm __volatile("int3"); }

    static __inline UInt8 INB(int port)
    {
      UInt8 data;
      __asm __volatile("inb %w1,%0" : "=a" (data) : "d" (port));
      return data;
    }

    static __inline void insb(int port, void *addr, int cnt)
    {
      __asm __volatile("cld\n\trepne\n\tinsb"            :
                       "=D" (addr), "=c" (cnt)           :
                       "d" (port), "0" (addr), "1" (cnt) :
                       "memory", "cc");
    }

    static __inline UInt16 INW(int port)
    {
	    UInt16 data;
	    __asm __volatile("INW %w1,%0" : "=a" (data) : "d" (port));
	    return data;
    }

    static __inline void insw(int port, void *addr, int cnt)
    {
	    __asm __volatile("cld\n\trepne\n\tinsw"			:
			     "=D" (addr), "=c" (cnt)		:
			     "d" (port), "0" (addr), "1" (cnt)	:
			     "memory", "cc");
    }

    static __inline UInt32 inl(int port)
    {
	    UInt32 data;
	    __asm __volatile("inl %w1,%0" : "=a" (data) : "d" (port));
	    return data;
    }

    static __inline void INSL(int port, void *addr, int cnt)
    {
	    __asm __volatile("cld\n\trepne\n\tinsl"			:
			     "=D" (addr), "=c" (cnt)		:
			     "d" (port), "0" (addr), "1" (cnt)	:
			     "memory", "cc");
    }

    static __inline void OUTB(int port, UInt8 data)
    {
	    __asm __volatile("outb %0,%w1" : : "a" (data), "d" (port));
    }

    static __inline void outsb(int port, const void *addr, int cnt)
    {
	    __asm __volatile("cld\n\trepne\n\toutsb"		:
			     "=S" (addr), "=c" (cnt)		:
			     "d" (port), "0" (addr), "1" (cnt)	:
			     "cc");
    }

    static __inline void OUTW(int port, UInt16 data)
    {
	    __asm __volatile("outw %0,%w1" : : "a" (data), "d" (port));
    }

    static __inline void outsw(int port, const void *addr, int cnt)
    {
	    __asm __volatile("cld\n\trepne\n\toutsw"		:
			     "=S" (addr), "=c" (cnt)		:
			     "d" (port), "0" (addr), "1" (cnt)	:
			     "cc");
    }

    static __inline void OUTSL(int port, const void *addr, int cnt)
    {
	    __asm __volatile("cld\n\trepne\n\toutsl"		:
			     "=S" (addr), "=c" (cnt)		:
			     "d" (port), "0" (addr), "1" (cnt)	:
			     "cc");
    }

    static __inline void outl(int port, UInt32 data)
    {
	    __asm __volatile("outl %0,%w1" : : "a" (data), "d" (port));
    }

    static __inline void invlpg(void *addr)
    { 
	    __asm __volatile("invlpg (%0)" : : "r" (addr) : "memory");
    }  

    static __inline void LIDT(const void *p)
    {
	    __asm __volatile("lidt (%0)" : : "r" (p));
    }

    static __inline void lldt(UInt16 sel)
    {
	    __asm __volatile("lldt %0" : : "r" (sel));
    }

    static __inline void ltr(UInt16 sel)
    {
	    __asm __volatile("ltr %0" : : "r" (sel));
    }

    static __inline void lcr0(UInt32 val)
    {
	    __asm __volatile("movl %0,%%cr0" : : "r" (val));
    }

    static __inline UInt32 rcr0(void)
    {
	    UInt32 val;
	    __asm __volatile("movl %%cr0,%0" : "=r" (val));
	    return val;
    }

    static __inline UInt32 rcr2(void)
    {
	    UInt32 val;
	    __asm __volatile("movl %%cr2,%0" : "=r" (val));
	    return val;
    }

    static __inline void lcr3(UInt32 val)
    {
	    __asm __volatile("movl %0,%%cr3" : : "r" (val));
    }

    static __inline UInt32 rcr3(void)
    {
	    UInt32 val;
	    __asm __volatile("movl %%cr3,%0" : "=r" (val));
	    return val;
    }

    static __inline void lcr4(UInt32 val)
    {
	    __asm __volatile("movl %0,%%cr4" : : "r" (val));
    }

    static __inline UInt32 rcr4(void)
    {
	    UInt32 cr4;
	    __asm __volatile("movl %%cr4,%0" : "=r" (cr4));
	    return cr4;
    }

    static __inline void tlbflush(void)
    {
	    UInt32 cr3;
	    __asm __volatile("movl %%cr3,%0" : "=r" (cr3));
	    __asm __volatile("movl %0,%%cr3" : : "r" (cr3));
    }

    static __inline UInt32 read_eflags(void)
    {
	    UInt32 eflags;
	    __asm __volatile("pushfl; popl %0" : "=r" (eflags));
	    return eflags;
    }

    static __inline void write_eflags(UInt32 eflags)
    {
	    __asm __volatile("pushl %0; popfl" : : "r" (eflags));
    }

    static __inline UInt32 read_ebp(void)
    {
	    UInt32 ebp;
	    __asm __volatile("movl %%ebp,%0" : "=r" (ebp));
	    return ebp;
    }

    static __inline UInt32 read_esp(void)
    {
	    UInt32 esp;
	    __asm __volatile("movl %%esp,%0" : "=r" (esp));
	    return esp;
    }

    static __inline void CPUID(UInt32 info, UInt32 *eaxp, UInt32 *ebxp, UInt32 *ecxp, UInt32 *edxp)
    {
      UInt32 eax, ebx, ecx, edx;
      asm volatile("cpuid" 
      : "=a" (eax), "=b" (ebx), "=c" (ecx), "=d" (edx)
      : "a" (info));

      if (eaxp)
        *eaxp = eax;
      if (ebxp)
        *ebxp = ebx;
      if (ecxp)
        *ecxp = ecx;
      if (edxp)
        *edxp = edx;
    }
  }
}

#else

#define SEG_NULL						\
	.word 0, 0;						\
	.byte 0, 0, 0, 0

#define SEG32(type,base,lim)				\
	.word (((lim) >> 12) & 0xffff), ((base) & 0xffff);	\
	.byte (((base) >> 16) & 0xff), (0x90 | (type)),		\
		(0xC0 | (((lim) >> 28) & 0xf)), (((base) >> 24) & 0xff)

#define SEG64(type,base,lim)				\
	.word (((lim) >> 12) & 0xffff), ((base) & 0xffff);	\
	.byte (((base) >> 16) & 0xff), (0x90 | (type)),		\
		(0xE0 | (((lim) >> 28) & 0xf)), (((base) >> 24) & 0xff)

#define STA_X 0x8 // Executable segment
#define STA_E 0x4 // Expand down (non-executable segments)
#define STA_C 0x4 // Conforming code segment (executable only)
#define STA_W 0x2 // Writeable (non-executable segments)
#define STA_R 0x2 // Readable (executable segments)
#define STA_A 0x1 // Accessed
#endif
