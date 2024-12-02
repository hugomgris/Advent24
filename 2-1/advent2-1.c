/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advent2-1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:38:54 by hmunoz-g          #+#    #+#             */
/*   Updated: 2024/12/02 17:06:32 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libft.h"

int	is_safe_report(int *levels, int size)
{
	int	is_increasing;
	int	is_decreasing;
	int	i;
	int	diff;

	is_increasing = 1;
	is_decreasing = 1;
	i = 0;
	while (i < size - 1)
	{
		diff = abs(levels[i] - levels[i + 1]);
		if (diff < 1 || diff > 3)
			return (0);
		if (levels[i] < levels[i + 1])
			is_decreasing = 0;
		else if (levels[i] > levels[i + 1])
			is_increasing = 0;
		i++;
	}
	return (is_increasing || is_decreasing);
}

int	*parse_levels(const char *line, int *size)
{
	int		*levels;
	char	*token;

	levels = malloc(sizeof(int) * 100);
	*size = 0;
	token = ft_strtok((char *)line, " ");
	while (token != NULL)
	{
		levels[*size] = ft_atoi(token);
		(*size)++;
		token = ft_strtok(NULL, " ");
	}
	return (levels);
}

int	process_report(int fd)
{
	int		safe_count;
	char	*line;
	int		*levels;
	int		size;

	safe_count = 0;
	line = get_next_line(fd);
	while (line)
	{
		levels = parse_levels(line, &size);
		free(line);
		if (is_safe_report(levels, size))
			safe_count++;
		free(levels);
		line = get_next_line(fd);
	}
	return (safe_count);
}

int	main(void)
{
	int	fd;
	int	safe_count;

	fd = open("input.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	safe_count = process_report(fd);
	printf("Number of safe reports: %d\n", safe_count);
	close(fd);
	return (0);
}
