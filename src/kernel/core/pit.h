#pragma once

#define PIT_CHANNEL_0_DATA  0x40
#define PIT_CHANNEL_1_DATA  0x41
#define PIT_CHANNEL_2_DATA  0x42
#define PIT_MODE_CMD        0x43

uint32_t globalTimer = 0; // 1/100 seconds

void TimerHandler()
{
    globalTimer += 1;
}

void PITSetFrequency(uint32_t frequency)
{
    uint32_t divisor = 1193180 / frequency;
    outb(PIT_MODE_CMD,       0x36);            
    io_wait();
    outb(PIT_CHANNEL_0_DATA, divisor & 0xff);   
    io_wait();
    outb(PIT_CHANNEL_0_DATA, divisor >> 8);   
    io_wait(); 
}

void Sleep(float seconds)
{
    uint32_t targetTimer = globalTimer + (seconds * 100);

    while(targetTimer > globalTimer);
}