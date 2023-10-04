#pragma once

#include "defs.h"

#pragma pack(1)
struct MemoryBlockHeader
{
    bool free;
    uint16_t size;
};

void* malloc(size_t size)
{
    return NULL;
}