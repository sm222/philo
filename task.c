/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 09:30:39 by anboisve          #+#    #+#             */
/*   Updated: 2023/05/22 17:26:42 by anboisve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_info(char *s, int id)
{
	t_data	*tmp;
	int		err;

	err = 0;
	tmp = rt_ptr(NULL);
	pthread_mutex_lock(tmp->msg);
	if (tmp->is_dead < 1)
	{
		printf("%5lld %3d %10s\n", get_time(), id, s);
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
	t_time	t;

	eat_t = data->eat + get_time();
	philo->last_meal = data->ttd + get_time();
	t = get_time();
	if (print_info(EAT, philo->id))
		return (1);
	while (t < eat_t)
	{
		t = get_time();
		if (philo->last_meal < t)
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
	if (print_info(THINK, philo->id))
		return (1);
	while (1)
	{
		if (philo->last_meal < get_time())
		{
			ft_kill(philo, rt_ptr(NULL));
			return (1);
		}
		if (look_fork(philo) == 1)
			break ;
		usleep(10);
	}
	pthread_mutex_lock(philo->left->lock);
	pthread_mutex_lock(philo->rigth->lock);
	if (print_info(TAKE_R, philo->id) || print_info(TAKE_L, philo->id))
		return (1);
	return (0);
}

int	ph_sleep(t_philo *philo, t_data *data)
{
	t_time	sleep_t;
	t_time	t;

	t = get_time();
	sleep_t = data->sleep + t;
	while (t <= sleep_t)
	{
		t = get_time();
		if (philo->last_meal < t)
		{
			ft_kill(philo, rt_ptr(NULL));
			return (1);
		}
		usleep(LOOP_TIME);
	}
	if (print_info(SLEEP, philo->id))
		return (1);
	return (0);
}

void	*task(void *in)
{
	t_philo	*philo;

	philo = (t_philo *)in;
	if (philo->id % 2 != 0)
		usleep(5000);
	philo->last_meal = philo->info.ttd;
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
