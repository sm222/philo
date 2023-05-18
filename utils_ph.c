/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ph.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 13:28:32 by anboisve          #+#    #+#             */
/*   Updated: 2023/05/18 10:46:22 by anboisve         ###   ########.fr       */
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
	print_info("drop fork", philo->id, get_time());
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

void	ft_memcpy(void *src, void *dest, size_t size)
{
	if (!src || !dest)
		return ;
	while (size--)
	{
		((unsigned char *)dest)[size] = ((unsigned char *)src)[size];
	}
}
