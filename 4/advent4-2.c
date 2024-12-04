/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advent4-2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:38:54 by hmunoz-g          #+#    #+#             */
/*   Updated: 2024/12/04 09:25:11 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
xXx---Day 4 part 2---xXx

In the second part of the puzzle, the goal is to find two "MAS" words crossing each other to form an 'X' pattern. 
The "MAS" words can be in any diagonal direction and can appear forwards or backwards. 

The four diagonal directions to check are:
  - top_left to bottom_right
  - top_right to bottom_left
  - bottom_left to top_right
  - bottom_right to top_left

The strategy is to search for the character 'A', as it will always be at the intersection of the two "MAS" words. 
Upon finding an 'A', the program checks the four diagonal directions for the "MAS" pattern. 
If a valid "MAS" word is found in two different directions, the result count is incremented. 
The final count reflects the number of such "MAS" crossings found in the array.
*/

#include "../lib/libft.h"

int	is_xmas(char **tab, int rows, int cols, int r, int c)
{
	if (r - 1 < 0 || c - 1 < 0 || r + 1 >= rows || c + 1 >= cols)
	{
		printf("Out of bounds for A at (%d, %d)\n", r, c);
		return (0);
	}

	int tl_br = 0;
	int tr_bl = 0;
	int bl_tr = 0;
	int br_tl = 0;
	if (tab[r - 1][c - 1] == 'M' && tab[r + 1][c + 1] == 'S')
	{
		printf("\033[0;33mTop-left to Bottom-right match for A at (%d, %d)\033[0m\n", r, c);
		tl_br = 1;
	}
	if (tab[r - 1][c + 1] == 'M' && tab[r + 1][c - 1] == 'S')
	{
		printf("\033[0;34mTop-right to Bottom-left match for A at (%d, %d)\033[0m\n", r, c);
		tr_bl = 1;
	}
	if (tab[r + 1][c - 1] == 'M' && tab[r - 1][c + 1] == 'S')
	{
		printf("\033[0;32mBottom-left to Top-right match for A at (%d, %d)\033[0m\n", r, c);
		bl_tr = 1;
	}
	if (tab[r + 1][c + 1] == 'M' && tab[r - 1][c - 1] == 'S')
	{
		printf("\033[0;35mBottom-right to Top-left match for A at (%d, %d)\033[0m\n", r, c);
		br_tl = 1;
	}
	if ((tl_br && bl_tr) || (br_tl && tr_bl) || (br_tl && bl_tr) || (tl_br && tr_bl) || (tr_bl && br_tl))
	{
		printf("\033[0;31mFound X-MAS centered at (%d, %d)\033[0m\n", r, c);
		return (1);
	}
	return (0);
}

int	count_xmas(char **tab, int rows, int cols)
{
	int	count;

	count = 0;
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			if (tab[r][c] == 'A')
			{
				printf("Checking A at \033[1;34m(%d, %d)\033[0m\n", r, c);
				if (is_xmas(tab, rows, cols, r, c))
					count++;
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
	word_count = count_xmas(tab, 140, ft_strlen(tab[0]));
	printf("\033[1;31mThe X-MAS pattern appears %d times\033[0m\n", word_count);
	ft_free(tab);
	close(fd);
	return (0);
}
