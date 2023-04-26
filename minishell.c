/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhazzout <bhazzout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:36:26 by bhazzout          #+#    #+#             */
/*   Updated: 2023/04/26 16:58:50 by bhazzout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_length(char *input)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (input[i] == ' '|| input[i] == '\t')
		i++;
	while (input[i])
	{
		if (input[i] == ' ' || input[i] == '\t')
		{
			while (input[i] == ' ' || input[i] == '\t')
				i++;
			i--;
		}
		len++;
		i++;
	}
	i--;
	if (input[i] == ' ' || input[i] == '\t')
	{
		i--;
		len--;
	}
	return (len);
}

char	*skip_spaces(char *input)
{
	int	i;

	i = 0;
	while (input[i] == ' ' || input[i] == '\t')
		input++;
	while (input[i])
		i++;
	while (input[i - 1] == ' ' || input[i - 1] == '\t')
		i--;
	input[i] = '\0';
	return (input);
}

char	*fill_line(char *input, int len)//get the line with one space separate it's words
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	j = 0;
	line = malloc (len + 1);
	input = skip_spaces(input);
	while (input[i])
	{
		if (input[i] == ' ' || input[i] == '\t')
		{
			while (input[i] == ' ' || input[i] == '\t')
				i++;
			i--;
		}
		line[j] = input[i];
		j++;
		i++;
	}
	line[j] = '\0';
	return (line);
}

// int	check_d_quote(char *input)
// {
// 	int	i;
// 	int	d_quoted;

// 	d_quoted = 0;
// 	i = 0;
// 	while (input[i])
// 	{
// 		if (input[i] == '"')
// 			d_quoted++;
// 		i++;
// 	}
// 	if (d_quoted % 2)
// 		return (1);
// 	return (0);
// }

int	check_outside(int count)
{
	if (count % 2 == 0)
		return (1);
	return (0);
}

int	check_quotes(char *input)
{
	int	i;
	int	d_count;
	int	s_count;

	d_count = 0;
	s_count = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '"')
		{
			if (check_outside(s_count) == 1)
				d_count++;
		}
		if (input[i] == '\'')
		{
			if (check_outside(d_count) == 1)
				s_count++;
		}
		i++;
	}
	if (s_count % 2 != 0)
	{
		printf("there is unclosed single quote.\n");
		return (1);
	}
	if (d_count % 2 != 0)
	{
		printf("there is unclosed double quote.\n");
		return (1);
	}
	return (0);
}


int check_pipe(char *input)
{
	int i;

	i = 0;
	if (input[i] == '|')
	{
		printf("Error, command line starts with a |.\n");
		return (1);
	}
	while (input[i] && input[i + 1])
	{
		if (input[i] == '|' && input[i + 1] == '|')
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

int	check_redirec_op(char *input)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(input);
	if (input[i] == '>' || input[i] == '<')
	{
		printf("Error, the command line starts with %c.\n", input[i]);
		return (1);
	}
	while (input[i])
	{
		if (input[i] == '>' && input[i + 1] == '>' && input[i + 2] == '>')
		{
			printf("Error, problem with > operator.\n");
			return (1);
		}
		if (input[i] == '<' && input[i + 1] == '<' && input[i + 2] == '<')
		{
			printf("Error, problem with < operator.\n");
			return (1);
		}
		i++;
	}
	i--;
	if (input[i] == '>' || input[i] == '<')
	{
		printf("Error, %c at the end of the command line.\n", input[i]);
		return (1);
	}
	return (0);
}

int check_line(char *input)
{
	input = skip_spaces(input);
	if (ft_strchr(input, '\\') || ft_strchr(input, ';') || ft_strchr(input, '&')) //special characters
	{
		printf("Error, special character.\n");
		exit (1);
	}
	if (check_quotes(input))// check if the command line contains an unclosed quote
	{
		printf("Error, unclosed quote.\n");
		exit (1);
	}
	if (check_pipe(input))
		exit (1);
	if (check_redirec_op(input))
		exit (1);
	return (0);
}

void	array_printer(int *input)
{
	int i;

	i = 0;
	while (input[i])
	{
		printf("elmnt--->%d\n", input[i]);
		i++;
	}
}

int	num_elemnts(char **cmd_array)
{
	int	i;

	i = 0;
	while (cmd_array[i])
	{
		i++;
	}
	return (i);
}

int	*array_tokens(char **cmd_array, int elements)
{
	int	*cmd_token;
	int	i;

	printf("this is the elements : %d\n", elements);
	cmd_token = ft_calloc(sizeof (int) , elements + 1);
	if (!cmd_token)
		return (NULL);
	i = 0;
	while (cmd_array[i])
	{
		if (ft_strcmp(cmd_array[i], "|") == 0)
			cmd_token[i] = PIPE;
		else if (ft_strcmp(cmd_array[i], "<") == 0)
			cmd_token[i] = R_IN_SIG;
		else if (ft_strcmp(cmd_array[i], ">") == 0)
			cmd_token[i] = R_OUT_SIG;
		else if (ft_strcmp(cmd_array[i], ">>") == 0)
			cmd_token[i] = R_APP_SIG;
		else if (ft_strcmp(cmd_array[i], "<<") == 0)
			cmd_token[i] = HEREDOC_SIG;
		else if ((i > 0) && (ft_strcmp(cmd_array[i - 1], "<<") == 0))
			cmd_token[i] = HEREDOC_LIM;
		else if ((i > 0) && (ft_strcmp(cmd_array[i - 1], ">>") == 0))
			cmd_token[i] = R_APP_FILE;
		else if ((i > 0) && (ft_strcmp(cmd_array[i - 1], ">") == 0))
			cmd_token[i] = R_OUT_FILE;
		else
			cmd_token[i] = CMD_NAME;
		if ((i > 0) && (cmd_token[i - 1] == CMD_NAME) && 
			ft_strcmp(cmd_array[i], ">") && ft_strcmp(cmd_array[i], "<") && 
			ft_strcmp(cmd_array[i], ">>") && ft_strcmp(cmd_array[i], "<<") && 
			ft_strcmp(cmd_array[i], "|"))
			cmd_token[i] = CMD_ARG;
		i++;
	}
	return (cmd_token);
}

void	get_input(char *input)
{
	int	len;
	char	**cmd_array;
	int	*arr;

	input = readline("Minishell: ");
	len = get_length(input);
	check_line(input);
	input = fill_line(input, len);
	input = add_spaces(input);
	cmd_array = ft_split(input, ' ');
	arr = array_tokens(cmd_array, num_elemnts(cmd_array));
	array_printer(arr);
	add_history(input);
	free (input);
}

int main (int ac, char **av, char **env)
{
	
	char    input;
	(void)  ac;
	(void)  av;
	(void)  env;
	while (1)
	{
		get_input(&input);
	}
	get_env(env);
}