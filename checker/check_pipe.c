/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhazzout <bhazzout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 09:13:39 by bhazzout          #+#    #+#             */
/*   Updated: 2023/05/19 20:12:29 by bhazzout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_pipe(char *input)
{
	int i;
	int	flag;

	i = 0;
	flag = 0;
	if (input[i] == '|')
	{
		printf("Error, command line starts with a |.\n");
		return (1);
	}
	while (input[i] && input[i + 1])
	{
		if (input[i] == '\'' || input[i] == '"')
			flag = is_outside(flag, input[i]);
		if ((input[i] == '|' && input[i + 1] == '|') && flag == 0)
		{
			printf("Error, double pipe.\n");
			return (1);
		}
		i++;
	}
	if (input[i] == '|')
	{
		printf("Error, | at the end of the line.\n");
		return (1);
	}
	return (0);
}