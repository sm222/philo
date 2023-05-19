/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 08:38:44 by anboisve          #+#    #+#             */
/*   Updated: 2023/05/19 16:37:20 by anboisve         ###   ########.fr       */
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
	tmp[0]->left = tmp[i]->rigth;
}

void	set_data(t_philo **ph, t_data *data, int i)
{
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

	if (start_data(&data, ac, av) < 0)
		return (1);
	make_pthread(&thread, data.nb_of_ph);
	if (make_ph(&ph, &data) < 0)
	{
		free_ph(ph, data.nb_of_ph);
		return (printf("malloc fail\n"));
	}
	i = 0;
	while (i < data.nb_of_ph)
	{
		pthread_create(thread[i], NULL, &task, ph[i]);
		i++;
	}
	start_ph(thread, &data);
	free_ph(ph, data.nb_of_ph);
}
