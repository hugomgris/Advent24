/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advent3-2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:38:54 by hmunoz-g          #+#    #+#             */
/*   Updated: 2024/12/04 09:43:20 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
xXx---Day 3 part 2---xXx

In this part of the puzzle, we need to handle the new instructions "do()" and "don't()" which enable and disable multiplication operations, respectively.

The task now is to scan the same corrupted memory and process the enabled "mul" instructions while taking into account the most recent "do()" or "don't()" instruction.
Initially, all "mul" instructions are enabled.

The approach starts by searching for any of the following three patterns: "mul(X,Y)", "do()", and "don't()". 
- "mul(X,Y)" represents a multiplication instruction, where X and Y are numbers. 
- "do()" enables subsequent "mul" instructions. 
- "don't()" disables subsequent "mul" instructions.

A flag is set, `mul_enabled`, which tracks whether multiplications are enabled or disabled based on the most recent "do()" or "don't()" instruction encountered. 

Once the valid "mul" instructions are identified and enabled, their results are accumulated.
For any invalid or disabled instructions, the result is ignored.
The final count reflects the sum of the results of the enabled "mul" instructions only.
*/

#include "../lib/libft.h"
#include <regex.h>

char	**extract_muls(int fd)
{
	char		**results = NULL;
	int			results_count = 0;
	char		*line = get_next_line(fd);
	const char	*cursor;
	regex_t		regex;
	regmatch_t	matches[2];

	if (regcomp(&regex, "mul\\([0-9]{1,3},[0-9]{1,3}\\)|do\\(\\)|don\\'t\\(\\)", REG_EXTENDED) != 0)
	{
		perror("Regex compilation error");
		return (NULL);
	}
	while (line)
	{
		cursor = line;
		while (match_mul((char *)cursor, &regex, matches))
		{
			if (matches[0].rm_eo - matches[0].rm_so >= 8 &&
				matches[0].rm_eo - matches[0].rm_so <= 12)
			{
				results = realloc(results, sizeof(char *) * (++results_count));
				results[results_count - 1] = strndup(cursor + matches[0].rm_so,
					matches[0].rm_eo - matches[0].rm_so);
			}
			cursor += matches[0].rm_eo;
		}
		free(line);
		line = get_next_line(fd);
	}
	regfree(&regex);
	if (results)
		results = realloc(results, sizeof(char *) * (results_count + 1));
	results[results_count] = NULL;
	return (results);
}

int	process_muls(char **tab)
{
	int	total;
	int	x;
	int	y;
	int	mul_enabled;

	total = 0;
	mul_enabled = 1;
	if (!tab)
		return (0);
	for (int i = 0; tab[i]; i++)
	{
		if (strcmp(tab[i], "do()") == 0)
			mul_enabled = 1;
		else if (strcmp(tab[i], "don't()") == 0)
			mul_enabled = 0;
		else if (mul_enabled && sscanf(tab[i], "mul(%d,%d)", &x, &y) == 2)
			total += x * y;
		else
			fprintf(stderr, "Ignored entry: '%s'\n", tab[i]);
	}
	return (total);
}

int	main(void)
{
	int		fd;
	int		i;
	int		res;
	char	**tab;

	fd = open("input.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	tab = extract_muls(fd);
	int j = 0;
	while (tab[j])
	{
		printf("%s\n", tab[j]);
		j++;
	}
	res = process_muls(tab);
	printf("res: %d", res);
	ft_free(tab);
	close(fd);
	return (0);
}
