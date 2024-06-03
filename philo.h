#ifndef PHILO_H
#define PHILO_H


#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
// typedef struct s_args t_args;

typedef struct s_philo
{
    int n_philo;
    int fork;
    int die;
    int sleep;
    int eat;
    pthread_t thread;
    struct s_args *args;
    pthread_mutex_t m_l_fork;
    pthread_mutex_t * m_r_fork;
    pthread_mutex_t m_write;
    pthread_mutex_t m_lock;
    int c_eat;

    struct timeval start;
    size_t t_eating;
    //struct s_philo *next;
} t_philo;

typedef struct s_args
{
    int philosophers;
    int forks; 
    int t_die;
    int die_s;
    int t_eat;
    int t_sleep;
    int n_eat;
    int w;
    int finish;
    struct timeval start;
    long int time;
    pthread_mutex_t m_data;
    pthread_mutex_t m_die;
    pthread_mutex_t m_read;
    pthread_mutex_t m_write;
    pthread_mutex_t m_lock;
    t_philo *philo;
} t_args;





int	ft_atoi(char *str);
int	ft_usleep(size_t milliseconds,t_philo *philo);
#endif