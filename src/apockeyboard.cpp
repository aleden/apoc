#include "x86/apocx86.h"
#include "x86/apocint.h"
#include "apocwindowmanager.h"
#include "apocarray.h"
#include "apoctextgraphics.h"
#include "apocinqueuestream.h"
#include "apockernel.h"
#include "apocconsole.h"
#include "apocstream.h"

namespace Apoc
{
  namespace Keyboard
  {
    enum CONTROLLER_STATUS
    {
      CONTROLLER_STATUS_OUT_BUF  = 1 << 0,
      CONTROLLER_STATUS_IN_BUF   = 1 << 1,
      CONTROLLER_STATUS_SYSTEM   = 1 << 2,
      CONTROLLER_STATUS_CMD_DATA = 1 << 3,
      CONTROLLER_STATUS_LOCKED   = 1 << 4,
      CONTROLLER_STATUS_AUX_BUF  = 1 << 5,
      CONTROLLER_STATUS_TIMEOUT  = 1 << 6,
      CONTROLLER_STATUS_PARITY   = 1 << 7
    };

    enum ENCODER_IO_PORT
    {
      ENCODER_IO_PORT_INPUT_BUFFER = 0x60,
      ENCODER_IO_PORT_CMD_REG      = 0x60
    };

    enum CONTROLLER_IO_PORT
    {
      CONTROLLER_IO_PORT_STATUS_REG = 0x64,
      CONTROLLER_IO_PORT_CMD_REG    = 0x64
    };

    enum ENCODER_COMMAND
    {
      ENCODER_COMMAND_SET_LEDS                                          = 0xED,
      ENCODER_COMMAND_ECHO                                              = 0xEE,
      ENCODER_COMMAND_SET_ALTERNATE_SCAN_CODE                           = 0xF0,
      ENCODER_COMMAND_SEND_2KEYBOARD_ID_CODE                            = 0xF2,
      ENCODER_COMMAND_SET_AUTO_REPEAT_RATE_AND_DELAY                    = 0xF3,
      ENCODER_COMMAND_ENABLE_KEYBOARD                                   = 0xF4,
      ENCODER_COMMAND_RESET_TO_POWER_ON_WAIT_FOR_ENABLE                 = 0xF5,
      ENCODER_COMMAND_RESET_AND_SCAN                                    = 0xF6,
      ENCODER_COMMAND_SET_ALL_AUTOREPEAT_PS2                            = 0xF7,
      ENCODER_COMMAND_SET_SEND_MAKE_AND_BREAK_CODES_PS2                 = 0xF8,
      ENCODER_COMMAND_SET_SEND_MAKE_CODES                               = 0xF9,
      ENCODER_COMMAND_SET_ALL_AUTOREAPEAT_AND_SEND_MAKE_AND_BREAK_CODES = 0xFA,
      ENCODER_COMMAND_SET_KEY_AUTOREPEAT                                = 0xFB,
      ENCODER_COMMAND_SET_KEY_SEND_MAKE_AND_BREAK_CODES                 = 0xFC,
      ENCODER_COMMAND_SET_KEY_SEND_BREAK_CODE                           = 0xFD,
      ENCODER_COMMAND_RESEND                                            = 0xFE,
      ENCODER_COMMAND_RESET_AND_SELF_TEST                               = 0xFF
    };

    enum CONTROLLER_COMMAND
    {
      CONTROLLER_COMMAND_READ             = 0x20,
      CONTROLLER_COMMAND_WRITE            = 0x60,
      CONTROLLER_COMMAND_SELF_TEST        = 0xAA,
      CONTROLLER_COMMAND_INTERFACE_TEST   = 0xAB,
      CONTROLLER_COMMAND_DISABLE          = 0xAD,
      CONTROLLER_COMMAND_ENABLE           = 0xAE,
      CONTROLLER_COMMAND_READ_IN_PORT     = 0xC0,
      CONTROLLER_COMMAND_READ_OUT_PORT    = 0xD0,
      CONTROLLER_COMMAND_WRITE_OUT_PORT   = 0xD1,
      CONTROLLER_COMMAND_READ_TEST_INPUTS = 0xE0,
      CONTROLLER_COMMAND_SYSTEM_RESET     = 0xFE,
      CONTROLLER_COMMAND_MOUSE_DISABLE    = 0xA7,
      CONTROLLER_COMMAND_MOUSE_ENABLE     = 0xA8,
      CONTROLLER_COMMAND_MOUSE_PORT_TEST  = 0xA9,
      CONTROLLER_COMMAND_MOUSE_WRITE      = 0xD4
    };

