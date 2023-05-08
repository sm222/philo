/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 14:06:48 by anboisve          #+#    #+#             */
/*   Updated: 2023/05/07 09:50:37 by anboisve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define DIE "is dead 💀"
# define EAT "is eating🍝"
# define TAKE "took fork🍴"
# define SLEEP "is sleeping 💤"
# define THINK "is thinking 🤔"

typedef unsigned long long	t_time;

void	*re_ptr(void *ptr);
void	*ft_free(void *ptr);
void	ft_bzero(void *ptr, size_t size);
void	*ft_calloc(size_t count, size_t size);

typedef struct s_data
{
	int					i;
	int					is_dead;
	int					nb_of_ph;
	int					meal_need;
	t_time				eat;
	t_time				ttd;
	t_time				sleep;
	t_time				thinks;
	pthread_mutex_t		lock;

}	t_data;

typedef struct s_fork
{
	pthread_mutex_t	lock;
	int				use;
}	t_fork;

typedef struct s_philo
{
	int		id;
	int		meal;
	t_data	*ptr;
	int		lock;
	int		time;
	t_fork	*left;
	t_fork	*rigth;
	t_time	last_meal;
}	t_philo;

#endif

/*
memset, printf, malloc, free, write,
usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock
*/
