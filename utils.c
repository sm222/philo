/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 13:23:24 by anboisve          #+#    #+#             */
/*   Updated: 2023/05/23 09:55:04 by anboisve         ###   ########.fr       */
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

int	start_data(t_data *data, int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (printf(MISS_ARGS), -1);
	data->nb_of_ph = take_ph_nb(av[1]);
	if (!data->nb_of_ph)
		return (-1);
	data->ttd = get_arg(av[2]);
	data->eat = get_arg(av[3]);
	data->sleep = get_arg(av[4]);
	if (data->ttd < 0 || data->eat < 0 || data->sleep < 0)
		return (-3);
	if (ac > 5)
		data->meal_need = get_arg(av[5]);
	else
		data->meal_need = 0;
	data->lock = ft_calloc(1, sizeof(pthread_mutex_t));
	data->msg = ft_calloc(1, sizeof(pthread_mutex_t));
	if (!data->lock || !data->msg)
	{
		printf(MFAIL);
		return (-2);
	}
	pthread_mutex_init(data->lock, NULL);
	pthread_mutex_init(data->msg, NULL);
	rt_ptr(data);
	return (1);
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