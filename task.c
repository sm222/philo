/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 09:30:39 by anboisve          #+#    #+#             */
/*   Updated: 2024/10/21 12:41:43 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

short	print_info(char *s, int id)
{
	t_data	*tmp;
	short	err;

	err = 0;
	tmp = rt_ptr(NULL);
	pthread_mutex_lock(tmp->msg);
	if (tmp->is_dead < 1)
	{
		printf("%lld %d %s\n", get_time(), id, s);
		err = 0;
	}
	else
		err = 1;
	pthread_mutex_unlock(tmp->msg);
	return (err);
}

int	eat(t_philo *philo, t_data *data)
{
	t_time	eat_t;

	eat_t = data->eat + get_time();
	philo->last_meal = data->ttd + get_time();
	print_info(EAT, philo->id);
	while (get_time() < eat_t)
	{
		if (philo->last_meal < get_time())
		{
			ft_kill(philo, rt_ptr(NULL));
			return (1);
		}
		usleep(LOOP_TIME);
	}
	give_back_fork(philo);
	return (0);
}

int	think(t_philo *philo)
{
	print_info(THINK, philo->id);
	usleep(1000);
	while (!look_fork(philo))
	{
		if (philo->last_meal < get_time())
		{
			ft_kill(philo, rt_ptr(NULL));
			return (1);
		}
		usleep(100);
	}
	pthread_mutex_lock(philo->left->lock);
	pthread_mutex_lock(philo->rigth->lock);
	if (print_info(TAKE_R, philo->id)
		|| print_info(TAKE_L, philo->id))
		return (1);
	return (0);
}

int	ph_sleep(t_philo *philo, t_data *data)
{
	t_time	sleep_t;

	sleep_t = data->sleep + get_time();
	if (print_info(SLEEP, philo->id))
		return (1);
	while (get_time() < sleep_t)
	{
		if (philo->last_meal < get_time())
		{
			ft_kill(philo, rt_ptr(NULL));
			return (1);
		}
		usleep(LOOP_TIME);
	}
	return (0);
}

void	*task(void *in)
{
	t_philo	*philo;

	philo = (t_philo *)in;
	philo->last_meal = philo->info.ttd;
	if (philo->id % 2 == 0)
		usleep(philo->info.eat * 1000 / 2);
	while (philo->meal < philo->info.meal_need || !philo->info.meal_need)
	{
		if (think(philo))
			break ;
		if (eat(philo, &philo->info))
			break ;
		if (philo->info.meal_need != 0)
			philo->meal++;
		if (ph_sleep(philo, &philo->info))
			break ;
	}
	close_mutex(philo);
	return (in);
}
