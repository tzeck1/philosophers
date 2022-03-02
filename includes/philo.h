/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:25:33 by tom               #+#    #+#             */
/*   Updated: 2022/03/02 00:09:25 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/*	external libarys	*/
# include <stdio.h> // printf
# include <stdbool.h> // bool type
# include <string.h> // memset
# include <sys/time.h> // gettimeofday
# include <limits.h> // int_max / int_min macros
# include <stdlib.h> // malloc
# include <pthread.h> // pthread functions

# define PRINT_HERE() (printf("in file: %s at line %d\n", __FILE__, __LINE__))

/*	color codes	*/
# define BLUE "\033[38;5;36m"
# define RED "\033[0;31m"
# define YELLOW "\033[0;33m"
# define PURPLE "\033[0;35m"
# define GREEN "\033[0;32m"
# define RESETCOLOR "\033[0m"

/*	structs	*/
typedef struct s_input
{
	long	philo_count;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	eat_n_times;
}	t_input;

/*	input handling	*/
void	ft_print_help(void);
t_input	*init_input(char **argv);

/*	utils	*/
bool	ft_isdigit(int c);
long	ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);

#endif
