
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
    pthread_t *threads;
    pthread_mutex_t *mutexes;
    int *ids;
} t_philo;

typedef struct s_current_philo
{
    int id;
    t_philo struph;
} t_curph;

// typedef struct s_mem
// {
//     void *ptr;
//     struct s_mem *next;
// } t_mem;

void    ft_putstr_fd(char *s, int fd);
int     *parser(int argc, char *argv[], void *mem[]);
int     ph_atoi(const char *str);

#endif