#include "philo.h"
#include <sys/time.h>
#include <string.h>


long int timer(t_args *args)
{
    struct timeval current;

    gettimeofday(&current, NULL);
    return ((current.tv_sec - args->start.tv_sec) * 1000 + (current.tv_usec - args->start.tv_usec) / 1000);
}

void message(char *str,t_philo *philo)
{
    pthread_mutex_lock(&philo->args->m_write);
    if(!philo->args->die_s && strcmp("died",str)==0)
    {
        printf("%ld %d %s\n", timer(philo->args), philo->n_philo, str);
        pthread_mutex_lock(&philo->args->m_die);
        philo->args->die_s=1;
        pthread_mutex_unlock(&philo->args->m_die);
    }
    if(!philo->args->die_s)
        printf("%ld %d %s\n", timer(philo->args), philo->n_philo, str);
    pthread_mutex_unlock(&philo->args->m_write);
}
void take_forks(t_philo *philo)
{
    pthread_mutex_lock(philo->m_r_fork);
    message("has taken a fork",philo);
    pthread_mutex_lock(&philo->m_l_fork);
    message("has taken a fork",philo);
}


void dow_forks(t_philo *philo)
{
    message("is sleeping",philo);
    pthread_mutex_unlock(philo->m_r_fork);
    pthread_mutex_unlock(&philo->m_l_fork);
    ft_usleep(philo->args->t_sleep,philo);
}

void eat(t_philo *philo)
{
    take_forks(philo);
    message(" is eating",philo);
    pthread_mutex_lock(&philo->args->m_lock);
    philo->t_eating=timer(philo->args);
    philo->c_eat+=1;
    pthread_mutex_unlock(&philo->args->m_lock);

    ft_usleep(philo->args->t_eat,philo);
    dow_forks(philo);
}


size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
int	ft_usleep(size_t milliseconds,t_philo *philo)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
    {
        pthread_mutex_lock(&philo->args->m_die);
        if(philo->args->die_s)
        {
            pthread_mutex_unlock(&philo->args->m_die);
            return 0;
        }
        pthread_mutex_unlock(&philo->args->m_die);
		usleep(500);
    }
	return (0);
}





void *testt(void *arg)
{
    t_philo *args;
    
    struct timeval current;
    args =(t_philo *) arg;
 
    if (args->n_philo % 2 == 0)
        usleep(1000);
   while(1)
   {
        pthread_mutex_lock(&args->args->m_die);
        pthread_mutex_lock(&args->args->m_data);

        if(args->args->die_s || args->args->finish >= args->args->philosophers)
        {
            pthread_mutex_unlock(&args->args->m_data);
            pthread_mutex_unlock(&args->args->m_die);
            break;
        }
        pthread_mutex_unlock(&args->args->m_data);
        pthread_mutex_unlock(&args->args->m_die);
        message("is thinking",args);
        eat(args);
   }
    return NULL;
}



void insial(t_args *args, int i)
{
    args->philo[i].args = args;
    args->philo[i].n_philo= i + 1;
    args->philo[i].fork=-1;
    args->philo[i].die=0;
    args->philo[i].sleep=0;
    args->philo[i].eat=0;
    args->philo[i].t_eating=0;
    args->philo[i].c_eat=0;
    args->philo[i].m_r_fork =NULL;
    pthread_mutex_init(&args->philo[i].m_l_fork,NULL);  
    pthread_mutex_init(&args->philo[i].m_write,NULL); 
    pthread_mutex_init(&args->philo[i].m_lock,NULL);   

    if(i == args->philosophers -1 )
        args->philo[i].m_r_fork = &args->philo[0].m_l_fork;
    else    
        args->philo[i].m_r_fork = &args->philo[i + 1].m_l_fork;

    pthread_create(&args->philo[i].thread, NULL, testt, &args->philo[i]);
}

void check(t_args *args)
{ 
    while (1)
    {
        int i=0;

        while (i < args->philosophers)
        {
            pthread_mutex_lock(&args->m_lock);

            pthread_mutex_lock(&args->m_data);
            if(args->philo[i].c_eat==args->w)
            {
                args->philo[i].c_eat = 0;
                args->finish++;
                //printf("\n                     %d\n",args->finish);
                // return;
            }
            pthread_mutex_unlock(&args->m_data);
            if(timer(args)- args->philo[i].t_eating >=args->t_die)
            {
                
            // pthread_mutex_unlock(&args->philo[i].m_lock);
                if(args->finish < args->philosophers)
                    message("died",&args->philo[i]);
                // pthread_mutex_unlock(&args->philo[i].m_lock);
                pthread_mutex_unlock(&args->m_lock);
                return ;
            }
            i++;
            pthread_mutex_unlock(&args->m_lock);
        }
    }
}

int main(int arc,char **arv)
{
    //1== number_of_philosophers
    //2== time_to_die
    //3== time_to_eat 
    //4== time_to_sleep
    //5== number_of_times_each_philosopher_must_eat
    t_args args;
    gettimeofday(&args.start , NULL);
    args.die_s = 0;
    args.finish =0;
    args.philosophers = ft_atoi(arv[1]);
    args.forks=args.philosophers;
    args.t_die= ft_atoi(arv[2]);
    args.t_eat= ft_atoi(arv[3]);
    args.t_sleep= ft_atoi(arv[4]);
    if(arc==6)
        args.w= ft_atoi(arv[5]);
    else    
        args.w =-1;
    pthread_mutex_init(&args.m_data,NULL);    
    pthread_mutex_init(&args.m_die,NULL); 
      pthread_mutex_init(&args.m_write,NULL); 
      pthread_mutex_init(&args.m_lock,NULL);   
    args.philo = malloc(sizeof(args.philo)*args.philosophers);


    int i =0;
    while (i < args.philosophers)
    {
        insial(&args,i);
        i++;
    }
    check(&args);
    i =0;
    while (i<args.philosophers)
    {
        pthread_join(args.philo[i].thread,NULL);
        i++;
    }

}