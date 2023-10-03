#include "util/defs.h"
#include "util/io.h"
#include "util/memory.h"
#include "util/string.h"
#include "util/textio.c"

int kmain();

void kernel()
{
    kmain();
}

int kmain()
{
    SetTextColor(FG_WHITE | BG_BLACK);
    puts("Hello world !");
    return 0;
}