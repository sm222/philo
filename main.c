/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 14:06:29 by anboisve          #+#    #+#             */
/*   Updated: 2023/04/30 15:04:55 by anboisve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h> //
#include <string.h> //

unsigned long long	get_time(void)
{
	static struct timeval	start = {-1, -1};
	struct timeval			now;
	unsigned long long		new;

	if (start.tv_sec == -1 && start.tv_usec == -1)
		gettimeofday(&start, NULL);
	gettimeofday(&now, NULL);
	new = (now.tv_sec * 1000 - start.tv_sec * 1000) + \
	(now.tv_usec / 1000 - start.tv_usec / 1000);
	return (new);
}

void	sleep_time(unsigned long long time)
{
	usleep(time);
}

char	*give_name(void)
{
	static int	i = 0;
	static int	cpy = 0;

	if (i >= 7)
		i = 0;
	else
		i++;
	if (i == 0)
		return (ft_combine("%s:%d", N0, cpy));
	if (i == 1)
		return (ft_combine("%s:%d", N1, cpy));
	if (i == 2)
		return (ft_combine("%s:%d", N2, cpy));
	if (i == 3)
		return (ft_combine("%s:%d", N3, cpy));
	if (i == 4)
		return (ft_combine("%s:%d", N4, cpy));
	if (i == 5)
		return (ft_combine("%s:%d", N5, cpy));
	if (i == 6)
		return (ft_combine("%s:%d", N6, cpy));
	if (i == 7)
		return (ft_combine("%s:%d", N6, cpy++));
	return (NULL);
}

void	print_info(char *s, int id)
{
	printf("%6llu %d %s\n", get_time(), id, s);
}

void	*work(void *in)
{
	t_philo	*data;

	data = (t_philo *)in;
	if (data->id % 2 == 0)
		usleep(100);
	while (data->meal < data->ptr->meal_need)
	{
		usleep(100);
		pthread_mutex_lock(&data->rigth.lock);
		pthread_mutex_lock(&data->left->lock);
		print_info(TAKE, data->id);
		data->meal++;
		usleep(5000);
		print_info(EAT, data->id);
		usleep(10000);
		print_info(SLEEP, data->id);
		pthread_mutex_unlock(&data->rigth.lock);
		pthread_mutex_unlock(&data->left->lock);
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
		printf("%d %d\n", i, i + 1);
		(philo[i]).left = &(philo[i + 1]).rigth;
		pthread_mutex_lock(&tmp->left->lock);
		i++;
	}
	(philo[i]).left = &(philo[0]).rigth;
	tmp = &philo[i];
	pthread_mutex_lock(&tmp->left->lock);
	printf("%d %d\n", i, 0);
}

int	main(void)
{
	int			save;
	pthread_t	t1[200];
	t_philo		ph[200];
	t_data		info;
	int			size;

	save = 50;
	info.meal_need = 100;
	info.end = save * 200;
	info.i = 0;
	get_time();
	size = save;
	pthread_mutex_init(&info.lock, NULL);
	while (size--)
	{
		ft_bzero(&ph[size], sizeof(t_philo));
		ph[size].ptr = &info;
		ph[size].name = give_name();
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
	while (size--)
		pthread_join(t1[size], NULL);
	/*
	pthread_mutex_destroy(&info.lock);
	unsigned long long time = get_time();
	if (time / 1000 > 60)
		printf("end at minute: %llu:%llu\n", time / 1000 / 60, time);
	else
		printf("end at segond : %llu\n", time / 1000);
	*/
	return (0);
}
