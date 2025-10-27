#include "../philo.h"

long convert_ms_us(long ms)
{
    return (ms * 1000);
}

long convert_us_ms(long us)
{
    return (us / 1000);
}

long convert_sec_ms(long sec)
{
    return (sec * 1000);
}