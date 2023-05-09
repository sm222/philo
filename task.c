/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 09:30:39 by anboisve          #+#    #+#             */
/*   Updated: 2023/05/09 17:47:29 by anboisve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_info(char *s, int id)
{
	printf("%6llu %3d %7s\n", get_time(), id, s);
}

void	do_something(char *job, int id, t_time t)
{
	usleep(t);
	print_info(job, id);
}

void	*task(void *in)
{
	t_philo	*data;

	data = (t_philo *)in;
	if (data->id % 2 == 0)
		usleep(100);
	data->last_meal = get_time();
	while (data->meal < data->ptr->meal_need)
	{
		pthread_mutex_lock(&data->rigth->lock);
		do_something(TAKE, data->id, 0);
		pthread_mutex_lock(&data->left->lock);
		do_something(TAKE, data->id, 0);
		do_something(EAT, data->id, 5000);
		data->meal++;
		pthread_mutex_unlock(&data->rigth->lock);
		pthread_mutex_unlock(&data->left->lock);
		do_something(SLEEP, data->id, 6000);
	}
	return (in);
}
