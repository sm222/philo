/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 14:06:48 by anboisve          #+#    #+#             */
/*   Updated: 2023/04/24 17:22:13 by anboisve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	pthread_mutex_t	lock;
	int				i;

}	t_data;

typedef struct s_philo
{
	char	*name;
	t_data	*ptr;
	int		lock;
	int		time;
}	t_philo;

# define N0 "William"
# define N1 "Antoine"
# define N2 "Raphael"
# define N3 "Brian"
# define N4 "Mathieu"
# define N5 "Zachary"
# define N6 "Zackary"

typedef enum e_name{
	Antoine,
}	t_name;

#endif