/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 13:23:24 by anboisve          #+#    #+#             */
/*   Updated: 2023/05/18 16:14:56 by anboisve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_time	get_time(void)
{
	static struct timeval	start = {-1, -1};
	struct timeval			now;
	t_time					new;

	if (start.tv_sec == -1 && start.tv_usec == -1)
		gettimeofday(&start, NULL);
	gettimeofday(&now, NULL);
	new = (now.tv_sec * 1000 - start.tv_sec * 1000) + \
	(now.tv_usec / 1000 - start.tv_usec / 1000);
	return (new);
}

void	ft_bzero(void *ptr, size_t size)
{
	if (!ptr)
		return ;
	while (size--)
		((char *)ptr)[size] = 0;
}

void	*ft_free(void *ptr)
{
	if (ptr)
		free(ptr);
	return (NULL);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*new;

	new = NULL;
	new = malloc(count * size);
	if (!new)
		return (NULL);
	ft_bzero(new, count * size);
	return (new);
}

void	start_data(t_data *data)
{
	data->meal_need = 0;
	data->nb_of_ph = 3;
	data->ttd = 410;
	data->eat = 200;
	data->sleep = 200;
	data->lock = ft_calloc(1, sizeof(pthread_mutex_t));
	pthread_mutex_init(data->lock, NULL);
	rt_ptr(data);
}

/*
Do not test with more than 200 philosophers.
- Do not test with time_to_die or time_to_eat or time_to_sleep set
to values lower than 60 ms.
	- Test 5 800 200 200. No philosopher should die.
	- Test 5 800 200 200 7. No philosopher should die and the simulation
should stop when every philosopher has eaten at least 7 times.
- - Test 4 410 200 200. No philosopher should die.
	- Test 4 310 200 100. One philosopher should die.
	- Test with 2 philosophers and check the different times: a death
delayed by more than 10 ms is unacceptable.
- Test with any values of your choice to verify all the requirements.
Ensure philosophers die at the right time, that they don't steal
forks, and so forth.
*/