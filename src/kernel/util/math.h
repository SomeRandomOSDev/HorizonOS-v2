#pragma once

double floor(double x)
{
    return (double)((int)x);
}

double ceil(double x)
{
    if(x == floor(x))
        return x;
    return floor(x) + 1;
}

double round(double x)
{
    return floor(x + 0.5);
}

float floorf(float x)
{
    return (float)((int)x);
}

float ceilf(float x)
{
    if(x == floor(x))
        return x;
    return floor(x) + 1;
}

float roundf(float x)
{
    return floor(x + 0.5f);
}

double abs(double x)
{
    return (x >= 0 ? x : x * -1);
}