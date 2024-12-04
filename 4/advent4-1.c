/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advent4-1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:38:54 by hmunoz-g          #+#    #+#             */
/*   Updated: 2024/12/04 09:25:53 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
xXx---Day 4 part 1---xXx

Today's puzzle is about array search. 
The goal is to look for the word "XMAS" in any position inside the array, checking all possible directions (vertical, horizontal, and diagonal). 
The word can be written in any direction from a valid starting position.

My approach starts by searching for the letter 'X' because it's always the first letter of the word "XMAS" and marks the potential start of the word. 
Once an 'X' is found, I check for the word in all 8 possible directions: horizontal (left and right), vertical (up and down), and diagonal (all four diagonals).
For each direction, I compare the subsequent characters in the grid to the corresponding characters in the word "XMAS". 

If the word goes out of bounds in any direction, the search for that direction stops immediately. 
If the entire word "XMAS" is found in any direction, I increase the result count by 1. 
The final count reflects how many times "XMAS" appears in the array in any of the 8 possible directions.
*/

#include "../lib/libft.h"

int	search_word(char **tab, int rows, int cols, int start_row, int start_col, int dir_x, int dir_y)
{
	const char	*word;
	int			len;
	int			row;
	int			col;

	word = "XMAS";
	len = 4;
	for (int i = 0; i < len; i++)
	{
		row = start_row + i * dir_x;
		col = start_col + i * dir_y;
		if (row < 0 || row >= rows || col < 0 || col >= cols)
			return (0);
		if (tab[row][col] != word[i])
			return (0);
	}
	return (1);
}

int	count_words(char **tab, int rows, int cols)
{
	int	directions[8][2] = {
	{0, 1}, {0, -1}, {1, 0}, {-1, 0},
	{1, 1}, {1, -1}, {-1, 1}, {-1, -1}
	};
	int	count;

	count = 0;
	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
		{
			if (tab[row][col] == 'X')
			{
				for (int d = 0; d < 8; d++)
				{
					if (search_word(tab, rows, cols, row, col, directions[d][0], directions[d][1]))
						count++;
				}
			}
		}
	}
	return (count);
}

char	**extract_lines(char **tab, int fd)
{
	char	*line;
	char	*cpy;
	int		i;

	i = 0;
	cpy = NULL;
	line = get_next_line(fd);
	while (i < 140)
	{
		cpy = ft_strdup(line);
		tab[i] = cpy;
		free (line);
		line = get_next_line(fd);
		i++;
	}
	return (tab);
}

int	main(void)
{
	int		fd;
	int		word_count;
	char	**tab;

	fd = open("input.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	tab = malloc(sizeof(char *) * 141);
	tab = extract_lines(tab, fd);
	word_count = count_words(tab, 140, ft_strlen(tab[0]));
	printf("The word XMAS appears %d times\n", word_count);
	ft_free(tab);
	close(fd);
	return (0);
}
