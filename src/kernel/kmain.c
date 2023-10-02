#include "defs.h"
#include "io.h"
#include "string.h"
#include "textio.c"

int kmain();

void kernel()
{
    kmain();
}

int kmain()
{
    SetTextColor(FG_LIGHTRED | BG_BLACK);
    puts("Hello world !");
    return 0;
}