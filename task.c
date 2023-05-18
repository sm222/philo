/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 09:30:39 by anboisve          #+#    #+#             */
/*   Updated: 2023/05/18 16:20:46 by anboisve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_info(char *s, int id, t_time t)
{
	t_data	*tmp;

	tmp = rt_ptr(NULL);
	pthread_mutex_lock(tmp->lock);
	printf("%5lld %3d %10s\n", t, id, s);
	pthread_mutex_unlock(tmp->lock);
}

int	eat(t_philo *philo, t_data *data)
{
	t_time	eat_t;

	eat_t = data->eat + get_time();
	while (get_time() < eat_t)
	{
		if (philo->last_meal < get_time())
		{
			print_info(DIE4, philo->id, get_time());
			return (1);
		}
		usleep(10);
	}
	print_info(EAT, philo->id, get_time());
	philo->last_meal = data->ttd + get_time();
	return (0);
}

int	think(t_philo *philo)
{
	print_info(THINK, philo->id, get_time());
	if (philo->last_meal < get_time())
	{
		print_info(DIE2, philo->id, get_time());
		return (1);
	}
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->rigth->lock);
		pthread_mutex_lock(philo->left->lock);
	}
	else
	{
		pthread_mutex_lock(philo->left->lock);
		pthread_mutex_lock(philo->rigth->lock);
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
			print_info(DIE4, philo->id, get_time());
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
		usleep(10);
	philo->last_meal = philo->info.ttd;
	while (philo->meal <= philo->info.meal_need)
	{
		if (think(philo))
		{
			print_info(DIE3, philo->id, get_time());
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
