/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 14:06:48 by anboisve          #+#    #+#             */
/*   Updated: 2023/05/22 17:13:16 by anboisve         ###   ########.fr       */
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
# define SLEEP "is sleeping 💤"
# define THINK "is thinking 🤔"
# define TAKE_L "took fork left 🍴"
# define TAKE_R "took fork rigth🍴"
# define LOOP_TIME 1000

# define MFAIL "Malloc fail\n"
# define MISS_ARGS "not rigth amont of args\n"

typedef long long	t_time;

//sizeof(t_philo)

typedef struct s_data
{
	t_time			eat;
	t_time			ttd;
	t_time			sleep;
	pthread_mutex_t	*msg;
	pthread_mutex_t	*lock;
	int				is_dead;
	int				nb_of_ph;
	int				meal_need;
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

t_time	get_time(void);
void	*task(void *in);
int		get_arg(char *s);
void	*rt_ptr(void *ptr);
void	*ft_free(void *ptr);
int		take_ph_nb(char *s);
int		look_fork(t_philo *philo);
void	close_mutex(t_philo *philo);
int		print_info(char *s, int id);
void	give_back_fork(t_philo *philo);
void	ft_bzero(void *ptr, size_t size);
void	ft_kill(t_philo *philo, t_data *tmp);
void	*ft_calloc(size_t count, size_t size);
int		start_data(t_data *data, int ac, char **av);
int		make_pthread(pthread_t ***thread, int size);
void	ft_memcpy(void *src, void *dest, size_t size);
void	free_ph(t_philo **ph, pthread_t	**thread, t_data *data, int size);

#endif

/*
memset, printf, malloc, free, write,
usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock
*/
