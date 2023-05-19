/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 14:06:48 by anboisve          #+#    #+#             */
/*   Updated: 2023/05/19 16:30:22 by anboisve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define DIE "is dead   💀"
# define EAT "is eating 🍝"
# define TAKE_R "took fork rigth🍴"
# define TAKE_L "took fork left 🍴"
# define SLEEP "is sleeping 💤"
# define THINK "is thinking 🤔"

# define MFAIL "Malloc fail\n"
# define MISS_ARGS "not rigth amont of args\n"

typedef long long	t_time;

//sizeof(t_philo)

typedef struct s_data
{
	int				i;
	int				is_dead;
	int				nb_of_ph;
	int				meal_need;
	t_time			eat;
	t_time			ttd;
	t_time			sleep;
	pthread_mutex_t	*lock;

}	t_data;

typedef struct s_fork
{
	pthread_mutex_t	*lock;
	int				use;
}	t_fork;

typedef struct s_philo
{
	int		id;
	int		meal;
	t_data	info;
	t_fork	*left;
	t_fork	*rigth;
	t_time	last_meal;
}	t_philo;

int		take_ph_nb(char *s);
int		get_arg(char *s);
int		make_pthread(pthread_t ***thread, int size);
void	print_info(char *s, int id, t_time t);
void	ft_memcpy(void *src, void *dest, size_t size);
t_time	get_time(void);
void	*rt_ptr(void *ptr);
void	*task(void *in);
void	*ft_free(void *ptr);
void	ft_bzero(void *ptr, size_t size);
void	*ft_calloc(size_t count, size_t size);
int		start_data(t_data *data, int ac, char **av);
void	close_mutex(t_philo *philo);
void	free_ph(t_philo **ph, int size);
int		look_fork(t_philo *philo);
void	give_back_fork(t_philo *philo);

#endif

/*
memset, printf, malloc, free, write,
usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock
*/
