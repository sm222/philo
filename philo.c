/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 08:38:44 by anboisve          #+#    #+#             */
/*   Updated: 2024/10/21 12:45:39 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	link_ph(t_philo **ph, int size)
{
	t_philo	**tmp;
	int		i;

	i = 0;
	tmp = ph;
	while (i < size - 1)
	{
		pthread_mutex_init(tmp[i]->rigth->lock, NULL);
		tmp[i + 1]->left = tmp[i]->rigth;
		i++;
	}
	pthread_mutex_init(tmp[i]->rigth->lock, NULL);
	if (size > 1)
		tmp[0]->left = tmp[i]->rigth;
}

void	set_data(t_philo **ph, t_data *data, int i)
{
	ft_bzero(&ph[i]->info, sizeof(*data));
	ph[i]->id = i + 1;
	ph[i]->meal = 0;
	ft_memcpy(data, &ph[i]->info, sizeof(t_data));
}

int	make_ph(t_philo ***ph, t_data *data)
{
	int		i;
	t_philo	**new;

	new = ft_calloc(data->nb_of_ph + 1, sizeof(t_philo *));
	if (!new)
		return (-1);
	i = 0;
	while (i < data->nb_of_ph)
	{
		new[i] = ft_calloc(1, sizeof(t_philo));
		if (!new[i])
			return (-2);
		set_data(new, data, i);
		new[i]->rigth = ft_calloc(1, sizeof(t_fork));
		if (!new[i]->rigth)
			return (-3);
		new[i]->rigth->lock = ft_calloc(1, sizeof(pthread_mutex_t));
		if (!new[i]->rigth->lock)
			return (-4);
		i++;
	}
	link_ph(new, data->nb_of_ph);
	*ph = new;
	return (1);
}

void	start_ph(pthread_t **thread, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_ph)
	{
		pthread_join(*thread[i], NULL);
		i++;
	}
}

int	main(int ac, char **av)
{
	pthread_t	**thread;
	t_philo		**ph;
	t_data		data;
	int			i;

	thread = NULL;
	ph = NULL;
	ft_bzero(&data, sizeof(data));
	if (start_data(&data, ac, av) < 0)
		return (1);
	if (make_ph(&ph, &data) < 1 || make_pthread(&thread, data.nb_of_ph) < 0)
	{
		free_ph(ph, thread, &data, data.nb_of_ph);
		return (printf(MFAIL));
	}
	i = -1;
	while (++i < data.nb_of_ph)
		pthread_create(thread[i], NULL, &task, ph[i]);
	start_ph(thread, &data);
	free_ph(ph, thread, &data, data.nb_of_ph);
}
