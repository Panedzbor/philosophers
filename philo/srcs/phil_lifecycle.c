#include "../philo.h"

static bool	phil_take_forks(t_curph *phil);
static bool	phil_eat(t_curph *phil, int meals_to_end);
static bool	phil_sleep(t_curph *phil);
static bool	phil_think(t_curph *phil);

void	*phil_live(void *phil_void)
{
	t_curph	*phil;
	int		meals_to_end;
	int		time_to_eat;

	phil = (t_curph *)phil_void;
	meals_to_end = -1;
	time_to_eat = phil->ph_struct->args[2];
	if (phil->ph_struct->argc == 5)
		meals_to_end = phil->ph_struct->args[4];
	if (phil->id % 2 == 0)
		usleep(convert_ms_us(time_to_eat / 2));
	while (!get_eos(phil->ph_struct))
	{
		phil_take_forks(phil);
		if (!get_eos(phil->ph_struct))
			phil_eat(phil, meals_to_end);
		if (!get_eos(phil->ph_struct))
			phil_sleep(phil);
		if (!get_eos(phil->ph_struct))
			phil_think(phil);
	}
	return (NULL);
}

static bool	phil_take_forks(t_curph *phil)
{
	int				number_of_philosophers;
	struct timeval	now;

	number_of_philosophers = phil->ph_struct->args[0];
	pthread_mutex_lock(&phil->ph_struct->forks[phil->rfork]);
	gettimeofday(&now, NULL);
	if (death_check(now, phil))
		mutex_print_prepare(now, FORK, phil);
	else
	{
		set_end_of_simulation(phil);
		mutex_print_prepare(now, DIE, phil);
		pthread_mutex_unlock(&phil->ph_struct->forks[phil->rfork]);
		return (true);
	}
	if (number_of_philosophers <= 1)
	{
		simulate_alone_phil(phil);
		return (true);
	}
	pthread_mutex_lock(&phil->ph_struct->forks[phil->lfork]);
	return (false);
}

static bool	phil_eat(t_curph *phil, int meals_to_end)
{
	long			time_to_eat;
	long			time_to_die;
	struct timeval	meal_time;

	time_to_eat = phil->ph_struct->args[2];
	time_to_die = phil->ph_struct->args[1];
	gettimeofday(&meal_time, NULL);
	if (!death_check(meal_time, phil))
	{
		set_end_of_simulation(phil);
		mutex_print_prepare(meal_time, DIE, phil);
		return (true);
	}
	pthread_mutex_lock(&phil->mutx_last_meal);
	phil->last_meal = meal_time;
	pthread_mutex_unlock(&phil->mutx_last_meal);
	reset_death(&phil->death, time_to_die, &phil->mutx_death, phil);
	mutex_print_prepare(meal_time, EAT, phil);
	ph_sleep(time_to_eat);
	pthread_mutex_unlock(&phil->ph_struct->forks[phil->rfork]);
	pthread_mutex_unlock(&phil->ph_struct->forks[phil->lfork]);
	increment_meals(phil);
	all_fed_up(phil, phil->id, meals_to_end);
	return (false);
}

static bool	phil_sleep(t_curph *phil)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	if (death_check(now, phil))
	{
		mutex_print_prepare(now, SLEEP, phil);
		ph_sleep(phil->ph_struct->args[3]);
		return (false);
	}
	set_end_of_simulation(phil);
	mutex_print_prepare(now, DIE, phil);
	return (true);
}

static bool	phil_think(t_curph *phil)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	if (death_check(now, phil))
	{
		mutex_print_prepare(now, THINK, phil);
		return (false);
	}
	set_end_of_simulation(phil);
	mutex_print_prepare(now, DIE, phil);
	return (true);
}
