/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 09:30:39 by anboisve          #+#    #+#             */
/*   Updated: 2023/05/12 16:55:53 by anboisve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_info(char *s, int id)
{
	printf("%10llu %3d %10s\n", get_time(), id, s);
}

int	do_something(char *job, t_philo *data, t_time t)
{
	t_data	*tmp;

	tmp = rt_ptr(NULL);
	if (tmp->is_dead || get_time() - data->last_meal > data->ptr->ttd)
	{
		tmp->is_dead++;
		if (tmp->is_dead < 2)
			print_info(DIE, data->id);
		return (1);
	}
	else
	{
		usleep(t * 1000);
		print_info(job, data->id);
	}
	return (0);
}

void	close_mutex(t_philo *philo)
{
	pthread_mutex_unlock(&philo->ptr->fork);
	pthread_mutex_unlock(&philo->rigth->lock);
	pthread_mutex_unlock(&philo->left->lock);
}

int	think(t_philo *philo)
{
	print_info(THINK, philo->id);
	while (1)
	{
		usleep(10);
		pthread_mutex_lock(&philo->ptr->fork);
		if (philo->rigth->use == 0 && philo->left->use == 0)
			break ;
		else if (philo->ptr->is_dead)
			return (1);
		pthread_mutex_lock(&philo->ptr->fork);
	}
	pthread_mutex_lock(&philo->rigth->lock);
	print_info(TAKE_R, philo->id);
	pthread_mutex_lock(&philo->left->lock);
	print_info(TAKE_L, philo->id);
	pthread_mutex_lock(&philo->ptr->fork);
	return (0);
}

void	*task(void *in)
{
	t_philo	*philo;

	philo = (t_philo *)in;
	philo->last_meal = 0;
	while (philo->meal <= philo->ptr->meal_need)
	{
		if (think(philo))
			break ;
		if (do_something(EAT, philo, philo->ptr->eat))
			break ;
		if (philo->ptr->meal_need != 0)
			philo->meal++;
		philo->last_meal = get_time();
		pthread_mutex_unlock(&philo->rigth->lock);
		pthread_mutex_unlock(&philo->left->lock);
		if (do_something(SLEEP, philo, philo->ptr->sleep))
			break ;
	}
	close_mutex(philo);
	return (in);
}
