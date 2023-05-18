/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 11:06:11 by anboisve          #+#    #+#             */
/*   Updated: 2023/05/18 14:48:40 by anboisve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
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
		printf("making ph %d\n", i);
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
*/

int	make_pthread(pthread_t ***thread, int size)
{
	int			i;
	pthread_t	**new;

	i = 0;
	if (size <= 0)
		return (-1);
	new = ft_calloc(size + 1, sizeof(pthread_t *));
	if (!new)
		return (-2);
	while (i < size)
	{
		new[i] = ft_calloc(1, sizeof(pthread_t));
		if (!new[i])
			return (-2);
		i++;
	}
	*thread = new;
	return (1);
}
