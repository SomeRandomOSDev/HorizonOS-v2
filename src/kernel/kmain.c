#include "defs.h"
#include "textio.h"

void kernel()
{
    kmain();
}

int kmain()
{
    putc('B');
    return 0;
}