/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhazzout <bhazzout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 14:46:29 by bhazzout          #+#    #+#             */
/*   Updated: 2023/05/17 19:06:19 by bhazzout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_print(char **input)
{
	int i;

	i = 0;
	while (input[i])
	{
		printf("the option is : %s\n", input[i]);
		i++;
	}
}

void	print_list(t_list *list)
{
	t_list *tmp = list;

    while (tmp)
    {
    	t_cmds *node = (t_cmds *)tmp->content;
        printf("the command name is: %s\n", node->cmd_name);
		// split_print(node->option);
		printf("The red is : %s\n", node->files.red);
        tmp = tmp->next;
    }
}

t_cmds	*fill_node(char **cmd_array, int *arr, int i)
{
	int	count;
	int	j;
	int	index = 0;

	t_cmds	*node;
	count = 0;
	node = malloc (sizeof (t_cmds));
	while (i >= 0 && arr[i] != PIPE)
	{
		if (arr[i] == CMD_NAME)
		{
			node->cmd_name = ft_strdup(cmd_array[i]);
		}	
		else if (arr[i] == CMD_ARG)
		{
			count = 0;
			j = i;
			while (i > 0 && arr[i] == CMD_ARG)
			{
				i--;
				count++;
				if (arr[i] != CMD_ARG)
				{
					i++;
					break ;
				}
			}
			node->option = malloc ((count + 1) * sizeof(char *));
			node->option[count] = NULL;
			while (index < count)
			{
				node->option[index] = ft_strdup(cmd_array[j]);
				index++;
				j--;
			}
		}
		else if (arr[i] == R_IN_SIG)
			node->files.red = ft_strdup(cmd_array[i]);
		else if (arr[i] == R_OUT_SIG)
			node->files.red = ft_strdup(cmd_array[i]);
		else if (arr[i] == R_OUT_FILE)
		{
			node->files.type = ft_strdup("Output");
			node->files.file_name = ft_strdup(cmd_array[i]);
		}
		else if (arr[i] == R_APP_SIG)
			node->files.red = ft_strdup(cmd_array[i]);
		else if (arr[i] == R_APP_FILE)
		{
			node->files.type = ft_strdup("APP_file");
			node->files.file_name = ft_strdup(cmd_array[i]);
		}
		else if (arr[i] == R_IN_FILE)
		{
			node->files.type = ft_strdup("Input");
			node->files.file_name = ft_strdup(cmd_array[i]);
		}
		else if (arr[i] == HEREDOC_SIG)
			node->files.red = ft_strdup(cmd_array[i]);
		else if (arr[i] == HEREDOC_LIM)
		{
			node->files.type = ft_strdup("HEREDOC_file");
			node->files.file_name = ft_strdup(cmd_array[i]);
		}
		i--;
	}
	return (node);
}

t_list	**list_cmds(char **cmd_array, int *arr)
{
	int		i;
	t_list *list = NULL;
	t_cmds	*node = NULL;

	i = 0;
	while (arr[i])
	{
		if (arr[i] == PIPE)
		{
			node = fill_node(cmd_array, arr, (i - 1));
			my_lstadd_back(&list, my_lstnew(node));
			node = NULL;
		}
		i++;
	}
	print_list(list);
	return (NULL);
}