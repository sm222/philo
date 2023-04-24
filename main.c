/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 14:06:29 by anboisve          #+#    #+#             */
/*   Updated: 2023/04/24 17:48:47 by anboisve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

	if (i >= 6)
		i = 0;
	else
		i++;
	if (i == 0)
		return (N0);
	if (i == 1)
		return (N1);
	if (i == 2)
		return (N2);
	if (i == 3)
		return (N3);
	if (i == 4)
		return (N4);
	if (i == 5)
		return (N5);
	if (i == 6)
		return (N6);
	return (NULL);
}

void	*work(void *in)
{
	t_philo	*data;

	data = (t_philo *)in;
	while (1)
	{
		pthread_mutex_lock(&data->ptr->lock);
		if (data->ptr->i >= 50000)
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
	save = 7;
	pthread_t		t1[save];
	t_philo			ph[save];
	t_data			info;
	int				size;

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
	printf("end at : %llu\n", get_time() / 1000);
	return (0);
}
