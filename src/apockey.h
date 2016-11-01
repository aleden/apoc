#pragma once

namespace Apoc
{
  enum KEY
  {
    // Printable
    KEY_0,
    KEY_1,
    KEY_2,
    KEY_3,
    KEY_4,
    KEY_5,
    KEY_6,
    KEY_7,
    KEY_8,
    KEY_9,

    KEY_A,
    KEY_B,
    KEY_C,
    KEY_D,
    KEY_E,
    KEY_F,
    KEY_G,
    KEY_H,
    KEY_I,
    KEY_J,
    KEY_K,
    KEY_L,
    KEY_M,
    KEY_N,
    KEY_O,
    KEY_P,
    KEY_Q,
    KEY_R,
    KEY_S,
    KEY_T,
    KEY_U,
    KEY_V,
    KEY_W,
    KEY_X,
    KEY_Y,
    KEY_Z,

    KEY_SPACE,
    KEY_TAB,
    KEY_KP_ENTER,
    KEY_RETURN,

    KEY_DOT,
    KEY_COMMA,
    KEY_COLON,
    KEY_SEMICOLON,
    KEY_SLASH,
    KEY_BACKSLASH,
    KEY_PLUS,
    KEY_MINUS,
    KEY_ASTERISK,
    KEY_EXCLAMATION,
    KEY_QUESTION,
    KEY_QUOTEDOUBLE,
    KEY_QUOTE,
    KEY_EQUAL,
    KEY_NUMBER_SIGN,
    KEY_PERCENT,
    KEY_AMPERSAND,
    KEY_UNDERSCORE,
    KEY_LEFT_PAREN,
    KEY_RIGHT_PAREN,
    KEY_LEFT_BRACKET,
    KEY_RIGHT_BRACKET,
    KEY_LEFT_CURL,
    KEY_RIGHT_CURL,
    KEY_DOLLAR,
    KEY_EURO,
    KEY_LESS,
    KEY_GREATER,
    KEY_BAR,
    KEY_GRAVE,
    KEY_TILDE,
    KEY_AT,
    KEY_CARRET,

    KEY_KP_0,
    KEY_KP_1,
    KEY_KP_2,
    KEY_KP_3,
    KEY_KP_4,
    KEY_KP_5,
    KEY_KP_6,
    KEY_KP_7,
    KEY_KP_8,
    KEY_KP_9,
    KEY_KP_PLUS,
    KEY_KP_MINUS,
    KEY_KP_DECIMAL,
    KEY_KP_DIVIDE,
    KEY_KP_ASTERISK,
    KEY_BACKSPACE,
    
    // Non-printable
    KEY_ESCAPE,

    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT,

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
    KEY_F11,
    KEY_F12,
    KEY_F13,
    KEY_F14,
    KEY_F15,
    KEY_KP_NUM_LOCK,

    KEY_CAPS_LOCK,

    KEY_LSHIFT,
    KEY_LCTRL,
    KEY_LALT,
    KEY_LWIN,
    KEY_RSHIFT,
    KEY_RCTRL,
    KEY_RALT,
    KEY_RWIN,

    KEY_INSERT,
    KEY_DELETE,
    KEY_HOME,
    KEY_END,
    KEY_PAGE_UP,
    KEY_PAGE_DOWN,
    KEY_SCROLL_LOCK,
    KEY_PAUSE
  };

  inline bool IsKeyPrintable(KEY key)
  { return key <= KEY_BACKSPACE; }

