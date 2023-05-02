/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 14:06:48 by anboisve          #+#    #+#             */
/*   Updated: 2023/05/02 17:59:47 by anboisve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define EAT  "is eating🍝"
# define TAKE "took fork🍴"
# define SLEEP "is sleeping 💤"
# define THINK "is thinking 🤔"
# define DIE "is dead 💀"
# define T_TIME unsigned long long

void	ft_bzero(void *ptr, size_t size);

typedef struct s_data
{
	pthread_mutex_t		lock;
	int					i;
	int					meal_need;
	int					is_dead;
	T_TIME				sleep;
	T_TIME				eat;
	T_TIME				thinks;
	T_TIME				ttd;

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
	t_fork	rigth;
	T_TIME	last_meal;
}	t_philo;

#endif