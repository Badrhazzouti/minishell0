/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_processor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhazzout <bhazzout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 00:27:03 by bhazzout          #+#    #+#             */
/*   Updated: 2023/04/17 22:19:07 by bhazzout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	space_before(char *input, int i)
{
	if (input[i - 1] == ' ' || input[i - 1] == '>' || input[i - 1] == '<')
		return (1);
	return (0);
}

int	space_after(char *input, int i)
{
	if (input[i + 1] == ' ' || input[i + 1] == '>' || input[i + 1] == '<')
		return (1);
	return (0);
}

int	full_length(char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (input[i] == '|' || input[i] == '>' || input[i] == '<')
		{
			if (space_before(input, i) == 0)
				count++;
			if (space_after(input, i) == 0)
				count++;
		}
		count++;
		i++;
	}
	return (count);
}

char	*add_spaces(char *input)
{
	int		i;
	int		j;
	char	*str;
	int		flag;

	i = 0;
	j = 0;
	str = malloc (full_length(input) + 1);
	if (!str)
		return (NULL);
	while (input[i])
	{
		if (input[i] == '|' || input[i] == '>' || input[i] == '<')
		{
			if (space_before(input, i) == 0)
				str[j++] = ' ';
			if (space_after(input, i) == 0)
				flag = 0;
		}
		str[j] = input[i];
		j++;
		i++;
		if (flag == 0)
			str[j++] = ' ';
		flag = 1;
	}
	str[j] = '\0';
	printf("this is my line: %s\n", str);
	return (str);
}