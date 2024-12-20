/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:45:17 by sting             #+#    #+#             */
/*   Updated: 2024/12/02 11:51:21 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// Gets the current time in milliseconds
size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + (time.tv_usec / 1000));
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

void	print_message(t_philo *philo, char *message)
{
	int	timestamp;

	pthread_mutex_lock(&philo->program->do_flag_mutex);
	if (philo->program->do_flag == NO)
	{
		pthread_mutex_unlock(&philo->program->do_flag_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->program->do_flag_mutex);
	pthread_mutex_lock(&philo->program->print_mutex);
	timestamp = get_current_time() - philo->program->start_time;
	printf("%i %i %s\n", timestamp, philo->id, message);
	pthread_mutex_unlock(&philo->program->print_mutex);
}
