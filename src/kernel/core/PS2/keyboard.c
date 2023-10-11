#include "keyboard.h"

#include "ps2.h"

void PS2KeyboardInit()
{
    memset(&kb_state, false, 256);
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

void PS2KBSetScancodeKeyState(uint8_t scancode, bool extended, bool state)
{
    if(extended)
        kb_state_extended[scancode] = state;
    else
        kb_state[scancode] = state;
}

bool PS2KBGetScancodeKeyState(uint8_t scancode, bool extended)
{
    if(extended)
        return kb_state_extended[scancode];
    else
        return kb_state[scancode];
}

void PS2KBSetKeyState(uint16_t key, bool state)
{
	for(uint8_t i = 0; i < 128; i++)
	{
        if(kb_layout == KB_AZERTY)
        {
            if(kb_azerty_set2[i] == key)
                PS2KBSetScancodeKeyState(i, false, state);
        }
        // else if(kb_layout == KB_QWERTY)
        // {
        //     if(kb_qwerty_set2[i] == key)
        //         PS2KBSetScancodeKeyState(i, false, state);
        // }
	}

    for(uint8_t i = 0; i < 128; i++)
	{
        if(kb_layout == KB_AZERTY)
        {
            if(kb_azerty_set2_extended[i] == key)
                PS2KBSetScancodeKeyState(i, true, state);
        }
        // else if(kb_layout == KB_QWERTY)
        // {
        //     if(kb_qwerty_set2_extended[i] == key)
        //         PS2KBSetScancodeKeyState(i, true, state);
        // }
	}
}

bool PS2KBGetKeyState(uint16_t key)
{
	bool r = false;
	for(uint8_t i = 0; i < 128; i++)
	{
		if(kb_layout == KB_AZERTY)
        {
            if(kb_azerty_set2[i] == key)
                r |= PS2KBGetScancodeKeyState(i, false);
        }
        // else if(kb_layout == KB_QWERTY)
        // {
        //     if(kb_qwerty_set2[i] == key)
        //         r |= PS2KBGetScancodeKeyState(i, false);
        // }
	}

    for(uint8_t i = 0; i < 128; i++)
	{
		if(kb_layout == KB_AZERTY)
        {
            if(kb_azerty_set2_extended[i] == key)
                r |= PS2KBGetScancodeKeyState(i, true);
        }
        // else if(kb_layout == KB_QWERTY)
        // {
        //     if(kb_qwerty_set2_extended[i] == key)
        //         r |= PS2KBGetScancodeKeyState(i, true);
        // }
	}

	return r;
}

uint16_t PS2KeyboardLookup(uint8_t scancode, bool extended)
{
    if(kb_layout == KB_AZERTY)
    {
        if(extended)
            return kb_azerty_set2_extended[scancode];
        return kb_azerty_set2[scancode];
    }
    return 0;
}

uint16_t PS2KeyboardFormattedLookup(uint8_t scancode, bool extended)
{
    if(kb_layout == KB_AZERTY)
    {
        if(extended)
            return kb_azerty_set2_extended[scancode];
        if(kb_capsLock ^ (PS2KBGetKeyState(KB_LSHIFT) || PS2KBGetKeyState(KB_RSHIFT)))
        {
            if(PS2KBGetKeyState(KB_ALT_GR))
                return 0;
            return kb_azerty_set2_caps[scancode];
        }
        else
        {
            if(PS2KBGetKeyState(KB_ALT_GR))
                return kb_azerty_set2_altgr[scancode];
            return kb_azerty_set2[scancode];
        }
    }
    return 0;
}

uint16_t PS2KBGetTextKey()
{
    if(!kb_text_key_pressed)
        return 0;

    kb_text_key_pressed = false;

    return PS2KeyboardFormattedLookup(kb_text_key, kb_text_key_extended);
}

char* PS2KeyboardReadTextInput()
{
    uint16_t cursor_start_pos = text_cursor_pos;
    char* string = (char*)malloc(64 * sizeof(char));
    uint8_t size = 0;
    while(!PS2KBGetKeyState('\n'))
    {
        if(kb_text_key_pressed)
        {
            uint16_t key = PS2KBGetTextKey();
            if((!(key == '\b' && cursor_start_pos == text_cursor_pos)))
            {
                if(key != '\b' && key != KB_DELETE && size < 64)
                {
                    if(key != '\n')
                    {
                        string[size] = key;
                        size++;
                    }
                    putc(key);
                }
                else if(key == '\b')
                {
                    size--;
                    putc('\b');
                }
            }
        }
    }

    string[size] = '\0';

    return string;
}

void PS2KeyboardHandler()
{
    uint8_t scancode = inb(PS2_DATA_PORT);

    if(scancode == 0xe0)
    {
        kb_extendedScancode = true;
        return;
    }

    if((scancode >> 7) & 1)
    {
        PS2KBSetScancodeKeyState(scancode - 0x80, kb_extendedScancode, false);
        kb_text_key_pressed = false;
    }
    else
    {
        uint16_t key = PS2KeyboardLookup(scancode, kb_extendedScancode);
        PS2KBSetScancodeKeyState(scancode, kb_extendedScancode, true);
        if(key == KB_CAPS_LOCK)
        {
            kb_capsLock ^= 1;
            PS2KBSetLEDState(KB_LED_CAPS_LOCK & (0xff * kb_capsLock));
        }
        else if(key == KB_NUMLOCK)
            kb_numLock ^= 1;
        else if(key == KB_SCROLLLOCK)
            kb_scrollLock ^= 1;
        else if(key == (key & 0xff) || (kb_numLock && (key == KB_NUMPAD_1 || key == KB_NUMPAD_2 || key == KB_NUMPAD_3 || 
                                                       key == KB_NUMPAD_4 || key == KB_NUMPAD_5 || key == KB_NUMPAD_6 || 
                                                       key == KB_NUMPAD_7 || key == KB_NUMPAD_8 || key == KB_NUMPAD_9 || 
                                                       key == KB_NUMPAD_0)))
        {
            kb_text_key = scancode;
            kb_text_key_extended = kb_extendedScancode;
            kb_text_key_pressed = true;
        }
    }

    kb_extendedScancode = false;
}