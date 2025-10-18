
#ifndef PHILO_H

# define PHILO_H

# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>

int *parser(int argc, char *argv[], pthread_t **threads, int **ids);
int    *process_input(int argc, char *argv[]);


#endif