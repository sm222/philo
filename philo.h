/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 14:06:48 by anboisve          #+#    #+#             */
/*   Updated: 2023/04/28 17:53:44 by anboisve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

#include "lib_ft/libft.h"

# define EAT  "is eating🍝"
# define TAKE "took fork🍴"

typedef struct s_data
{
	pthread_mutex_t	lock;
	int				i;
	int				end;
	int				meal_need;
	int				is_dead;

}	t_data;

typedef struct s_fork
{
	pthread_mutex_t	lock;
	int				use;
}	t_fork;

typedef struct s_philo
{
	int		id;
	int		meal;
	char	*name;
	t_data	*ptr;
	int		lock;
	int		time;
	t_fork	*left;
	t_fork	rigth;
}	t_philo;

# define N0 "William"
# define N1 "Antoine"
# define N2 "Raphael"
# define N3 "Brian"
# define N4 "Mathieu"
# define N5 "Zachary"
# define N6 "Zackary"
# define N7 "Pascal"

typedef enum e_name{
	Antoine,
}	t_name;

#endif