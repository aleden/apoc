#pragma once
#include "apoccommon.h"
#include "apockey.h"
#include "apocstream.h"

namespace Apoc
{
  namespace Keyboard
  {
    enum LED
    {
      LED_SCROLL_LOCK = 1 << 0,
      LED_NUM_LOCK    = 1 << 1,
      LED_CAPS_LOCK   = 1 << 2
    };

    void Initialize();

    void Enable();
    void Disable();

    void SetLED(LED, bool);
    void SetLEDOn(LED);
    void SetLEDOff(LED);

    KEY ReadKey();
    UInt ReadCharacter();

    Stream* GetKeyPressStream();
    Stream* GetKeyReleaseStream();
    Stream* GetTextStream();
  }
}
