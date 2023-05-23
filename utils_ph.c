/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ph.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 13:28:32 by anboisve          #+#    #+#             */
/*   Updated: 2023/05/23 16:56:56 by anboisve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_kill(t_philo *philo, t_data *tmp)
{
	pthread_mutex_lock(tmp->msg);
	if (tmp->is_dead == 0)
		printf("%lld %d %s\n", get_time(), philo->id, DIE);
	tmp->is_dead++;
	pthread_mutex_unlock(tmp->msg);
}

void	*rt_ptr(void *ptr)
{
	static void	*mem = NULL;

	if (ptr)
		mem = ptr;
	return (mem);
}

void	close_mutex(t_philo *philo)
{
	if (philo->left)
		pthread_mutex_unlock(philo->left->lock);
	pthread_mutex_unlock(philo->rigth->lock);
}

int	look_fork(t_philo *philo)
{
	t_data	*tmp;
	int		use;

	tmp = rt_ptr(NULL);
	pthread_mutex_lock(tmp->lock);
	if (!philo->left)
		use = 0;
	else if (philo->left->use == 0 && philo->rigth->use == 0)
	{
		use = 1;
		philo->left->use = 1;
		philo->rigth->use = 1;
	}
	else
		use = 0;
	pthread_mutex_unlock(tmp->lock);
	return (use);
}

void	give_back_fork(t_philo *philo)
{
	t_data	*tmp;

	tmp = rt_ptr(NULL);
	close_mutex(philo);
	pthread_mutex_lock(tmp->lock);
	philo->left->use = 0;
	philo->rigth->use = 0;
	pthread_mutex_unlock(tmp->lock);
}
