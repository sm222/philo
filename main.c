/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 14:06:29 by anboisve          #+#    #+#             */
/*   Updated: 2023/04/25 15:49:24 by anboisve         ###   ########.fr       */
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

char	*give_name(void)
{
	static int	i = 0;
	static int	cpy = 0;

	if (i >= 6)
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
		return (ft_combine("%s:%d", N6, cpy++));
	return (NULL);
}

void	*work(void *in)
{
	t_philo	*data;

	data = (t_philo *)in;
	while (1)
	{
		pthread_mutex_lock(&data->ptr->lock);
		if (data->ptr->i >= data->ptr->end)
		{
			printf("\x1B[32m%10s %d\n\x1B[37m", data->name, data->time);
			pthread_mutex_unlock(&data->ptr->lock);
			return (NULL);
		}
		else
		{
			data->ptr->i++;
			usleep(250);
			data->time++;
			printf("%llu %s %d\n", get_time(), data->name, data->ptr->i);
		}
		pthread_mutex_unlock(&data->ptr->lock);
	}
	return (in);
}

int	main(void)
{
	int				save;
	pthread_t		t1[200];
	t_philo			ph[200];
	t_data			info;
	int				size;

	save = 100;
	info.end = save * 2000;
	info.i = 0;
	get_time();
	size = save;
	pthread_mutex_init(&info.lock, NULL);
	while (size--)
	{
		ph[size].time = 0;
		ph[size].name = give_name();
		ph[size].ptr = &info;
		pthread_create(&t1[size], NULL, &work, &ph[size]);
	}
	size = save;
	while (size--)
		pthread_join(t1[size], NULL);
	pthread_mutex_destroy(&info.lock);
	unsigned long long time = get_time();
	if (time / 1000 > 60)
		printf("end at minute: %llu:%llu\n", time / 1000 / 60, time);
	else
		printf("end at segond : %llu\n", time / 1000);
	return (0);
}
