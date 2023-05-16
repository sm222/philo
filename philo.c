/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 08:38:44 by anboisve          #+#    #+#             */
/*   Updated: 2023/05/16 11:18:19 by anboisve         ###   ########.fr       */
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
		new[i]->id = i + 1;
		new[i]->meal = 0;
		new[i]->ptr = data;
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

void	free_ph(t_philo **ph, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		ft_free(ph[i]->rigth);
		ft_free(ph[i]);
		i++;
	}
	ft_free(ph);
}

void	start_ph(pthread_t thread[200], t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_ph)
	{
		pthread_join(thread[i], NULL);
		i++;
	}
}

int	main(void)
{
	pthread_t	thread[200];
	t_philo		**ph;
	t_data		data;
	int			i;

	start_data(&data);
	if (make_ph(&ph, &data) < 0)
	{
		free_ph(ph, data.nb_of_ph);
		return (printf("malloc fail\n"));
	}
	i = 0;
	while (i < data.nb_of_ph)
	{
		pthread_create(&thread[i], NULL, &task, ph[i]);
		i++;
	}
	start_ph(thread, &data);
	free_ph(ph, data.nb_of_ph);
}
