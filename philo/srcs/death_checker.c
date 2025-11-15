#include "../philo.h"

bool	death_check(struct timeval tv, t_curph *phil)
{
	struct timeval	death;
	long long		d;
	long long		now;

	pthread_mutex_lock(&phil->mutx_death);
	death = phil->death;
	pthread_mutex_unlock(&phil->mutx_death);
	now = convert_timeval_ms(tv);
	d = convert_timeval_ms(death);
	if (now > d)
		return (false);
	return (true);
}
