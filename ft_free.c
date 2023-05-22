/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 10:24:29 by anboisve          #+#    #+#             */
/*   Updated: 2023/05/22 13:57:43 by anboisve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_free(void *ptr)
{
	if (ptr)
		free(ptr);
	return (NULL);
}

void	free_ph(t_philo **ph, pthread_t	**thread, t_data *data, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		pthread_mutex_destroy(ph[i]->rigth->lock);
		ft_free(thread[i]);
		ft_free(ph[i]->rigth->lock);
		ft_free(ph[i]->rigth);
		ft_free(ph[i]);
		i++;
	}
	ft_free(ph);
	pthread_mutex_destroy(data->msg);
	pthread_mutex_destroy(data->lock);
	ft_free(data->msg);
	ft_free(data->lock);
	ft_free(thread);
}
