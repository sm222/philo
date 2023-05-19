/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 09:30:39 by anboisve          #+#    #+#             */
/*   Updated: 2023/05/19 17:19:43 by anboisve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_info(char *s, int id, t_time t)
{
	printf("%5lld %3d %10s\n", t, id, s);
}

int	eat(t_philo *philo, t_data *data)
{
	t_time	eat_t;

	eat_t = data->eat + get_time();
	philo->last_meal = data->ttd + get_time();
	print_info(EAT, philo->id, get_time());
	while (get_time() < eat_t)
	{
		if (philo->last_meal < get_time())
		{
			print_info(DIE, philo->id, get_time());
			return (1);
		}
		usleep(10);
	}
	give_back_fork(philo);
	return (0);
}

int	think(t_philo *philo)
{
	print_info(THINK, philo->id, get_time());
	while (1)
	{
		usleep(10);
		if (philo->last_meal < get_time())
		{
			print_info(DIE, philo->id, get_time());
			return (1);
		}
		if (look_fork(philo) == 1)
			break ;
	}
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left->lock);
		pthread_mutex_lock(philo->rigth->lock);
	}
	else
	{
		pthread_mutex_lock(philo->rigth->lock);
		pthread_mutex_lock(philo->left->lock);
	}
	print_info(TAKE_R, philo->id, get_time());
	print_info(TAKE_L, philo->id, get_time());
	return (0);
}

int	ph_sleep(t_philo *philo, t_data *data)
{
	t_time	sleep_t;

	sleep_t = data->sleep + get_time();
	while (get_time() < sleep_t)
	{
		if (philo->last_meal < get_time())
		{
			print_info(DIE, philo->id, get_time());
			return (1);
		}
		usleep(10);
	}
	print_info(SLEEP, philo->id, get_time());
	return (0);
}

void	*task(void *in)
{
	t_philo	*philo;

	philo = (t_philo *)in;
	if (philo->id % 2 == 0)
		usleep(100);
	philo->last_meal = philo->info.ttd;
	while (philo->meal <= philo->info.meal_need)
	{
		if (think(philo))
		{
			print_info(DIE, philo->id, get_time());
			break ;
		}
		if (eat(philo, &philo->info))
			break ;
		if (philo->info.meal_need != 0)
			philo->meal++;
		close_mutex(philo);
		if (ph_sleep(philo, &philo->info))
			break ;
	}
	close_mutex(philo);
	return (in);
}
