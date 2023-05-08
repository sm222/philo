/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilse.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:47:21 by anboisve          #+#    #+#             */
/*   Updated: 2023/05/07 09:50:18 by anboisve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_time	get_time(void)
{
	static struct timeval	start = {-1, -1};
	struct timeval			now;
	t_time					new;

	if (start.tv_sec == -1 && start.tv_usec == -1)
		gettimeofday(&start, NULL);
	gettimeofday(&now, NULL);
	new = (now.tv_sec * 1000 - start.tv_sec * 1000) + \
	(now.tv_usec / 1000 - start.tv_usec / 1000);
	return (new);
}

void	*re_ptr(void *ptr)
{
	static void	*p = NULL;

	if (ptr)
		p = ptr;
	return (p);
}

void	ft_bzero(void *ptr, size_t size)
{
	if (!ptr)
		return ;
	while (size--)
		((char *)ptr)[size] = 0;
}

void	*ft_free(void *ptr)
{
	if (ptr)
		free(ptr);
	return (NULL);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*new;

	new = NULL;
	new = malloc(count * size);
	ft_bzero(new, count * size);
	return (new);
}
