
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
    int *args;
    int argc;
    int args_us[3];
    pthread_t *threads;// ?: why not separately for each phil?
    pthread_t death_check;
    pthread_mutex_t *mutexes;
    //int *ids;// ?: needed?
    struct timeval start;
} t_philo;

typedef enum e_next_action
{
    EAT,
    SLEEP,
    THINK
} t_action;

typedef enum e_status
{
    ALIVE,
    DEAD
} t_status;

typedef struct s_current_philo
{
    int id;
    int meals;
    int lfork;
    int rfork;
    struct timeval death;
    t_status status;
    t_action next_action;
    t_philo *ph_struct;
} t_curph;

// typedef struct s_mem
// {
//     void *ptr;
//     struct s_mem *next;
// } t_mem;

void convert_args_us(t_philo *ph_struct);
int convert_ms_us(int ms);
int convert_us_ms(int us);
void    create_threads(t_curph philosophers[], int num_of_phil);
void *death_checker(void *phil_void);
void    ft_putstr_fd(char *s, int fd);
void    join_threads(t_philo ph_struct, int num_of_phil);
t_curph *mem_allocator(int *args, t_philo *ph_struct, void *mem[]);
void    *mem_cleaner(void *mem[]);
//void    init_ids(int *ids, int number_of_philosophers);
void    init_locks(pthread_mutex_t *forks, int number_of_philosophers);
void    init_mem(void *mem[]);
void    init_philosophers(t_curph philosophers[], t_philo *ph_struct);
int     parser(int argc, char *argv[], void *mem[], t_philo *ph_struct);
int     ph_atoi(const char *str);
void    *phil_live(void *phil_void);
void reset_death(struct timeval *tv, int time_to_die);

#endif