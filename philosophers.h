/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crepou <crepou@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:16:10 by crepou            #+#    #+#             */
/*   Updated: 2023/05/23 16:16:10 by crepou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# define MAX_INT 2147483647
# define MIN_INT -2147483648

typedef struct s_philosopher
{
	int			left_fork;
	int			right_fork;
	long long	last_time_ate;
	int			times_ate;
	int			id;
	pthread_t	philosopher;
	int			is_dead;
}			t_philosopher;

typedef struct s_info
{
	t_philosopher	*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	printing;
	pthread_mutex_t	eating;
	pthread_mutex_t	satisfied;
	pthread_mutex_t	is_dead;
	pthread_mutex_t	last_time_eating;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				number_of_meals;
	int				number_of_philos;
	int				philo_is_dead;
	long long		init_time;
	int				all_satisfied;
}				t_info;

typedef struct s_args
{
	int		id;
	t_info	*info;
	int		*is_dead;
}			t_args;

int			philosophers(char *argv[], int argc);
int			fill_info(int argc, char *argv[], t_info *info, t_args *args);
int			create_mutex(t_info *info);
long long	get_curr_time(void);
long long	time_diff(long long previous);
void		*actions(void *args);
void		action_print(t_info *info, t_philosopher *philosopher,
				char *str, long long timestamp);
int			join_threads(t_info *info);
int			destroy_threads(t_info *info);
int			destroy_mutexes(t_info *info);
int			eat(t_info *info, t_philosopher *philosopher);
int			check_if_dead(t_info *info);
int			ft_atoi(const char *str);
int			satisfaction_check(t_info *info);
int			count_meals(t_info *info);
int			ft_kill(t_info *info, long long last, int i);
int			eating_proc(t_info *info, t_philosopher *philosopher);
int			is_a_number(char *str);
int			is_an_integer(char *str);
int			error_check(char *str);
int			wrong_arg(int j, char **args, char *argv[]);
int			ft_get_arguments(char *argv[], int argc, char ***args);
char		**ft_split(char const *s, char c);
long long	ft_atol(const char *str);
int			ft_isprint(int argument);
int			ft_isdigit(int argument);
int			ft_strncmp(const char *str1, const char *str2, size_t n);
void		leaks(void);

#endif