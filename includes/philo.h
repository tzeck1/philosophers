/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:25:33 by tom               #+#    #+#             */
/*   Updated: 2022/02/18 17:24:29 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h> // printf
# include <stdbool.h> // bools
# include <limits.h> // max_int/min_int macros
# include <stdlib.h> // malloc
# include <pthread.h> // pthread functions

# define PRINT_HERE() (printf("in file: %s at line %d\n", __FILE__, __LINE__))

typedef struct s_input
{
	long	philo_count;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	eat_n_times;
}	t_input;

//input handling
t_input	*init_input(char **argv);

//utils
bool	ft_isdigit(int c);
long	ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);

#endif