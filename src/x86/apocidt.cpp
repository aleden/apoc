#include "apoctextgraphics.h"
#include "apocconsole.h"
#include "apocstream.h"
#include "apockernel.h"
#include "apocstring.h"
#include "apocprocess.h"
#include "apockeyboard.h"
#include "x86/apocx86.h"
#include "x86/apocidt.h"
#include "x86/apocgdt.h"
#include "x86/apocint.h"

namespace Apoc
{
  namespace Keyboard
  {
    void IRQ();
  }

  namespace X86
  {
    namespace IDT
    {
      static const UInt IDT_BASE = 0x500;
      static const UInt NUM_INTERRUPTS = 255;

      // IDTR register format, points to IDTDescriptor
      #pragma pack(push, 1)
      struct IDTR
      {
	// Size of IDT
	UInt16 limit;

	// Base address of IDT
	UInt base;
      };
      #pragma pack (pop)

      #define HANDLE_EXCEPTION(REASON) \
        if (ProcessManager::IsProcessRunning()) \
	  ProcessManager::HandleException(Exception(REASON)); \
	else \
	  Kernel::Halt(REASON);

      static void DivideErrorException()
      {
        HANDLE_EXCEPTION("Divide error");
      }

      static void DebugException()
      {
        HANDLE_EXCEPTION("Debug");
      }

      static void NMIInterrupt()
      {
        Kernel::Log("NMI Interrupt");
      }

      static void BreakpointException()
      {
        HANDLE_EXCEPTION("Breakpoint");
      }

      static void OverflowException()
      {
        HANDLE_EXCEPTION("Overflow");
      }

      static void BoundRangeExceededException()
      {
        HANDLE_EXCEPTION("Bound range exceeded");
      }
      
      static void InvalidOpcodeException()
      {
        HANDLE_EXCEPTION("Invalid opcode");
      }

      static void DeviceNotAvailableException()
      {
        HANDLE_EXCEPTION("Device not available");
      }

      static void DoubleFaultException()
      {
        HANDLE_EXCEPTION("Double fault");
      }

      static void CoprocessorSegmentOverrun()
      {
        HANDLE_EXCEPTION("Coprocessor segment overrun");
      }

      static void InvalidTSSException()
      {
        HANDLE_EXCEPTION("Invalid TSS exception");
      }

      static void SegmentationFaultException()
      {
        HANDLE_EXCEPTION("Segmentation fault");
      }

      static void StackFaultException()
      {
        HANDLE_EXCEPTION("Stack fault");
      }

      static void GeneralProtectionException()
      {
        HANDLE_EXCEPTION("General protection");
      }

      static void PageFaultException()
      {
        HANDLE_EXCEPTION("Page fault");
      }
      
      static void Int15()
      {
        HANDLE_EXCEPTION("Int15");
      }

      static void FPUFloatingPointException()
      {
        HANDLE_EXCEPTION("FPU floating point");
      }

      static void AlignmentCheckException()
      {
        HANDLE_EXCEPTION("Alignment check");
      }

      static void MachineCheckException()
      {
        HANDLE_EXCEPTION("Machine check");
      }

      static void SIMDFloatingPointException()
      {
        HANDLE_EXCEPTION("SIMD floating point");
      }

      void HandleIRQ(UInt irqNumber)
      {
        switch (irqNumber)
	{
	  case 1:
	    Keyboard::IRQ();
	    break;
	}
      }

      #define DINT(NUM) static void Int ## NUM() { Kernel::GetConsole()->GetOutputStream()->WriteString("Int" #NUM ); }
      DINT(20);
      DINT(21);
      DINT(22);
      DINT(23);
      DINT(24);
      DINT(25);
      DINT(26);
      DINT(27);
      DINT(28);
      DINT(29);
      DINT(30);
      DINT(31);

      #define SetBuiltinInterrupt(ROUTINE, INDEX) InstallInterrupt((Interrupt)(ROUTINE), INDEX, DESCRIPTOR_FLAG_PRESENT | DESCRIPTOR_FLAG_BIT32, GDT::DEFAULT_CODE_SELECTOR);

