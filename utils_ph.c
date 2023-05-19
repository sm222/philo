/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ph.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 13:28:32 by anboisve          #+#    #+#             */
/*   Updated: 2023/05/19 12:22:45 by anboisve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*rt_ptr(void *ptr)
{
	static void	*mem = NULL;

	if (ptr)
		mem = ptr;
	return (mem);
}

void	close_mutex(t_philo *philo)
{
	pthread_mutex_unlock(philo->rigth->lock);
	pthread_mutex_unlock(philo->left->lock);
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

int	look_fork(t_philo *philo)
{
	t_data	*tmp;
	int		boo;

	tmp = rt_ptr(NULL);
	pthread_mutex_lock(tmp->lock);
	if (philo->left->use == 0 && philo->rigth->use == 0)
	{
		boo = 1;
		philo->left->use = 1;
		philo->rigth->use = 1;
	}
	else
		boo = 0;
	pthread_mutex_unlock(tmp->lock);
	return (boo);
}

void	give_back_fork(t_philo *philo)
{
	t_data	*tmp;

	tmp = rt_ptr(NULL);
	pthread_mutex_lock(tmp->lock);
	philo->left->use = 0;
	philo->rigth->use = 0;
	pthread_mutex_unlock(tmp->lock);
}
