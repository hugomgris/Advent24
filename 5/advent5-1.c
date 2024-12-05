/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advent5-1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:38:54 by hmunoz-g          #+#    #+#             */
/*   Updated: 2024/12/05 10:21:49 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
xXx---Day 5 part 1---xXx

Today's puzzle is about determining whether updates to a set of pages are printed in the correct order according to specific rules. 
The goal is to verify if the page numbers in each update follow the given rules, and if so, calculate the sum of the middle pages of the correctly-ordered updates.

My approach starts by parsing the input to extract the page ordering rules and updates.
	- The rules are stored as pairs of pages, indicating the relative order that must be followed when printing the pages.
	- The updates are stored as lists of page numbers that need to be printed.

For each update, I check whether the pages are ordered according to the rules.
I create an array that tracks the position of each page in the update, and for each rule, I verify that the page from must appear before the page to.
If any rule is violated, the update is considered invalid.

If the update is valid, I calculate the middle page of the update by dividing the length of the update by 2 and adding that page number to the result sum.
The final result is the sum of the middle pages of all the valid updates.
*/

#include "../lib/libft.h"

#define MAX_RULES 1180
#define MAX_UPDATES 210
#define MAX_PAGES_PER_UPDATE 100

typedef struct s_rule {
	int	from;
	int to;
} t_rule;

typedef struct s_update{
	int	pages[MAX_PAGES_PER_UPDATE];
	int	length;
}	t_update;

void	parse_input(t_rule *rules, t_update *updates, int *rule_count, int *update_count, int fd)
{
	char	*line;
	char	*token;
	int		update_mode = 0;
	int		from;
	int		to;

	   while ((line = get_next_line(fd)) != NULL)
	{
		line[ft_strcspn(line,  "\n")]  = '\0';
		if (ft_strlen(line)  == 0)
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

void print_parsing(t_rule *rules, t_update *updates, int rule_count, int update_count)
{
	ft_printf("Parsed %d rules:\n", rule_count);
    for (int i = 0; i < rule_count; i++)
    {
        ft_printf("Rule %d: %d -> %d\n", i, rules[i].from, rules[i].to);
    }

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

int	puzzle(t_rule *rules, t_update *updates, int rule_count, int update_count)
{
	int	res  = 0;

	for(int i = 0; i < update_count; i++)
	{
		t_update *current_update = &updates[i];
		int	page_positions[MAX_PAGES_PER_UPDATE];
		for (int j = 0; j < MAX_PAGES_PER_UPDATE; j++)
            page_positions[j] = -1;
		for (int j = 0; j < current_update->length; j++)
			page_positions[current_update->pages[j]] = j;
		int	is_valid  = 1;
		for (int k = 0; k < rule_count; k++)
		{
			int from = rules[k].from;
			int to = rules[k].to;
			if (page_positions[from] == -1 || page_positions[to] == -1)
				continue ;
			if (page_positions[from] >= page_positions[to])
			{
				is_valid = 0;
				break ;
			}
		}
		if (is_valid)
		{
			int	middle_index = current_update->length / 2;
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
	int			update_count  = 0;
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
	ft_printf("The sum of middle pages from valid updates is:%d\n", res);
	return (0);
}
