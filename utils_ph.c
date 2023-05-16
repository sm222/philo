/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ph.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 13:28:32 by anboisve          #+#    #+#             */
/*   Updated: 2023/05/16 13:51:06 by anboisve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*rt_ptr(void *ptr)
{
	static void	*mem;

	if (ptr)
		mem = ptr;
	return (mem);
}

void	close_mutex(t_philo *philo)
{
	pthread_mutex_unlock(philo->rigth->lock);
	pthread_mutex_unlock(philo->left->lock);
}
