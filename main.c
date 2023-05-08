/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 14:06:29 by anboisve          #+#    #+#             */
/*   Updated: 2023/05/07 09:29:47 by anboisve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h> //
#include <string.h> //

void	print_info(char *s, int id)
{
	printf("%6llu %3d %7s\n", get_time(), id, s);
}

void	*work(void *in)
{
	t_philo	*data;

	data = (t_philo *)in;
	if (data->id % 2 == 0)
		usleep(100);
	data->last_meal = get_time();
	while (data->meal < data->ptr->meal_need)
	{
		usleep(100);
		pthread_mutex_lock(&data->rigth.lock);
		do_something(&print_info, data, 0, TAKE);
		pthread_mutex_lock(&data->left->lock);
		do_something(&print_info, data, 0, TAKE);
		do_something(&print_info, data, data->ptr->eat, EAT);
		data->last_meal = get_time();
		data->meal++;
		do_something(&print_info, data, data->ptr->thinks, THINK);
		pthread_mutex_unlock(&data->rigth.lock);
		pthread_mutex_unlock(&data->left->lock);
		do_something(&print_info, data, data->ptr->sleep, SLEEP);
		usleep(1000);
	}
	return (in);
}

void	lock_and_join(t_philo *philo, int size)
{
	int		i;
	t_philo	*tmp;

	i = 0;
	while (i < size - 1)
	{
		tmp = &philo[i];
		(philo[i]).left = &(philo[i + 1]).rigth;
		pthread_mutex_lock(&tmp->left->lock);
		i++;
	}
	(philo[i]).left = &(philo[0]).rigth;
	tmp = &philo[i];
	pthread_mutex_lock(&tmp->left->lock);
}

void	set_data(t_data *data, t_philo **ph, int size)
{
	data->eat = 200;
	data->sleep = 200;
	data->thinks = 4100;
	data->ttd = 4000;
	data->meal_need = 8;
	data->i = 0;
	pthread_mutex_init(&data->lock, NULL);
	while (size--)
	{
		(*ph)[size].ptr = data;
		printf("ici\n");
		(ph)[size]->left = NULL;
		(ph[size])->id = size + 1;
		pthread_mutex_init(&(ph[size])->rigth.lock, NULL);
	}
}

int	main(void)
{
	int			save;
	pthread_t	t1[200];
	t_philo		*ph;
	t_data		info;
	int			size;

	save = 6;
	ph = ft_calloc(save, sizeof(t_philo));
	size = save;
	re_ptr(&info);
	set_data(&info, &ph, save);
	lock_and_join(ph, save);
	size = save;
	while (size--)
		pthread_create(&t1[size], NULL, &work, &ph[size]);
	size = 0;
	while (size < save)
	{
		if (size % 2 == 0)
		{
			pthread_mutex_unlock(&ph[size].left->lock);
			pthread_mutex_unlock(&ph[size].rigth.lock);
		}
		size++;
	}
	size = save;
	printf("done\n");
	get_time();
	while (size--)
		pthread_join(t1[size], NULL);
	return (0);
}