    enum SCAN_ERROR_CODE
    {
      SCAN_ERROR_CODE_BUF_OVERRUN = 0,
      SCAN_ERROR_CODE_ID_RET      = 0x83AB,
      SCAN_ERROR_CODE_BAT         = 0xAA,
      SCAN_ERROR_CODE_ECHO_RET    = 0xEE,
      SCAN_ERROR_CODE_ACK         = 0xFA,
      SCAN_ERROR_CODE_BAT_FAILED  = 0xFC,
      SCAN_ERROR_CODE_DIAG_FAILED = 0xFD,
      SCAN_ERROR_CODE_RESEND_CMD  = 0xFE,
      SCAN_ERROR_CODE_KEY         = 0xFF
    };

    // Original XT scan code set
    static Int MakeCodesToKeys[] =
    {
      -1,
      KEY_ESCAPE,
      KEY_1,
      KEY_2,
      KEY_3,
      KEY_4,
      KEY_5,
      KEY_6,
      KEY_7,
      KEY_8,
      KEY_9,
      KEY_0,
      KEY_MINUS,
      KEY_EQUAL,
      KEY_BACKSPACE,
      KEY_TAB,
      KEY_Q,
      KEY_W,
      KEY_E,
      KEY_R,
      KEY_T,
      KEY_Y,
      KEY_U,
      KEY_I,
      KEY_O,
      KEY_P,
      KEY_LEFT_BRACKET,
      KEY_RIGHT_BRACKET,
      KEY_RETURN,
      KEY_LCTRL,
      KEY_A,
      KEY_S,
      KEY_D,
      KEY_F,
      KEY_G,
      KEY_H,
      KEY_J,
      KEY_K,
      KEY_L,
      KEY_SEMICOLON,
      KEY_QUOTE,
      KEY_GRAVE,
      KEY_LSHIFT,
      KEY_BACKSLASH,
      KEY_Z,
      KEY_X,
      KEY_C,
      KEY_V,
      KEY_B,
      KEY_N,
      KEY_M,
      KEY_COMMA,
      KEY_DOT,
      KEY_SLASH,
      KEY_RSHIFT,
      KEY_KP_ASTERISK,
      KEY_RALT,
      KEY_SPACE,
      KEY_CAPS_LOCK,
      KEY_F1,
      KEY_F2,
      KEY_F3,
      KEY_F4,
      KEY_F5,
      KEY_F6,
      KEY_F7,
      KEY_F8,
      KEY_F9,
      KEY_F10,
      KEY_KP_NUM_LOCK,
      KEY_SCROLL_LOCK,
      KEY_HOME,
      KEY_KP_8,
      KEY_PAGE_UP,
      KEY_KP_2,
      KEY_KP_3,
      KEY_KP_0,
      KEY_KP_DECIMAL,
      -1,
      -1,
      -1,
      KEY_PAGE_DOWN,
      KEY_F11,
      KEY_F12
    };

    UInt8 ledMask = 0;
    bool isCapsLock = false, isNumLock = false, isScrollLock = false, isShift = false;
    UInt capsCount = 0;
    Queue<Character> text;
    Queue<KEY> keyPresses;
    Queue<KEY> keyReleases;
    InQueueStream<KEY> keyPressStream(&keyPresses);
    InQueueStream<KEY> keyReleaseStream(&keyReleases);
    InQueueStream<Character> textStream(&text);

    static inline UInt8 ReadControllerStatus()
    { return X86::INB(CONTROLLER_IO_PORT_STATUS_REG); }

    static inline UInt8 ReadEncoderBuffer()
    { return X86::INB(ENCODER_IO_PORT_INPUT_BUFFER); }

    static inline void WaitToSendCommand()
    {
      while (1)
      {
        if ((ReadControllerStatus () & CONTROLLER_STATUS_IN_BUF) == 0)
          break;
      }
    }

