/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advent1-2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 09:23:08 by hmunoz-g          #+#    #+#             */
/*   Updated: 2024/12/04 10:20:16 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
xXx---Day 1 part 2---xXx

In this part of the puzzle, the goal is to calculate a "similarity score" between two lists of location IDs.
The similarity score is determined by checking how often each number in the left list appears in the right list.
For each number in the left list, we multiply that number by the number of times it appears in the right list and add the result to the total similarity score.

The approach begins by reading the two lists from a file.
The first step is to parse the input and store the values into two arrays.
After this, the algorithm iterates through each number in the left list.
For each number, it counts how many times that number appears in the right list.

To count repetitions, I use a helper function that iterates through the right list and increments a counter whenever a match is found.
The result of multiplying the number by its count in the right list is added to the total similarity score.

The process continues for every number in the left list.
At the end of the calculation, the program prints the total similarity score, which reflects how similar the two lists are based on the matching numbers and their frequencies.
*/

#include "../lib/libft.h"

static void	make_lists(int *a, int *b, int fd)
{
	char	*line;
	int		a_index;
	int		b_index;
	int		i;
	char	*substr;

	line = get_next_line(fd);
	a_index = 0;
	b_index = 0;
	while (line)
	{
		i = 0;
		a[a_index++] = ft_atoi(line);
		while (ft_isdigit(line[i]))
			i++;
		while (ft_isspace(line[i]))
			i++;
		substr = ft_substr(line, i, ft_strlen(line) - i);
		b[b_index++] = ft_atoi(substr);
		free(substr);
		free(line);
		line = get_next_line(fd);
	}
}

int	get_repetitions(int a, int *b)
{
	int	reps;
	int	i;

	reps = 0;
	i = 0;
	while (b[i])
	{
		if (b[i] == a)
			reps++;
		i++;
	}
	return (reps);
}

int	puzzle(int *a, int *b)
{
	int	res;
	int	i;

	res = 0;
	i = 0;
	while (i < 1000)
	{
		res += a[i] * get_repetitions(a[i], b);
		i++;
	}
	return (res);
}

int	main(void)
{
	int	fd;
	int	*a;
	int	*b;
	int	res;

	a = malloc(sizeof(int) * 1000);
	b = malloc(sizeof(int) * 1000);
	fd = open("input.txt", O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		exit(1);
	}
	make_lists(a, b, fd);
	res = puzzle(a, b);
	printf("res = %d\n", res);
	free(a);
	free(b);
	close(fd);
	return (0);
}
