#include "../philo.h"

void convert_args_us(t_philo *ph_struct)
{
    int *args_ms;
    int *args_us;
    int i;

    args_ms = &ph_struct->args[1];
    args_us = ph_struct->args_us;
    i = 0;
    while (i < 3)
    {
        args_us[i] = convert_ms_us(args_ms[i]);
        i++;
    }
}

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