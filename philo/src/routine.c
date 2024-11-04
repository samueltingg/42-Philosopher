/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:17:57 by sting             #+#    #+#             */
/*   Updated: 2024/11/04 10:18:23 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->l_fork);
	print_message(philo, "has taken a fork");
	if (philo->program->args.philo_count == 1)
	{
		ft_usleep(philo->program->args.time_to_die);
		pthread_mutex_unlock(&philo->l_fork);
		return ;
	}
	pthread_mutex_lock(&philo->r_fork);
	print_message(philo, "has taken a fork");

	pthread_mutex_lock(&philo->program->eat_flag_mutex);
	philo->eat_flag = YES;
	print_message(philo, "is eating");
	ft_usleep(philo->program->args.time_to_eat);
	philo->last_meal = get_current_time(); // ! added
	pthread_mutex_unlock(&philo->program->eat_flag_mutex);

	pthread_mutex_lock(&philo->program->eat_flag_mutex);
	philo->eat_flag = NO;
	pthread_mutex_unlock(&philo->program->eat_flag_mutex);

	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(&philo->r_fork);
}

void sleeping(t_philo *philo)
{
	print_message(philo, "is sleeping");
	ft_usleep(philo->program->args.time_to_sleep);
}

void thinking(t_philo *philo)
{
	print_message(philo, "is thinking");
}

void	*philo_routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;

	if (philo->id % 2 == 0) // even num delay
		ft_usleep(50); //! why 50?

    while (1) // Loop until do_flag is NO
    {
        pthread_mutex_lock(&philo->program->do_flag_mutex); // Lock the mutex
        if (philo->program->do_flag == NO) // Check the do_flag
        {
            pthread_mutex_unlock(&philo->program->do_flag_mutex); // Unlock before breaking
            break; // Exit the loop if do_flag is NO
        }
        pthread_mutex_unlock(&philo->program->do_flag_mutex); // Unlock the mutex
        eating(philo);
        sleeping(philo);
        thinking(philo);
    }
	return (NULL);
}
