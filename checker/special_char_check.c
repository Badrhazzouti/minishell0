/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_char_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhazzout <bhazzout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 09:17:40 by bhazzout          #+#    #+#             */
/*   Updated: 2023/05/19 21:19:45 by bhazzout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_line(char *input)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	input = skip_spaces(input);
	// printf("this is the input : %s\n", input);
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
			flag = is_outside(flag, input[i]);
		if ((input[i] == ';' || input[i] == '\\' || input[i] == '&') && flag == 0)
		{
			write(2, "Syntax error, unexpected token.\n", 32);
			return (1);
		}
		i++;
	}
	if (check_quotes(input))// check if the command line contains an unclosed quote
	{
		return (1);
	}
	if (check_pipe(input))
		return (1);
	if (check_redirec_op(input))
		return (1);
	return (0);
}