      void Initialize()
      {
        SetBuiltinInterrupt(DivideErrorException, 0);
        SetBuiltinInterrupt(DebugException, 1);
        SetBuiltinInterrupt(NMIInterrupt, 2);
        SetBuiltinInterrupt(BreakpointException, 3);
        SetBuiltinInterrupt(OverflowException, 4);
        SetBuiltinInterrupt(BoundRangeExceededException, 5);
        SetBuiltinInterrupt(InvalidOpcodeException, 6);
        SetBuiltinInterrupt(DeviceNotAvailableException, 7);
        SetBuiltinInterrupt(DoubleFaultException, 8);
        SetBuiltinInterrupt(CoprocessorSegmentOverrun, 9);
        SetBuiltinInterrupt(InvalidTSSException, 10);
        SetBuiltinInterrupt(SegmentationFaultException, 11);
        SetBuiltinInterrupt(StackFaultException, 12);
        SetBuiltinInterrupt(GeneralProtectionException, 13);
        SetBuiltinInterrupt(PageFaultException, 14);
        SetBuiltinInterrupt(Int15, 15);
        SetBuiltinInterrupt(FPUFloatingPointException, 16);
        SetBuiltinInterrupt(AlignmentCheckException, 17);
        SetBuiltinInterrupt(MachineCheckException, 18);
        SetBuiltinInterrupt(SIMDFloatingPointException, 19);
        SetBuiltinInterrupt(Int20, 20);
        SetBuiltinInterrupt(Int21, 21);
        SetBuiltinInterrupt(Int22, 22);
        SetBuiltinInterrupt(Int23, 23);
        SetBuiltinInterrupt(Int24, 24);
        SetBuiltinInterrupt(Int25, 25);
        SetBuiltinInterrupt(Int26, 26);
        SetBuiltinInterrupt(Int27, 27);
        SetBuiltinInterrupt(Int28, 28);
        SetBuiltinInterrupt(Int29, 29);
        SetBuiltinInterrupt(Int30, 30);
        SetBuiltinInterrupt(Int31, 31);
        SetBuiltinInterrupt(irq_0, 32);
        SetBuiltinInterrupt(irq_1, 33);
        SetBuiltinInterrupt(irq_2, 34);
        SetBuiltinInterrupt(irq_3, 35);
        SetBuiltinInterrupt(irq_4, 36);
        SetBuiltinInterrupt(irq_5, 37);
        SetBuiltinInterrupt(irq_6, 38);
        SetBuiltinInterrupt(irq_7, 39);
        SetBuiltinInterrupt(irq_8, 40);
        SetBuiltinInterrupt(irq_9, 41);
        SetBuiltinInterrupt(irq_10, 42);
        SetBuiltinInterrupt(irq_11, 43);
        SetBuiltinInterrupt(irq_12, 44);
        SetBuiltinInterrupt(irq_13, 45);
        SetBuiltinInterrupt(irq_14, 46);
        SetBuiltinInterrupt(irq_15, 47);
        SetBuiltinInterrupt(irq_16, 48);

        const IDTR idtr = {sizeof(Descriptor)*NUM_INTERRUPTS, IDT_BASE};

        LIDT(&idtr);
      }

      volatile Descriptor* GetDescriptor(UInt8 index)
      { return ((volatile Descriptor*)IDT_BASE) + index; }

      Interrupt* GetInterrupt(UInt8 index)
      {
#if APOC_ARCH == APOC_ARCH_X86_64
        return (Interrupt*)(((UInt)GetDescriptor(index)->baseLow) | (((UInt)GetDescriptor(index)->baseMiddle << 16) & ((UInt)GetDescriptor(index)->baseHigh << 32)));
#elif APOC_ARCH == APOC_ARCH_X86_32
        return (Interrupt*)(((UInt)GetDescriptor(index)->baseLow) | (((UInt)GetDescriptor(index)->baseHigh) << 16));
#endif
      }

      void InstallInterrupt(Interrupt interrupt, UInt8 index, UInt8 flags, UInt16 codeSelector)
      {
        volatile Descriptor* idt = GetDescriptor(index);
        idt->reserved     = 0;
        idt->flags        = flags;
        idt->codeSelector = codeSelector;
        idt->baseLow      = static_cast<UInt16>(reinterpret_cast<UInt>(interrupt) & 0xFFFF);
#if APOC_ARCH == APOC_ARCH_X86_64
        idt->reserved2    = 0;
        idt->baseMiddle   = static_cast<UInt16>((reinterpret_cast<UInt>(interrupt) >> 16) & 0xFFFF);
        idt->baseHigh     = static_cast<UInt32>((reinterpret_cast<UInt>(interrupt) >> 32) & 0xFFFFFFFF);
#elif APOC_ARCH == APOC_ARCH_X86_32
        idt->baseHigh     = static_cast<UInt16>((reinterpret_cast<UInt>(interrupt) >> 16) & 0xFFFF);
#endif
      }

      UInt GetIDTBase()
      { return IDT_BASE; }

      UInt GetNumInterrupts()
      { return NUM_INTERRUPTS; }
    }
  }
}
