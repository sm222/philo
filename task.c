/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 09:30:39 by anboisve          #+#    #+#             */
/*   Updated: 2023/05/15 17:19:17 by anboisve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_info(char *s, int id, t_time t)
{
	printf("%5lld %3d %10s\n", t, id, s);
}

void	close_mutex(t_philo *philo)
{
	pthread_mutex_unlock(&philo->ptr->fork);
	pthread_mutex_unlock(&philo->rigth->lock);
	pthread_mutex_unlock(&philo->left->lock);
}

int	eat(t_philo *philo, t_data *data)
{
	t_time	eat_t;

	eat_t = data->eat;
	while (eat_t > 0)
	{
		eat_t -= 1;
		if (philo->last_meal < get_time() - philo->start_t)
		{
			print_info("die here", philo->id, get_time() - philo->start_t);
			return (1);
		}
		usleep(1 * 1000);
	}
	philo->last_meal = data->ttd + get_time();
	print_info(EAT, philo->id, get_time() - philo->start_t);
	return (0);
}

int	think(t_philo *philo)
{
	print_info(THINK, philo->id, get_time() - philo->start_t);
	while (1)
	{
		usleep(10);
		if (philo->ptr->is_dead > 0 || philo->last_meal < get_time() - philo->start_t)
		{
			print_info(DIE, philo->id, get_time() - philo->start_t);
			return (1);
		}
		else if (philo->rigth->use == 0 && philo->left->use == 0)
			break ;
	}
	//pthread_mutex_lock(&philo->rigth->lock);
	//print_info(TAKE_R, philo->id, get_time() - philo->start_t);
	//pthread_mutex_lock(&philo->left->lock);
	//print_info(TAKE_L, philo->id, get_time() - philo->start_t);
	return (0);
}

void	*task(void *in)
{
	t_philo	*philo;

	philo = (t_philo *)in;
	philo->last_meal = philo->ptr->ttd;
	philo->start_t = get_time();
	printf("%lld --\n" , philo->start_t);
	while (philo->meal <= philo->ptr->meal_need)
	{
		if (philo->last_meal < get_time() || think(philo))
		{
			print_info(DIE, philo->id, get_time() - philo->start_t);
			break ;
		}
		if (eat(philo, philo->ptr))
			break ;
		if (philo->ptr->meal_need != 0)
			philo->meal++;
		pthread_mutex_unlock(&philo->rigth->lock);
		pthread_mutex_unlock(&philo->left->lock);
	}
	close_mutex(philo);
	return (in);
}
