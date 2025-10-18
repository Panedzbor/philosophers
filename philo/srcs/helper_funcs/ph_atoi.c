

#include "../../philo.h"

static int	substract(const char *str, int start, int end);
static int	add(const char *str, int start, int end);
static void	check_input(const char *str, int *start, int *end, int *negative);
static int	ft_isdigit(int c);

int	ph_atoi(const char *str)
{
	int		num;
	int		negative;
	int		start;
	int		end;

	start = 0;
	end = 0;
	negative = 0;
	if (!str)
		return (0);
	check_input(str, &start, &end, &negative);
	if (!(ft_isdigit(str[start])))
		return (-1);
	if (negative == 1)
		num = substract(str, start, end);
	else
		num = add(str, start, end);
	return (num);
}

static void	check_input(const char *str, int *start, int *end, int *negative)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '-')
	{
		*negative = 1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	*start = i;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (i > 0)
		*end = i - 1;
}

static int	substract(const char *str, int start, int end)
{
	int	num;
	int	mult;

	num = 0;
	mult = 1;
	while (end >= start)
	{
		num -= (str[end] - '0') * mult;
		end--;
		mult *= 10;
	}
	return (num);
}

static int	add(const char *str, int start, int end)
{
	int	num;
	int	mult;

	num = 0;
	mult = 1;
	while (end >= start)
	{
		num += (str[end] - '0') * mult;
		end--;
		mult *= 10;
	}
	return (num);
}

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}
