/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 14:06:29 by anboisve          #+#    #+#             */
/*   Updated: 2023/04/23 15:54:29 by anboisve         ###   ########.fr       */
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

void	*work(void *in)
{
	int		i;
	t_philo	*data;

	i = 0;
	data = (t_philo *)in;
	pthread_mutex_lock(&data->lock);
	while (i++ < 10000)
	{
		usleep(1000);
		printf("%llu %d\n", get_time(), data->i++);
	}
	pthread_mutex_unlock(&data->lock);
	return (in);
}

int	main(void)
{
	pthread_t		t1, t2;
	t_philo			data;

	data.i = 0;
	get_time();
	pthread_mutex_init(&data.lock, NULL);
	pthread_create(&t1, NULL, &work, &data);
	pthread_create(&t2, NULL, &work, &data);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	printf("%d\n", data.i);
	pthread_mutex_destroy(&data.lock);
	printf("end at %llu\n", get_time());
	return (0);
}
