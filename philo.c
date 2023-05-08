/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 08:38:44 by anboisve          #+#    #+#             */
/*   Updated: 2023/05/08 17:52:21 by anboisve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	link_ph(t_philo ***ph, int size)
{
	t_philo	**tmp;
	int		i;

	i = 0;
	tmp = (*ph);
	while (i < size - 1)
	{
		tmp[i]->rigth = tmp[i + 1]->left;
		i++;
	}
	tmp[i]->left = (*ph)[0]->rigth;
	return (1);
}

int	make_ph(t_philo ***ph, t_data *data)
{
	int		i;
	t_philo	**new;

	new = ft_calloc(data->nb_of_ph, sizeof(t_philo *));
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
		new[i]->rigth->use = 0;
		i++;
	}
	*ph = new;
	link_ph(ph, data->nb_of_ph);
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

int	main(void)
{
	t_philo	**ph;
	t_data	data;

	data.nb_of_ph = 4;
	if (make_ph(&ph, &data) < 0)
	{
		free_ph(ph, data.nb_of_ph);
		return (printf("malloc fail\n"));
	}
	free_ph(ph, 4);
}