  const static UInt keyToCharTable[] =
  {
    '0', // KEY_0
    '1', // KEY_1
    '2', // KEY_2
    '3', // KEY_3
    '4', // KEY_4
    '5', // KEY_5
    '6', // KEY_6
    '7', // KEY_7
    '8', // KEY_8
    '9', // KEY_9

    'a', // KEY_A
    'b', // KEY_B
    'c', // KEY_C
    'd', // KEY_D
    'e', // KEY_E
    'f', // KEY_F
    'g', // KEY_G
    'h', // KEY_H
    'i', // KEY_I
    'j', // KEY_J
    'k', // KEY_K
    'l', // KEY_L
    'm', // KEY_M
    'n', // KEY_N
    'o', // KEY_O
    'p', // KEY_P
    'q', // KEY_Q
    'r', // KEY_R
    's', // KEY_S
    't', // KEY_T
    'u', // KEY_U
    'v', // KEY_V
    'w', // KEY_W
    'x', // KEY_X
    'y', // KEY_Y
    'z', // KEY_Z

    ' ', // KEY_SPACE
    '\t', // KEY_TAB
    '\n', // KEY_KP_ENTER
    '\n', // KEY_RETURN

    '.', // KEY_DOT
    ',', // KEY_COMMA
    ':', // KEY_COLON
    ';', // KEY_SEMICOLON
    '/', // KEY_SLASH
    '\\', // KEY_BACKSLASH
    '+', // KEY_PLUS
    '-', // KEY_MINUS
    '*', // KEY_ASTERISK
    '!', // KEY_EXCLAMATION
    '?', // KEY_QUESTION
    '\"', // KEY_QUOTEDOUBLE
    '\'', // KEY_QUOTE
    '=', // KEY_EQUAL
    '#', // KEY_NUMBER_SIGN
    '%', // KEY_PERCENT
    '&', // KEY_AMPERSAND
    '_', // KEY_UNDERSCORE
    '(', // KEY_LEFT_PAREN
    ')', // KEY_RIGHT_PAREN
    '[', // KEY_LEFT_BRACKET
    ']', // KEY_RIGHT_BRACKET
    '{', // KEY_LEFT_CURL
    '}', // KEY_RIGHT_CURL
    '$', // KEY_DOLLAR
    '$', // KEY_EURO
    '<', // KEY_LESS
    '>', // KEY_GREATER
    '|', // KEY_BAR
    '`', // KEY_GRAVE
    '~', // KEY_TILDE
    '@', // KEY_AT
    '^', // KEY_CARRET

    '0', // KEY_KP_0
    '1', // KEY_KP_1
    '2', // KEY_KP_2
    '3', // KEY_KP_3
    '4', // KEY_KP_4
    '5', // KEY_KP_5
    '6', // KEY_KP_6
    '7', // KEY_KP_7
    '8', // KEY_KP_8
    '9', // KEY_KP_9
    '+', // KEY_KP_PLUS
    '-', // KEY_KP_MINUS
    '.', // KEY_KP_DECIMAL
    '/', // KEY_KP_DIVIDE
    '*', // KEY_KP_ASTERISK
    '\b' // KEY_BACKSPACE
  };

  const static UInt shiftedKeyToCharTable[] =
  {
    ')', // KEY_0
    '!', // KEY_1
    '@', // KEY_2
    '#', // KEY_3
    '$', // KEY_4
    '%', // KEY_5
    '^', // KEY_6
    '&', // KEY_7
    '*', // KEY_8
    '(', // KEY_9

    'A', // KEY_A
    'B', // KEY_B
    'C', // KEY_C
    'D', // KEY_D
    'E', // KEY_E
    'F', // KEY_F
    'G', // KEY_G
    'H', // KEY_H
    'I', // KEY_I
    'J', // KEY_J
    'K', // KEY_K
    'L', // KEY_L
    'M', // KEY_M
    'N', // KEY_N
    'O', // KEY_O
    'P', // KEY_P
    'Q', // KEY_Q
    'R', // KEY_R
    'S', // KEY_S
    'T', // KEY_T
    'U', // KEY_U
    'V', // KEY_V
    'W', // KEY_W
    'X', // KEY_X
    'Y', // KEY_Y
    'Z', // KEY_Z

    ' ', // KEY_SPACE
    '\t', // KEY_TAB
    '\n', // KEY_KP_ENTER
    '\n', // KEY_RETURN

    '.', // KEY_DOT
    ',', // KEY_COMMA
    ':', // KEY_COLON
    ';', // KEY_SEMICOLON
    '/', // KEY_SLASH
    '\\', // KEY_BACKSLASH
    '+', // KEY_PLUS
    '-', // KEY_MINUS
    '*', // KEY_ASTERISK
    '!', // KEY_EXCLAMATION
    '?', // KEY_QUESTION
    '\"', // KEY_QUOTEDOUBLE
    '\'', // KEY_QUOTE
    '=', // KEY_EQUAL
    '#', // KEY_NUMBER_SIGN
    '%', // KEY_PERCENT
    '&', // KEY_AMPERSAND
    '_', // KEY_UNDERSCORE
    '(', // KEY_LEFT_PAREN
    ')', // KEY_RIGHT_PAREN
    '[', // KEY_LEFT_BRACKET
    ']', // KEY_RIGHT_BRACKET
    '{', // KEY_LEFT_CURL
    '}', // KEY_RIGHT_CURL
    '$', // KEY_DOLLAR
    '$', // KEY_EURO
    '<', // KEY_LESS
    '>', // KEY_GREATER
    '|', // KEY_BAR
    '`', // KEY_GRAVE
    '~', // KEY_TILDE
    '@', // KEY_AT
    '^', // KEY_CARRET

    '0', // KEY_KP_0
    '1', // KEY_KP_1
    '2', // KEY_KP_2
    '3', // KEY_KP_3
    '4', // KEY_KP_4
    '5', // KEY_KP_5
    '6', // KEY_KP_6
    '7', // KEY_KP_7
    '8', // KEY_KP_8
    '9', // KEY_KP_9
    '+', // KEY_KP_PLUS
    '-', // KEY_KP_MINUS
    '.', // KEY_KP_DECIMAL
    '/', // KEY_KP_DIVIDE
    '*', // KEY_KP_ASTERISK
    '\b' // KEY_BACKSPACE
  };

  inline Int8 KeyToCharacter(KEY key)
  {
    return 0;
  }
}
