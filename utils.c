

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

void	print_status(t_data *data, int id, char *status)
{
	pthread_mutex_lock(&data->print_mutex);
	if (!check_if_simulation_finished(data))
		printf("%lld %d %s\n", get_time() - data->start_time, id, status);
	pthread_mutex_unlock(&data->print_mutex);
}

int	validate_number(const char *str)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	if (!str[0])
		return (0);
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		result = result * 10 + (str[i] - '0');
		if (result > INT_MAX)
			return (0);
		i++;
	}
	return (1);
}

int	validate_input(int argc, char **argv)
{
	int	i;

	if (argc != 5 && argc != 6)
		return (0);
	i = 1;
	while (i < argc)
	{
		if (!validate_number(argv[i]))
			return (0);
		i++;
	}
	if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[1]) > 200)
		return (0);
	if (ft_atoi(argv[2]) < 60)
		return (0);
	if (ft_atoi(argv[3]) < 60)
		return (0);
	if (ft_atoi(argv[4]) < 60)
		return (0);
	if (argc == 6 && ft_atoi(argv[5]) <= 0)
		return (0);
	return (1);
}

void	clean_exit(t_data *data)
{
	int	i;

	if (data->forks)
	{
		i = -1;
		while (++i < data->num_philosophers)
			pthread_mutex_destroy(&data->forks[i]);
		free(data->forks);
	}
	pthread_mutex_destroy(&data->meal_mutex);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	if (data->philosophers)
		free(data->philosophers);
}
