/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_deleter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhazzout <bhazzout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 10:38:19 by bhazzout          #+#    #+#             */
/*   Updated: 2023/05/03 14:33:21 by bhazzout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sub_lenght(char *str, int i, char c)
{
	(void) c;
	while (str[i])
	{
		
		i++;
	}
	return (0);
}

// char	*quote_processor(char *str)
// {
// 	int	i;
// 	int	flag;
// 	int	count;
// 	int	j;

// 	i = 0;
// 	flag = 0;
// 	count = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '"')
// 		{
// 			count--;
// 			// flag += 1;
// 			j = i + 1;
// 			while (str[j])
// 			{
// 			printf("[%c]", str[j]);
// 				if (str[j] == '"')
// 				{
// 					count--;
// 					j++;
// 					i++;
// 					break;
// 				}
// 				j++;
// 				i++;
// 				count++;
// 			}
// 		}
// 		else if (str[i] == '\'')
// 		{
// 			count--;
// 			j = i + 1;
// 			while (str[j])
// 			{
// 				if (str[j] == '"')
// 				{
// 					count--;
// 					break;
// 				}
// 				j++;
// 				i++;
// 				count++;
// 			}
// 		}
// 		// printf("this is i : %d\n", i);
// 		i++;
// 		count++;
// 	}
// 	printf("the count is : %d\n", count);
// 	return (str);
// }

// int	get_f_index(char *str)
// {
// 	int	i;
// 	int	index = 0;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '\'' || str[i] == '"')
// 		{
// 			index = i;
// 			break ;
// 		}
// 		i++;
// 	}
// 	return (index);
// }

void	skip_quotes(char *str, int *i)
{
	char	c;

	c = str[*i];
	while (str[*i] && str[*i + 1])
	{
		if (str[*i] == c && str[*i + 1] == c)
		{
			i++;
		}
		i++;
	}
}

int	no_quotes_len(char *str)
{
	int	i;
	int	flag = 0;
	int	count = 0;
	int	j = 0;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			skip_quotes(str, &i);
		if (str[i] == '\'' || str[i] == '"')
			flag = is_outside(flag, str[i]);
		if ((str[i] == '\'' || str[i] == '"') && flag == 0)
		{
			count--;
			j++;
		}
		count++;
		i++;
	}
	count -= j;
	return (count);
}

char	*quote_processor(char *str)
{
	int	i;
	int	j = 0;
	int	length = 0;
	int	flag = 0;
	char	*cmd;

	i = 0;
	length = no_quotes_len(str);
	cmd = malloc (length + 1);
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"') && flag == 0)
		{
			flag = is_outside(flag, str[i]);
			i++;
		}
		if (str[i] && (str[i] == '\'' || str[i] =='"'))
			flag = is_outside(flag, str[i]);
		if ((str[i] == '\'' || str[i] == '"') && flag == 0)
		{
			flag = is_outside(flag, str[i]);
			i++;
		}
		if (str[i] != '\0')
			cmd[j++] = str[i++];
	}
	cmd[j] = '\0';
	free(str);
	// printf("the cmd is : %s\n", cmd);
	return (cmd);
}

char	**quote_delete(char **cmd)
{
	int		i;
	char	*str;

	i = 0;
	while (cmd[i])
	{
		str = quote_processor(cmd[i]);
		printf("This is the str: (%s)\n", str);
		i++;
	}
	return (cmd);
}