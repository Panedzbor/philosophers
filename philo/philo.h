
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
    pthread_t *threads;// ?: why not separately for each phil?
    pthread_mutex_t *mutexes;
    int *ids;// ?: needed?
} t_philo;

typedef struct s_current_philo
{
    int id;
    
    t_philo *ph_struct;
} t_curph;

// typedef struct s_mem
// {
//     void *ptr;
//     struct s_mem *next;
// } t_mem;

void    ft_putstr_fd(char *s, int fd);
t_curph *mem_allocator(int *args, t_philo ph_struct, void *mem[]);
void    *mem_cleaner(void *mem[]);
void    init_ids(int *ids, int number_of_philosophers);
void    init_locks(int *forks, int number_of_philosophers);
void    init_mem(void *mem[]);
int     *parser(int argc, char *argv[], void *mem[]);
int     ph_atoi(const char *str);

#endif