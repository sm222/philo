/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 09:30:39 by anboisve          #+#    #+#             */
/*   Updated: 2023/05/11 16:40:34 by anboisve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_info(char *s, int id)
{
	printf("%10llu %3d %10s\n", get_time(), id, s);
}

void	do_something(char *job, t_philo *data, t_time t)
{
	t_data	*tmp;
	t_time	end;

	end = t + data->last_meal;
	usleep(t);
	tmp = rt_ptr(NULL);
	pthread_mutex_lock(&tmp->lock);
	print_info(job, data->id);
	printf("time to die %llu\n", end);
	pthread_mutex_unlock(&tmp->lock);
}

void	*task(void *in)
{
	t_philo	*data;

	data = (t_philo *)in;
	if (data->id % 2 == 0)
		usleep(100);
	data->last_meal = get_time();
	while (data->meal <= data->ptr->meal_need)
	{
		do_something(THINK, data, data->ptr->thinks);
		pthread_mutex_lock(&data->rigth->lock);
		do_something(TAKE, data, 0);
		pthread_mutex_lock(&data->left->lock);
		do_something(TAKE, data, 0);
		do_something(EAT, data, data->ptr->eat);
		if (data->ptr->meal_need != 0)
			data->meal++;
		pthread_mutex_unlock(&data->rigth->lock);
		pthread_mutex_unlock(&data->left->lock);
		do_something(SLEEP, data, data->ptr->sleep);
	}
	return (in);
}
