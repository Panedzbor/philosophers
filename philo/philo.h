
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
    bool            end_of_simulation;//mutex
    int             *args;
    int             argc;
    pthread_mutex_t eos;
    pthread_mutex_t *forks;
    pthread_mutex_t print;
    pthread_t       death_check;
    struct timeval  start;
} t_philo;

typedef enum e_next_action
{
    EAT,
    SLEEP,
    THINK
} t_action;

typedef enum e_print_message
{
    FORK,
    EATS,
    SLEEPS,
    THINKS,
    DIE,
    END
} t_print;

/* typedef enum e_status
{
    ALIVE,
    DEAD
} t_status; */

typedef struct s_current_philo
{
    int             id;
    int             meals;//mutex
    int             lfork;
    int             rfork;
    pthread_mutex_t ph_mutex;
    pthread_t       *thread;
    struct timeval  death;//mutex
    t_action        next_action;//remove
    t_philo         *ph_struct;
    //t_status        status;
} t_curph;

long    convert_ms_us(long ms);
long    convert_sec_ms(long sec);
long    convert_us_ms(long us);
void    create_threads(t_curph philosophers[], int num_of_phil);
void    *death_checker(void *phil_void);
void    destroy_mutexes(t_curph *phil);
void    finish_threads(t_curph phil[]);
void    ft_putstr_fd(char *s, int fd);
long    generate_timestamp(t_curph *phil);
t_curph *mem_allocator(int *args, t_philo *ph_struct, void *mem[]);
void    *mem_cleaner(void *mem[]);
void    init_locks(pthread_mutex_t *forks, int number_of_philosophers);
void    init_mem(void *mem[]);
void    init_philosophers(t_curph philosophers[], t_philo *ph_struct, void *threads);
int     parser(int argc, char *argv[], void *mem[], t_philo *ph_struct);
int     ph_atoi(const char *str);
void    *phil_live(void *phil_void);
void    reset_death(struct timeval *tv, int time_to_die, pthread_mutex_t *ph_mutex);
int     timeval_cmp(struct timeval now, t_curph *phil);

#endif