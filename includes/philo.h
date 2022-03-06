/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:25:33 by tom               #+#    #+#             */
/*   Updated: 2022/03/06 14:22:06 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/*	external libarys	*/
# include <unistd.h> // write
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
# define RESET "\033[0m"

/*	structs	*/
typedef struct s_input
{
	long long	philo_count;
	long long	time_to_die;
	long long	time_to_eat;
	long long	time_to_sleep;
	long long	eat_n_times;
}				t_input;

typedef struct s_philo
{
	int					philo_n;
	pthread_t			thread_id;
	pthread_mutex_t		fork_r;
	pthread_mutex_t		fork_l;
	bool				wait;
}						t_philo;

/*	input handling	*/
void		ft_print_help(void);
t_input		*init_input(char **argv);

/*	create philos	*/
int			init_philos(t_input *input, t_philo **philos);

/*	utils	*/
void		*ft_calloc(size_t count, size_t size);
void		ft_print_error(char *error);
void		free_philos(t_philo	**philos);
bool		ft_isdigit(int c);
long long	ft_atoi(const char *str);
void		destroy_forks(t_philo	**philos);

#endif
