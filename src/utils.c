/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:44:53 by tom               #+#    #+#             */
/*   Updated: 2022/03/14 21:39:16 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @brief  checks if char is a digit (0-9)
 * @param  c: char to be checked
 * @retval true if digit or false
 */
bool	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (true);
	if (c == '-' || c == '+')
		return (true);
	else
		return (false);
}

/**
 * @brief  converts a string into a number (if possible)
 * @param  *str: string to be converted
 * @retval converted string as long long
 */
long long	ft_atoi(const char *str)
{
	long long	i;
	long long	re;
	long long	sign;

	i = 0;
	sign = 1;
	re = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		re = re * 10 + str[i] - '0';
		i++;
	}
	return (re * sign);
}

/**
 * @brief  like malloc, init 0 / NULL for everything
 * @param  count: n of elements
 * @param  size: size of type
 */
void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	p = malloc(count * size);
	if (p == NULL)
		return (NULL);
	memset(p, 0, count * size);
	return (p);
}

/**
 * @brief  writes error message to STDERROR
 * @param  *error: error message
 */
void	ft_print_error(char *error)
{
	int	i;

	i = 0;
	while (error[i] != '\0')
	{
		write(STDERR_FILENO, &error[i], sizeof(char));
		i++;
	}
	write(STDERR_FILENO, "\n", sizeof(char));
}

/**
 * @brief  calls mutex_destroy for all forks
 * @param  **philos: philo array
 */
void	destroy_forks(t_philo	**philos)
{
	int	i;

	i = 0;
	while (philos[i] != NULL)
	{
		// pthread_mutex_destroy(&philos[i]->fork_r);
		i++;
	}
}

/**
 * @brief  free allocated space used for philos
 * @param  **philos: philo array
 */
void	free_philos(t_philo	**philos)
{
	int	i;

	i = 0;
	while (philos[i] != NULL)
	{
		free(philos[i]);
		i++;
	}
	free(philos);
}

void	free_all(t_philo **philos, t_input *input)
{
	destroy_forks(philos);
	free_philos(philos);
	free(input);
}

long	get_time(void)
{
	long			time_ms;
	struct timeval	time;

	gettimeofday(&time, NULL);
	time_ms = (time.tv_sec * 1000);
	time_ms += (time.tv_usec / 1000);
	return (time_ms);
}

void	print_state(t_input *input, t_philo *philo, int status)
{
	long			cur_t;
	long			new_t;

	new_t = get_time();
	cur_t = new_t - input->start_time;
	pthread_mutex_lock(&(input->print_lock));
	if (status == FORK)
		printf("[%ld] %d has taken a fork\n", cur_t, philo->philo_n);
	else if (status == EAT)
		printf("[%ld] %d is eating\n", cur_t, philo->philo_n);
	else if (status == SLEEP)
		printf("[%ld] %d is sleeping\n", cur_t, philo->philo_n);
	else if (status == THINK)
		printf("[%ld] %d is thinking\n", cur_t, philo->philo_n);
	else if (status == DEAD)
		printf("[%ld] %d died\n", cur_t, philo->philo_n);
	pthread_mutex_unlock(&(input->print_lock));
}