/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 09:30:39 by anboisve          #+#    #+#             */
/*   Updated: 2023/05/14 17:58:23 by anboisve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_info(char *s, int id)
{
	printf("%10llu %3d %10s\n", get_time(), id, s);
}

void	close_mutex(t_philo *philo)
{
	pthread_mutex_unlock(&philo->ptr->fork);
	pthread_mutex_unlock(&philo->rigth->lock);
	pthread_mutex_unlock(&philo->left->lock);
}

int	all_alive(t_data *data)
{
	(void)data;
	return (0);
}

int	eat(t_philo *philo, t_data *data)
{
	t_time	eat_t;

	eat_t = data->eat;
	while (eat_t > 0)
	{
		if (philo->last_meal <= 0)
		{
			print_info(DIE, philo->id);
			return (1);
		}
		usleep(10 * 1000);
		eat_t -= 10;
		philo->last_meal -= 10;
	}
	philo->last_meal = data->eat;
	print_info(EAT, philo->id);
	return (0);
}

int	think(t_philo *philo)
{
	print_info(THINK, philo->id);
	while (1)
	{
		usleep(1 * 1000);
		philo->last_meal -= 1;
		if (philo->ptr->is_dead > 0 || philo->last_meal < 1)
			return (1);
		else if (philo->rigth->use == 0 && philo->left->use == 0)
			break ;
	}
	pthread_mutex_lock(&philo->rigth->lock);
	print_info(TAKE_R, philo->id);
	pthread_mutex_lock(&philo->left->lock);
	print_info(TAKE_L, philo->id);
	return (0);
}

void	*task(void *in)
{
	t_philo	*philo;

	philo = (t_philo *)in;
	philo->last_meal = philo->ptr->eat;
	while (philo->meal <= philo->ptr->meal_need)
	{
		if (think(philo))
			break ;
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
