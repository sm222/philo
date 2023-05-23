/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 14:00:44 by anboisve          #+#    #+#             */
/*   Updated: 2023/05/23 11:08:32 by anboisve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_is_nb(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] >= '0' && s[i] <= '9')
			i++;
		else
			return (0);
	}
	return (1);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

long	ft_atol(const char *s)
{
	size_t	i;
	int		flp;
	long	val;

	if (!s)
		return (0);
	val = 0;
	flp = 1;
	i = 0;
	while ((s[i] >= '\t' && s[i] <= '\r') || s[i] == ' ')
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			flp *= -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
		val = val * 10 + (s[i++] - '0');
	return (val * flp);
}

int	take_ph_nb(char *s)
{
	int	nb;

	if (!ft_is_nb(s))
		return (0);
	nb = ft_atol(s);
	if (ft_strlen(s) > 3 || (nb > 200 || nb < 1))
		return (-1);
	return (nb);
}

int	get_arg(char *s)
{
	int		nb;
	size_t	len;

	len = ft_strlen(s);
	nb = ft_atol(s);
	if (len > 10 || nb > INT32_MAX || nb < 0 || ft_is_nb(s) < 1)
		return (-1);
	return (nb);
}
