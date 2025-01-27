

#include "philo.h"

static void	print_usage(void)
{
	printf("Error: Invalid arguments\n");
	printf(STR_USAGE);
}

static int	create_philosophers(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_philosophers)
	{
		if (pthread_create(&data->philosophers[i].thread, NULL,
				philosopher_routine, &data->philosophers[i]) != 0)
		{
			clean_exit(data);
			return (1);
		}
	}
	return (0);
}

static void	join_philosophers(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_philosophers)
		pthread_join(data->philosophers[i].thread, NULL);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (!validate_input(argc, argv))
	{
		print_usage();
		return (1);
	}
	memset(&data, 0, sizeof(t_data));
	if (init_data(&data, argc, argv) != 0)
		return (1);
	if (create_philosophers(&data) != 0)
		return (1);
	monitor_philosophers(&data);
	join_philosophers(&data);
	clean_exit(&data);
	return (0);
}
