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

int convert_ms_us(int ms)
{
    return (ms * 1000);
}

int convert_us_ms(int us)
{
    return (us / 1000);
}