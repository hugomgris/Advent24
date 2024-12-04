/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advent3-1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:38:54 by hmunoz-g          #+#    #+#             */
/*   Updated: 2024/12/04 09:40:08 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
xXx---Day 3 part 1---xXx

Today's puzzle involves processing corrupted memory to extract and sum valid "mul(X,Y)" instructions. 
The goal is to multiply the numbers in each valid "mul(X,Y)" instruction and add up the results.

My approach starts by scanning the memory for valid "mul(X,Y)" instructions using a regular expression. 
The regex is designed to match instructions of the form "mul(X,Y)", where both X and Y are numbers between 1 and 3 digits long. 

Once a valid "mul(X,Y)" instruction is found, I use `sscanf` to extract the numbers X and Y, then multiply them. 
Each valid multiplication result is accumulated in a total sum. 

Invalid characters or malformed instructions are ignored, ensuring only the correctly formatted "mul(X,Y)" instructions are processed. 
The final result is the sum of all valid multiplication results from the input memory.
*/

#include "../lib/libft.h"
#include <regex.h>

char	**extract_muls(int fd)
{
	char		**results = NULL;
	int			results_count = 0;
	int			start;
	int			end;
	char		*line = get_next_line(fd);
	const char	*cursor;
	regex_t		regex;
	regmatch_t	matches[2];

	if (regcomp(&regex, "mul\\([0-9]{1,3},[0-9]{1,3}\\)", REG_EXTENDED) != 0)
	{
		perror("Regex compilation error");
		return (NULL);
	}
	while (line)
	{
		cursor = line;
		while (regexec(&regex, cursor, 1, matches, 0) == 0)
		{
			start = matches[0].rm_so;
			end = matches[0].rm_eo;
			if (end - start >= 8 && end - start <= 12)
			{
				results = realloc(results, sizeof(char *) * (results_count + 1));
				results[results_count] = strndup(cursor + start, end - start);
				results_count++;
			}
			cursor += end;
		}
		free(line);
		line = get_next_line(fd);
	}
	regfree(&regex);
	if (results)
	{
		results = realloc(results, sizeof(char *) * (results_count + 1));
		results[results_count] = NULL;
	}
	return (results);
}

int	process_muls(char **tab)
{
	int	total;
	int	x;
	int	y;

	total = 0;
	if (!tab)
		return (0);
	for (int i = 0; tab[i]; i++)
	{
		if (sscanf(tab[i], "mul(%d, %d)", &x, &y) == 2)
		{
			total += x * y;
		}
		else
		{
			perror("Malformed tab");
		}
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
	res = process_muls(tab);
	printf("res: %d", res);
	ft_free(tab);
	close(fd);
	return (0);
}
