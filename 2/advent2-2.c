/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advent2-2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:38:54 by hmunoz-g          #+#    #+#             */
/*   Updated: 2024/12/04 09:51:37 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
xXx---Day 2 part 2---xXx

In this part of the puzzle, the analysis is extended by introducing the concept of the "Problem Dampener".
This module allows the reactor to tolerate a single "bad" level in an otherwise safe report.
A report that was previously unsafe may become safe if we can remove a single level and still meet the conditions for a safe report.

The new task is to update the analysis by checking if a report can be made safe by removing one level, on top of the first's part checks.

The conditions for a safe report remain the same:
	1. The levels must be either strictly increasing or strictly decreasing.
	2. The difference between any two adjacent levels must be at least 1 and at most 3.

However, if a report is unsafe but could become safe by removing a single level, it is considered safe.
The logic to implement this is as follows:
- First, every report is processed following instructions of Part 1. If the report is already safe, it is counted as valid.
- If the report is unsafe, I check if removing one of the levels would make the report safe.
	- This is done by trying to remove each level one by one and checking if the resulting report becomes safe.
- If the resulting report becomes safe after removing just one level, it is counted as valid.

The final output is the total number of safe reports, considering the Problem Dampener.
*/

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

//This has +25 lines, which Norminette doesn't like.
//If I break it with helpers, I'll have +5 functions. 
//The only solution is to have 2 files, which I won't do.
int	can_be_safe_by_removing_one(int *levels, int size)
{
	int		i;
	int		j;
	int		*new_levels;
	int		new_size;

	i = 0;
	while (i < size)
	{
		new_size = size - 1;
		new_levels = malloc(sizeof(int) * new_size);
		if (!new_levels)
			return (0);
		j = 0;
		while (j < i)
		{
			new_levels[j] = levels[j];
			j++;
		}
		while (j < new_size)
		{
			new_levels[j] = levels[j + 1];
			j++;
		}
		if (is_safe_report(new_levels, new_size))
		{
			free(new_levels);
			return (1);
		}
		free(new_levels);
		i++;
	}
	return (0);
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
		if (is_safe_report(levels, size)
			|| can_be_safe_by_removing_one(levels, size))
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
