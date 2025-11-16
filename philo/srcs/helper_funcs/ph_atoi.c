/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 17:46:23 by earutiun          #+#    #+#             */
/*   Updated: 2025/11/15 17:46:26 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philo.h"

static int	substract(const char *str, int start, int end);
static int	add(const char *str, int start, int end);
static void	skip_starting_spaces(const char *str, int *start, int *negative);
static int	only_numeric(const char *str, int *end);

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
	skip_starting_spaces(str, &start, &negative);
	if (!(only_numeric(&str[start], &end)))
		return (-1);
	if (negative == 1)
		num = substract(str, start, end);
	else
		num = add(str, start, end);
	return (num);
}

static void	skip_starting_spaces(const char *str, int *start, int *negative)
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

static int	only_numeric(const char *str, int *end)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	if (i == 0)
		return (0);
	*end = i;
	return (1);
}
