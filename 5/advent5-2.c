/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advent5-2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:38:54 by hmunoz-g          #+#    #+#             */
/*   Updated: 2024/12/05 10:24:53 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
xXx---Day 5 part 2---xXx

In part 2, the incorrect updates need to be corrected (apparently, I have to do all the work around here!!).
The goal is similar to the one of part 1, but the resulting sum is taken from the middle pages of just the corrected updates.

I keep the parsing from part 1.
For each update, I check if it's already valid by following the rules.
If it’s not, I reorder the pages in the update according to the rules.

To reorder the pages, I bubble sort the updates using the rules from the input (instead of a usual ascending bubble sort).
I repeatedly compare each pair of pages, and if they are out of order, I swap them to ensure they follow the correct page ordering.

Once all invalid updates are reordered, the sum calculation is the same as in part 1, just done with the corrected updates.
*/

#include "../lib/libft.h"
#include <stdbool.h>

#define MAX_RULES 1180
#define MAX_UPDATES 210
#define MAX_PAGES_PER_UPDATE 100

typedef struct s_rule {
	int	from;
	int	to;
} t_rule;

typedef struct s_update {
	int	pages[MAX_PAGES_PER_UPDATE];
	int	length;
} t_update;

void	parse_input(t_rule *rules, t_update *updates, int *rule_count, int *update_count, int fd)
{
	char	*line;
	char	*token;
	int		update_mode = 0;
	int		from;
	int		to;

	while ((line = get_next_line(fd)) != NULL)
	{
		line[ft_strcspn(line, "\n")] = '\0';
		if (ft_strlen(line) == 0)
		{
			update_mode = 1;
			free(line);
			continue ;
		}
		if (!update_mode)
		{
			token = ft_strtok(line, "|");
			if (token)
			{
				from = ft_atoi(token);
				token = ft_strtok(NULL, "|");
				if (token)
				{
					to = ft_atoi(token);
					rules[*rule_count].from = from;
					rules[*rule_count].to = to;
					(*rule_count)++;
				}
			}
		}
		else
		{
			t_update update;
			update.length = 0;
			token = ft_strtok(line, ",");
			while (token)
			{
				update.pages[update.length] = ft_atoi(token);
				update.length++;
				token = ft_strtok(NULL, ",");
			}
			updates[*update_count] = update;
			(*update_count)++;
		}
		free(line);
	}
}

void	print_parsing(t_rule *rules, t_update *updates, int rule_count, int update_count)
{
	ft_printf("Parsed %d rules:\n", rule_count);
	for (int i = 0; i < rule_count; i++)
		ft_printf("Rule %d: %d -> %d\n", i, rules[i].from, rules[i].to);
	ft_printf("\nParsed %d updates:\n", update_count);
	for (int i = 0; i < update_count; i++)
	{
		ft_printf("Update %d: ", i);
		for (int j = 0; j < updates[i].length; j++)
		{
			ft_printf("%d ", updates[i].pages[j]);
		}
		ft_printf("\n");
	}
}

int	is_valid_update(t_rule *rules, int rule_count, t_update *update)
{
	int	page_positions[MAX_PAGES_PER_UPDATE];

	for (int i = 0; i < MAX_PAGES_PER_UPDATE; i++)
		page_positions[i] = -1;
	for (int i = 0; i < update->length; i++)
		page_positions[update->pages[i]] = i;
	for (int k = 0; k < rule_count; k++)
	{
		int from = rules[k].from;
		int to = rules[k].to;
		if (page_positions[from] == -1 || page_positions[to] == -1)
			continue ;
		if (page_positions[from] >= page_positions[to])
		{
			return (0);
		}
	}
	return (1);
}

void	reorder_update(t_rule *rules, int rule_count, t_update *update)
{
	for (int i = 0; i < update->length - 1; i++)
	{
		for (int j = i + 1; j < update->length; j++)
		{
			for (int k = 0; k < rule_count; k++)
			{
				if (rules[k].from == update->pages[i] && rules[k].to == update->pages[j])
				{
					int temp = update->pages[i];
					update->pages[i] = update->pages[j];
					update->pages[j] = temp;
					break ;
				}
			}
		}
	}
}

int	puzzle(t_rule *rules, t_update *updates, int rule_count, int update_count)
{
	int	res = 0;

	for (int i = 0; i < update_count; i++)
	{
		t_update *current_update = &updates[i];
		if (!is_valid_update(rules, rule_count, current_update))
		{
			reorder_update(rules, rule_count, current_update);
			int middle_index = current_update->length / 2;
			int middle_page = current_update->pages[middle_index];
			res += middle_page;
		}
	}

	return (res);
}

int	main(void)
{
	t_rule		rules[MAX_RULES];
	t_update	updates[MAX_UPDATES];
	int			rule_count = 0;
	int			update_count = 0;
	int			fd;
	int			res;

	fd = open("input.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	parse_input(rules, updates, &rule_count, &update_count, fd);
	close(fd);
	//print_parsing(rules, updates, rule_count, update_count);
	res = puzzle(rules, updates, rule_count, update_count);
	ft_printf("The sum of middle pages from corrected updates is: %d\n", res);
	return (0);
}
