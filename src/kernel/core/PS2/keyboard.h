#pragma once

#include "ps2.h"

enum KB_LAYOUT
{
    KB_QWERTY,
    KB_AZERTY
};

bool kb_capsLock = false, kb_numLock = false, kb_scrollLock = false;
enum KB_LAYOUT kb_layout = KB_QWERTY;

#define KB_ESCAPE      27
#define KB_BACKSPACE   '\b'
#define KB_RETURN      '\n'
#define KB_CTRL        (0x0100 + 0)
#define KB_LSHIFT      (0x0100 + 1)
#define KB_RSHIFT      (0x0100 + 2)
#define KB_ALT         (0x0100 + 3)
#define KB_CAPS_LOCK   (0x0100 + 4)
#define KB_F1          (0x0100 + 5)
#define KB_F2          (0x0100 + 6)
#define KB_F3          (0x0100 + 7)
#define KB_F4          (0x0100 + 8)
#define KB_F5          (0x0100 + 9)
#define KB_F6          (0x0100 + 10)
#define KB_F7          (0x0100 + 11)
#define KB_F8          (0x0100 + 12)
#define KB_F9          (0x0100 + 13)
#define KB_F10         (0x0100 + 14)
#define KB_F11         (0x0100 + 15)
#define KB_F12         (0x0100 + 16)
#define KB_NUMLOCK     (0x0100 + 17)
#define KB_SCROLLLOCK  (0x0100 + 18)
#define KB_INSERT      (0x0100 + 27)
#define KB_DELETE      127
#define KB_NUMPAD_5    (0x0100 + 28)
#define KB_É           ((uint8_t)130)
#define KB_È           ((uint8_t)138)
#define KB_Ç           ((uint8_t)135)
#define KB_À           ((uint8_t)133)

#define KB_NUMPAD_0    (0x0100 + 38)
#define KB_NUMPAD_1    (0x0100 + 26)
#define KB_NUMPAD_2    (0x0100 + 23)
#define KB_NUMPAD_3    (0x0100 + 25)
#define KB_NUMPAD_4    (0x0100 + 21)

#define KB_NUMPAD_6    (0x0100 + 22)
#define KB_NUMPAD_7    (0x0100 + 19)
#define KB_NUMPAD_8    (0x0100 + 20)
#define KB_NUMPAD_9    (0x0100 + 24)

// Extended keys
#define KB_HOME        (0x0100 + 30)
#define KB_UP          (0x0100 + 31)
#define KB_LEFT        (0x0100 + 32)
#define KB_RIGHT       (0x0100 + 33)
#define KB_DOWN        (0x0100 + 34)
#define KB_PAGEUP      (0x0100 + 35)
#define KB_PAGEDOWN    (0x0100 + 36)
#define KB_END         (0x0100 + 37)

#define KB_ALT_GR      (0x0100 + 38)

#define KB_LED_SCROLL_LOCK (1 << 0)
#define KB_LED_NUM_LOCK    (1 << 1)
#define KB_LED_CAPS_LOCK   (1 << 2)

#define KB_ACK      0xfa
#define KB_RESEND   0xfe

#define KB_SCANCODE_SET_1   1
#define KB_SCANCODE_SET_2   2
#define KB_SCANCODE_SET_3   3

uint16_t kb_qwerty_set2[128] =
{
    0,  KB_ESCAPE, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', 
    '-', '=', '\b', '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 
    'i', 'o', 'p', '[', ']', '\n', KB_CTRL, 'a', 's', 'd', 
    'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', KB_LSHIFT, 
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 
    KB_RSHIFT, '*', KB_ALT, ' ', KB_CAPS_LOCK, KB_F1, KB_F2, 
    KB_F3, KB_F4, KB_F5, KB_F6, KB_F7, KB_F8, KB_F9, KB_F10,
    KB_NUMLOCK, KB_SCROLLLOCK, KB_NUMPAD_7, KB_NUMPAD_8, KB_NUMPAD_9, '-', 
    KB_NUMPAD_4, KB_NUMPAD_5, KB_NUMPAD_6, '+', KB_NUMPAD_1, KB_NUMPAD_2, KB_NUMPAD_3,
    KB_NUMPAD_0, '.', 0, 0, 0, KB_F11, KB_F12,
    //Extended :
    KB_RIGHT, KB_UP, KB_LEFT, KB_DOWN, KB_DELETE, KB_INSERT, KB_ALT_GR
};	

uint16_t kb_azerty_set2[128] =
{
    0,  KB_ESCAPE, '&', KB_É, '\"', '\'', '(', '-', KB_È, '_', KB_Ç, KB_À, ')', '=', '\b', '\t', 
    'a', 'z', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '^', '$', '\n', KB_CTRL, 'q', 's', 
    'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', '%', 0, KB_LSHIFT, '*', 'w', 'x', 'c', 'v', 
    'b', 'n', ',', ';', ':', '!', KB_RSHIFT, '*', KB_ALT, ' ', KB_CAPS_LOCK, KB_F1, KB_F2, KB_F3, KB_F4, KB_F5, 
    KB_F6, KB_F7, KB_F8, KB_F9, KB_F10, KB_NUMLOCK, KB_SCROLLLOCK, KB_NUMPAD_7, KB_NUMPAD_8, KB_NUMPAD_9, '-', KB_NUMPAD_4, KB_NUMPAD_5, KB_NUMPAD_6, '+', KB_NUMPAD_1, 
    KB_NUMPAD_2, KB_NUMPAD_3, KB_NUMPAD_0, '.', 0, 0, 0, KB_F11, KB_F12,
    //Extended :
    KB_RIGHT, KB_UP, KB_LEFT, KB_DOWN, KB_DELETE, KB_INSERT, KB_ALT_GR
};	

