/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 14:06:29 by anboisve          #+#    #+#             */
/*   Updated: 2023/05/02 18:02:46 by anboisve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h> //
#include <string.h> //

T_TIME	get_time(void)
{
	static struct timeval	start = {-1, -1};
	struct timeval			now;
	T_TIME					new;

	if (start.tv_sec == -1 && start.tv_usec == -1)
		gettimeofday(&start, NULL);
	gettimeofday(&now, NULL);
	new = (now.tv_sec * 1000 - start.tv_sec * 1000) + \
	(now.tv_usec / 1000 - start.tv_usec / 1000);
	return (new);
}

void	do_something(void f(char *, int), \
t_philo *data, T_TIME time, char *s)
{
	T_TIME	tmp;

	if (time > 0)
	{
		tmp = get_time();
		if (data->last_meal + time > tmp + data->ptr->ttd)
		{
			data->ptr->is_dead++;
			f(DIE, data->id);
			return ;
		}
	}
	usleep(time);
	f(s, data->id);
}

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
		data->meal++;
		data->last_meal = get_time();
		do_something(&print_info, data, data->ptr->eat, EAT);
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

int	main(void)
{
	int			save;
	pthread_t	t1[200];
	t_philo		ph[200];
	t_data		info;
	int			size;

	save = 4;
	info.meal_need = 8;
	info.i = 0;
	size = save;
	info.eat = 200;
	info.sleep = 200;
	info.thinks = 410;
	info.ttd = 7000;
	pthread_mutex_init(&info.lock, NULL);
	while (size--)
	{
		ft_bzero(&ph[size], sizeof(t_philo));
		ph[size].ptr = &info;
		ph[size].left = NULL;
		ph[size].id = size + 1;
		pthread_mutex_init(&ph[size].rigth.lock, NULL);
	}
	lock_and_join(ph, save);
	size = save;
	while (size--)
		pthread_create(&t1[size], NULL, &work, &ph[size]);
	size = 0;
	while (size < save)
	{
		printf("size:%d\n", size);
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
