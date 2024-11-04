/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:23:12 by sting             #+#    #+#             */
/*   Updated: 2024/11/04 15:26:41 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void init_args(t_program *program, char **argv, int argc)
{
	program->args.philo_count = ft_atoi(argv[1]);
	program->args.time_to_die = ft_atoi(argv[2]);
	program->args.time_to_eat = ft_atoi(argv[3]);
	program->args.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		program->args.num_times_to_eat = ft_atoi(argv[5]);
	else
		program->args.num_times_to_eat = -1; // ? necessary?
}
// calloc array of forks(mutex)
int	init_mutexes(t_program *program)
{
	int i;

	// init fork mutexes
	program->forks = ft_calloc(program->args.philo_count, sizeof(pthread_mutex_t));
	if (!program->forks)
	{
		printf("Error: ft_callocc\n");
		return (1);
	}
	i = -1;
	while (++i < program->args.philo_count)
		pthread_mutex_init(&program->forks[i], NULL);

	// init other mutexes
	pthread_mutex_init(&program->print_mutex, NULL);
	pthread_mutex_init(&program->do_flag_mutex, NULL);
	pthread_mutex_init(&program->eat_flag_mutex, NULL);
	pthread_mutex_init(&program->start_mutex, NULL);

	return (0);
}

void	init_philo_struct(t_program	*program, int index)
{
	// memset(program->philos, 0, sizeof(t_philo));
	t_philo *philo;

	philo = &program->philos[index];
	philo->id = index + 1;
	philo->program = program;

	// todo: (REVIEW)init left_fork & right fork
	philo->l_fork = &program->forks[index];
	if (index + 1 == program->args.philo_count) // if last element
		philo->r_fork = &program->forks[0];
	else
		philo->r_fork = &program->forks[index + 1];
	philo->eat_flag = NO;
	philo->last_meal = get_current_time();

}

// malloc philos array + init individual philo struct content
int init_philos(t_program *program)
{
	int i;

	program->philos = ft_calloc(program->args.philo_count, sizeof(t_philo));
	if (!program->philos)
	{
		printf("Error: ft_calloc\n");
		return (1);
	}
	i = -1;
	while (++i < program->args.philo_count)
	{
		init_philo_struct(program, i);
	}
	return (0);
}
