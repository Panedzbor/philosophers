/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 17:45:10 by earutiun          #+#    #+#             */
/*   Updated: 2025/11/15 17:45:15 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_philo	ph_struct;
	t_curph	*philosophers;
	void	*mem[D_PTRS];

	gettimeofday(&ph_struct.start, NULL);
	init_mem(mem);
	if (!(parser(argc, argv, mem, &ph_struct)))
		return (1);
	philosophers = mem_allocator(ph_struct.args, &ph_struct, mem);
	if (!philosophers)
		return (2);
	init_forks(ph_struct.forks, ph_struct.args[0]);
	init_philosophers(philosophers, &ph_struct, mem[1]);
	create_threads(philosophers, ph_struct.args[0]);
	finish_threads(philosophers);
	destroy_mutexes(philosophers);
	mem_cleaner(mem);
	return (0);
}
