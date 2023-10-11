#pragma once

#include "math.h"
#include "string.h"
#include "textio.h"

#define FREE_MEMORY_START 0x01000000
#define FREE_MEMORY_END   0x0a000000//0xc0000000 
#define BLOCK_SIZE        64
#define NUM_BLOCKS        ((FREE_MEMORY_END - FREE_MEMORY_START) / BLOCK_SIZE)

uint8_t bitmap[(uint32_t)(NUM_BLOCKS / 8)];
uint8_t bitmap_firstblock[(uint32_t)(NUM_BLOCKS / 8)];

void InitMemory()
{
    memset(&bitmap,            0xff, NUM_BLOCKS / 8);
    memset(&bitmap_firstblock, 0x00, NUM_BLOCKS / 8);
}

void setBlockStatus(uint32_t block, bool free, bool firstBlock)
{
    uint32_t i = block / 8, j = block % 8;
    
    if(!free)
    {
        uint8_t mask = ~(1 << j);
        bitmap[i] &= mask;
    }
    else
        bitmap[i] |= (1 << j);

    if(!firstBlock)
    {
        uint8_t mask = ~(1 << j);
        bitmap_firstblock[i] &= mask;
    }
    else
        bitmap_firstblock[i] |= (1 << j);
}

void getBlockStatus(uint32_t block, bool* free, bool* firstBlock)
{
    uint32_t i = block / 8, j = block % 8;
    if(free != NULL)
        (*free) = (bitmap[i] >> j) & 0b1;
    if(firstBlock != NULL)
        (*firstBlock) = (bitmap_firstblock[i] >> j) & 0b1;
}

void printMemState(uint32_t block)
{
    DisableCursor();
    SetCursorPos(0, 0);
    for(uint32_t i = 0; i < 80 * 25 && i < (NUM_BLOCKS / 8); i++)
    {
        bool isFree, firstBlock;
        getBlockStatus(block + i, &isFree, &firstBlock);
        if(isFree)
            SetTextColor(BG_LIGHTGREEN);
        else
            SetTextColor(BG_LIGHTBLUE);

        if(firstBlock)
            putc('#');
        else
            putc('+');
    }

    while(true);
}

uint32_t SwitchEndian32(uint32_t nb)
{
    return ((nb>> 24) & 0xff) | ((nb << 8) & 0xff0000) | ((nb >> 8) & 0xff00) | ((nb << 24) & 0xff000000);
}

void memDump(void* address)
{
    uint32_t* ptr = (uint32_t*)address;

    ClearScreen(BG_BLACK | FG_WHITE);

    DisableCursor();
    SetCursorPos(0, 0);

    for(uint8_t i = 0; i < 25; i++)
    {
        printf("0x%x : %x%x %x%x %x%x %x%x", (uint32_t)ptr,
SwitchEndian32(ptr[0]), SwitchEndian32(ptr[1]), SwitchEndian32(ptr[2]), SwitchEndian32(ptr[3]), 
SwitchEndian32(ptr[4]), SwitchEndian32(ptr[5]), SwitchEndian32(ptr[6]), SwitchEndian32(ptr[7]));
        ptr += 8;
        //ptr = (uint32_t*)(address + 8 * i);
    }

    while(true);
}

void* malloc(size_t size)
{
    uint32_t neededBlocks = ceil(size / (float)BLOCK_SIZE);
    uint32_t consecutiveBlocks = 0;
    uint32_t lastBlock = 0;
    for(uint32_t i = 0; i < NUM_BLOCKS; i++)
    {
        bool isFree;
        getBlockStatus(i, &isFree, NULL);
        if(isFree)
            consecutiveBlocks++;
        else
        {
            consecutiveBlocks = 0;
            lastBlock = i + 1;
        }
        if(consecutiveBlocks >= neededBlocks)
        {       
            setBlockStatus(lastBlock, false, true);
            for(uint32_t j = 1; j < neededBlocks; j++)
                setBlockStatus(lastBlock + j, false, false);
            return (void*)(FREE_MEMORY_START + lastBlock * BLOCK_SIZE);
        }
    }

    return NULL;
}

void free(void* ptr)
{
    uint32_t blockID = ((uint32_t)ptr - FREE_MEMORY_START) / BLOCK_SIZE;

    setBlockStatus(blockID, true, false);

    bool nextBlock = false, isFree = false;

    blockID++;

    while((!nextBlock) && (!isFree))
    {
        getBlockStatus(blockID, &isFree, &nextBlock);

        if((!nextBlock) && (!isFree))
            setBlockStatus(blockID, true, false);

        blockID++;
    }
}