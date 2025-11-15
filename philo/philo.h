
#ifndef PHILO_H

# define PHILO_H

# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>

# define D_PTRS 5

typedef struct s_philo
{
    bool            end_of_simulation;
    int             *args;
    int             argc;
    int             dead_id;
    pthread_mutex_t did;
    pthread_mutex_t eos;
    pthread_mutex_t *forks;
    pthread_mutex_t print;
    struct timeval  start;
} t_philo;

typedef enum e_print_message
{
    FORK,
    EAT,
    SLEEP,
    THINK,
    DIE,
    END,
    NOT_END
} t_print;

typedef struct s_current_philo
{
    bool            fed_up;
    int             id;
    int             meals;
    int             lfork;
    int             rfork;
    pthread_mutex_t mutx_death;
    pthread_mutex_t mutx_meals;
    pthread_mutex_t mutx_last_meal;
    pthread_t       *thread;
    struct timeval  death;
    struct timeval  last_meal;
    t_philo         *ph_struct;
} t_curph;

bool all_fed_up(t_curph *phil, int id, int meals_to_end);
bool    check_id(t_curph *phil);
long    convert_ms_sec(long ms);
long    convert_ms_us(long ms);
long    convert_sec_ms(long sec);
long long convert_timeval_ms(struct timeval tv);
long    convert_us_ms(long us);
void    create_threads(t_curph philosophers[], int num_of_phil);
bool    death_check(struct timeval tv, t_curph *phil);
void    destroy_mutexes(t_curph *phil);
void    finish_threads(t_curph phil[]);
void    ft_putstr_fd(char *s, int fd);
long    generate_timestamp(t_curph *phil);
bool    get_eos(t_philo *ph_struct);
int     get_meals(t_curph *phil);
void    increment_meals(t_curph *phil);
t_curph *mem_allocator(int *args, t_philo *ph_struct, void *mem[]);
void    *mem_cleaner(void *mem[]);
void    mutex_print_prepare(struct timeval time_tv, t_print message_type, t_curph *phil);
void    init_forks(pthread_mutex_t *forks, int number_of_philosophers);
void    init_mem(void *mem[]);
void    init_philosophers(t_curph philosophers[], t_philo *ph_struct, void *threads);
int     parser(int argc, char *argv[], void *mem[], t_philo *ph_struct);
int     ph_atoi(const char *str);
void    ph_sleep(long ms);
void    *phil_live(void *phil_void);
void    reset_death(struct timeval *tv, int time_to_die, pthread_mutex_t *death, t_curph *phil);
void    set_end_of_simulation(t_curph *phil);
void simulate_alone_phil(t_curph *phil);
//int     timeval_cmp(struct timeval now, t_curph *phil);

#endif
