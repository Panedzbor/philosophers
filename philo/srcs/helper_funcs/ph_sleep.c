/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_sleep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 17:46:31 by earutiun          #+#    #+#             */
/*   Updated: 2025/11/15 17:46:33 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philo.h"

void	ph_sleep(long ms)
{
	const long		slice_ms = 1;
	long			slice_us;
	struct timeval	start;
	struct timeval	now;
	long			diff;

	slice_us = convert_ms_us(slice_ms);
	gettimeofday(&start, NULL);
	now = start;
	diff = convert_timeval_ms(now) - convert_timeval_ms(start);
	while (diff < ms)
	{
		usleep(slice_us);
		gettimeofday(&now, NULL);
		diff = convert_timeval_ms(now) - convert_timeval_ms(start);
	}
}
