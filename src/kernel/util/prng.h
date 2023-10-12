#pragma once

uint32_t prng_rand_next = 1;  
 
uint32_t PRNGrand()
{
    prng_rand_next = prng_rand_next * 1103515245 + 12345;
    return (uint32_t) (prng_rand_next / 65536) % 32768;
}
 
void PRNGsrand(uint32_t seed)
{
    prng_rand_next = seed;
}

static uint16_t prng_wh_seed[3]; // 0 - 30000

float PRNGWichmannHill() 
{
    prng_wh_seed[0] = (171 * prng_wh_seed[0]) % 30269;
    prng_wh_seed[1] = (172 * prng_wh_seed[1]) % 30307;
    prng_wh_seed[2] = (170 * prng_wh_seed[2]) % 30323;
    return fmod(prng_wh_seed[0] / 30269.0 + prng_wh_seed[1] / 30307.0 + prng_wh_seed[2] / 30323.0, 1.0);
}

void PRNGWichmannHillSetSeed(uint16_t seed0, uint16_t seed1, uint16_t seed2)
{
    prng_wh_seed[0] = seed0;
    prng_wh_seed[1] = seed1;
    prng_wh_seed[2] = seed2;
}

uint16_t start_state = 0xACE1;
uint16_t PRNGLFSR()
{
    uint16_t xor = 0b1100101111001110;
    uint16_t r = 0;

    for(unsigned int i = 0; i < 16; i++)
    {
        start_state ^= xor;
        start_state = (uint16_t)((int16_t)start_state * -1);
        uint16_t bit = (start_state & 1);
        r |= (bit << i);
        start_state >>= 1;
        start_state |= (bit << 15);
    }

    return r;
}