    static inline void SendControllerCommand(UInt8 command)
    {
      WaitToSendCommand();
      X86::OUTB(CONTROLLER_IO_PORT_CMD_REG, command);
    }

    static inline void SendEncoderCommand(UInt8 command)
    {
      WaitToSendCommand();
      X86::OUTB(ENCODER_IO_PORT_CMD_REG, command);
    }

    static inline void UpdateLEDs()
    {
      SendEncoderCommand(ENCODER_COMMAND_SET_LEDS);
      SendEncoderCommand(static_cast<UInt8>(ledMask));
    }

    void Initialize()
    {
      X86::IDT::InstallInterrupt((X86::IDT::Interrupt)irq_1, 33, X86::IDT::DESCRIPTOR_FLAG_BIT32 | X86::IDT::DESCRIPTOR_FLAG_PRESENT, X86::GDT::DEFAULT_CODE_SELECTOR);
      Enable();
    }

    void IRQ()
    {
      bool isBreak = false;
      KEY key;

      // Read scan code only if the kkybrd controller output buffer is full
      if (!(ReadControllerStatus() & CONTROLLER_STATUS_OUT_BUF))
        return;

      // Read the scan code
      UInt code = ReadEncoderBuffer();

      // Is this not an extended code?
      if (code != 0xE0 && code != 0xE1)
      {
        // Either the second byte of an extended scan code or a single byte scan code

        // Test if this is a break code (Original XT Scan Code Set specific)
        if (code & 0x80)
        {
          // Convert the break code into its make code equivelant
          code -= 0x80;
          isBreak = true;
        }

        // Get key
        key = static_cast<KEY>(MakeCodesToKeys[code]);

        if (isBreak)
        {
          keyReleases.Enqueue(key);

          WindowManager::OnKeyRelease();
        }
        else
        {
#if 0
          {
            Int8 buff[0xFF];
            Kernel::GetConsole()->GetOutStream()->WriteString(HexadecimalString(code, buff));
            Kernel::GetConsole()->GetOutStream()->Flush();
          }
#endif
          keyPresses.Enqueue(key);

          if (IsKeyPrintable(key))
          {
            Int8 character;

            if (isShift)
              character = shiftedKeyToCharTable[key];
            else
              character = keyToCharTable[key];

            text.Enqueue(character);
          }

          WindowManager::OnKeyPress();
        }

        switch (key)
        {
          case KEY_LSHIFT:
          case KEY_RSHIFT:
            isShift = !isBreak;
            break;

          case KEY_CAPS_LOCK:
            //Kernel::GetConsole()->GetOutStream()->WriteString("caps");
            if (!(capsCount & 1))
            {
              isCapsLock = !isCapsLock;
              SetLED(LED_CAPS_LOCK, isCapsLock);
            }
            ++capsCount;

            break;

          case KEY_KP_NUM_LOCK:
            isNumLock = !isBreak;
            SetLED(LED_NUM_LOCK, isCapsLock);
            break;

          case KEY_SCROLL_LOCK:
            isScrollLock = !isBreak;
            SetLED(LED_SCROLL_LOCK, isScrollLock);
            break;

          default:
            break;
        }
      }
    }

    void Enable()
    { SendControllerCommand(CONTROLLER_COMMAND_ENABLE); }

    void Disable()
    { SendControllerCommand(CONTROLLER_COMMAND_DISABLE); }

    void SetLED(LED led, bool on)
    {
      ledMask = (on ? ledMask | led : ledMask & ~(1 << led));
      UpdateLEDs();
    }

    void SetLEDOn(LED led)
    {
      ledMask |= led;
      UpdateLEDs();
    }

    void SetLEDOff(LED led)
    {
      ledMask &= ~(1 << led);
      UpdateLEDs();
    }

    UInt GetInput()
    {
      return 0;
    }

    UInt GetChar()
    {
      return 0;
    }

    Stream* GetKeyPressStream()
    { return &keyPressStream; }

    Stream* GetKeyReleaseStream()
    { return &keyReleaseStream; }

    Stream* GetTextStream()
    { return &textStream; }
  }
}
