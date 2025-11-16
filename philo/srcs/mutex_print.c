/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 17:47:51 by earutiun          #+#    #+#             */
/*   Updated: 2025/11/15 17:47:53 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	mutex_print_out(long timestamp, const char *string,
				t_curph *phil, t_print message_type);

static const char	*define_string(t_print message_type)
{
	if (message_type == FORK)
		return ("has taken a fork");
	else if (message_type == EAT)
		return ("is eating");
	else if (message_type == SLEEP)
		return("is sleeping");
	else if (message_type == THINK)
		return ("is thinking");
	else if (message_type == DIE)
		return ("died");
	return (NULL);
}

int	increment_dieprint(t_curph *phil)
{
	int	dieprint;

	pthread_mutex_lock(&phil->ph_struct->dpr);
	dieprint = ++phil->ph_struct->dieprint;
	pthread_mutex_unlock(&phil->ph_struct->dpr);
	return (dieprint);
}

void	mutex_print_prepare(struct timeval time_tv,
				t_print message_type, t_curph *phil)
{
	const char		*string;
	long			timestamp;
	int				dieprint;

	dieprint = 0;
	string = define_string(message_type);
	timestamp = convert_timeval_ms(time_tv)
		- convert_timeval_ms(phil->ph_struct->start);
	if (!get_eos(phil->ph_struct) || check_id(phil))
	{
		if (message_type == END)
			mutex_print_out(timestamp, string, phil, END);
		else
		{
			if (message_type == DIE)
				dieprint = increment_dieprint(phil);
			if (dieprint > 1)
				return ;
			mutex_print_out(timestamp, string, phil, NOT_END);
		}
	}
}

static void	mutex_print_out(long timestamp, const char *string,
	t_curph *phil, t_print message_type)
{
	if (message_type == END)
	{
		pthread_mutex_lock(&phil->ph_struct->print);
		printf("End of simulation: philosophers go partying 🥳\n");
		pthread_mutex_unlock(&phil->ph_struct->print);
		return ;
	}
	pthread_mutex_lock(&phil->ph_struct->print);
	printf("%04ld %d %s\n", timestamp, phil->id, string);
	pthread_mutex_unlock(&phil->ph_struct->print);
}
