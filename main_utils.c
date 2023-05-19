/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 11:06:11 by anboisve          #+#    #+#             */
/*   Updated: 2023/05/19 12:50:40 by anboisve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	ft_memcpy(void *src, void *dest, size_t size)
{
	if (!src || !dest)
		return ;
	while (size--)
	{
		((unsigned char *)dest)[size] = ((unsigned char *)src)[size];
	}
}
