/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advent1-1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 09:23:08 by hmunoz-g          #+#    #+#             */
/*   Updated: 2024/12/01 10:53:03 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	find_min_index(int *nums)
{
	int	i;
	int	min_i;
	int	min_v;

	min_v = INT_MAX;
	i = 0;
	while (i < 1000)
	{
		if (nums[i] < min_v)
		{
			min_v = nums[i];
			min_i = i;
		}
		i++;
	}
	return (min_i);
}

int	puzzle(int *a, int *b)
{
	int	res;
	int	a_min;
	int	b_min;
	int	i;

	res = 0;
	a_min = 0;
	b_min = 0;
	i = 0;
	while (i < 1000)
	{
		a_min = find_min_index(a);
		b_min = find_min_index(b);
		res += abs(a[a_min] - b[b_min]);
		a[a_min] = 100000;
		b[b_min] = 100000;
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
	close(fd);
	free(a);
	free(b);
	return (0);
}
