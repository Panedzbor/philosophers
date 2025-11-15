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

void	mutex_print_prepare(struct timeval time_tv,
				t_print message_type, t_curph *phil)
{
	const char		*string;
	long			timestamp;

	if (message_type == FORK)
		string = "has taken a fork";
	else if (message_type == EAT)
		string = "is eating";
	else if (message_type == SLEEP)
		string = "is sleeping";
	else if (message_type == THINK)
		string = "is thinking";
	else if (message_type == DIE)
		string = "died";
	timestamp = convert_timeval_ms(time_tv)
		- convert_timeval_ms(phil->ph_struct->start);
	if (!get_eos(phil->ph_struct) || check_id(phil))
	{
		if (message_type == END)
			mutex_print_out(timestamp, string, phil, END);
		else
			mutex_print_out(timestamp, string, phil, NOT_END);
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