bool kb_state[128] =
{
    false,
};

bool kb_extendedScancode = false;

void PS2KeyboardInit()
{
    memset(&kb_state, false, 128);
}

void PS2KBSetLEDState(uint8_t state)
{
	PS2Wait();
	outb(PS2_DATA_PORT, 0xed);
    io_wait();
	outb(PS2_DATA_PORT, state);
    io_wait();
	if(inb(PS2_DATA_PORT) == KB_RESEND)
		PS2KBSetLEDState(state);
}

bool PS2KBResetKeyboard()
{
	PS2Wait();
	outb(PS2_DATA_PORT, 0xff);
    io_wait();
	if(inb(PS2_DATA_PORT) == KB_RESEND)
		return PS2KBResetKeyboard();
	return (inb(PS2_DATA_PORT) == 0xaa);
}

void PS2KBSetScancodeSet(uint8_t set)
{
	PS2Wait();
	outb(PS2_DATA_PORT, 0xf0);
    io_wait();
	outb(PS2_DATA_PORT, set);
    io_wait();
	if(inb(PS2_DATA_PORT) == KB_RESEND)
		PS2KBSetScancodeSet(set);
}

uint8_t PS2KBGetScancodeSet()
{
	PS2Wait();
	outb(PS2_DATA_PORT, 0xf0);
    io_wait();
	outb(PS2_DATA_PORT, 0);
	if(inb(PS2_DATA_PORT) == KB_RESEND)
		return PS2KBGetScancodeSet();
	uint8_t r = inb(PS2_DATA_PORT);
	return r == 0x43 ? KB_SCANCODE_SET_1 : (r == 0x41 ? KB_SCANCODE_SET_2 : KB_SCANCODE_SET_3 /*3f*/);
}

uint16_t PS2KeyboardLookup(uint8_t key)
{
	if(kb_layout == KB_QWERTY)
		return kb_qwerty_set2[key];
	if(kb_layout == KB_AZERTY)
		return kb_azerty_set2[key];
	return 0;
}

void PS2KBSetScancodeKeyState(uint8_t scancode, bool state)
{
    kb_state[scancode] = state;
}

bool PS2KBGetScancodeKeyState(uint8_t scancode)
{
    return kb_state[scancode];
}

void PS2KBSetKeyState(uint16_t key, bool state)
{
	for(uint8_t i = 0; i < 128; i++)
	{
		if(PS2KeyboardLookup(i) == key)
			PS2KBSetScancodeKeyState(i, state);
	}
}

bool PS2KBGetKeyState(uint16_t key)
{
	bool r = false;
	for(uint8_t i = 0; i < 128; i++)
	{
		if(PS2KeyboardLookup(i) == key)
			r |= PS2KBGetScancodeKeyState(i);
	}
	return r;
}

uint16_t kb_text_key;
bool     kb_text_key_pressed = false;

uint16_t PS2KBGetTextKey()
{
    if(!kb_text_key_pressed)
        return 0;

    kb_text_key_pressed = false;

    uint16_t formattedKey = kb_text_key;
    if(kb_capsLock ^ (PS2KBGetKeyState(KB_LSHIFT) || PS2KBGetKeyState(KB_RSHIFT)))
        ;
    
    return formattedKey;
}

void PS2KeyboardReadTextInput()
{
    uint16_t cursor_start_pos = text_cursor_pos;
    while(true)
    {
        if(kb_text_key_pressed)
        {
            uint16_t key = PS2KBGetTextKey();
            if(!(key == '\b' && cursor_start_pos == text_cursor_pos))
                putc(key);
        }
    }
}

void PS2KeyboardHandler()
{
    uint8_t scancode = inb(PS2_DATA_PORT);
    uint16_t key = kb_azerty_set2[scancode];

    if(scancode == 0xe0)
    {
        kb_extendedScancode = true;
        return;
    }

    if(scancode >> 7)
    {
        PS2KBSetScancodeKeyState(scancode - 0x80, false);
    }
    else
    {
        PS2KBSetScancodeKeyState(scancode, true);
        if(key == KB_CAPS_LOCK)
            kb_capsLock ^= 1;
        else if(key == KB_NUMLOCK)
            kb_numLock ^= 1;
        else if(key == KB_SCROLLLOCK)
            kb_scrollLock ^= 1;
        else if(key == (key & 0xff))
        {
            kb_text_key = key;
            kb_text_key_pressed = true;
        }

        PS2KBSetLEDState(KB_LED_CAPS_LOCK * kb_capsLock);
    }

    kb_extendedScancode = false;
}