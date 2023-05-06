/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhazzout <bhazzout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:14:21 by bhazzout          #+#    #+#             */
/*   Updated: 2023/05/06 11:21:47 by bhazzout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isalnum(int i)
{
	if ((i >= 'a' && i <= 'z') || (i >= 'A' && i <= 'Z'))
		return (1);
	else if (i >= '0' && i <= '9')
		return (1);
	else if (i == '_')
		return (1);
	else
		return (0);
}

int	expand_length(char *cmd)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (ft_isalnum(cmd[i]))
	{
		i++;
		count++;
	}
	return (count);
}

int	env_length(char *env)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (env[i])
	{
		if (env[i] == '=')
		{
			count++;
			break ;
		}
		i++;
		count++;
	}
	return (count);
}

int	ft_envcmp(char *s1, char *s2, int length)
{
	int	i;

	i = 0;
	while (i < length)
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
}

char	*get_value(char *cmd, char **env)
{
	int		i;
	char	*str;
	int		length;
	char	*value;
	int		len;

	length = expand_length(cmd);
	// printf("the length : %d\n", length);
	value = NULL;
	str = ft_substr(cmd, 0, length);
	i = 0;
	while (env[i])
	{
		if (ft_envcmp(str, env[i], length) == 0)
		{
			len = env_length(env[i]);
			value = ft_substr(env[i], len, 1000);
			// printf("the string is : %s\n", value);
			break ;
		}
		i++;
	}
	return (value);
}

void	expand_processor(char *cmd, char **env)
{
	int		i;
	char	*str;
	char	*value;
	// char	*full_str;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '$')
		{
			str = ft_substr(cmd, 0, i);
			printf("this is the str: %s\n", str);
			i++;
			if (cmd[i])
				value = get_value(&cmd[i], env);
			str = ft_strjoin(str, value);
			// cmd += (i - 1);
			// free(str);
			// free(value);
			printf("(%s)====>(%s)\n", value, str);
		}
		i++;
	}
	printf("this is the full str: %s\n", str);
}

void	expander(char **cmd, char **env)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (ft_strchr(cmd[i], '$'))
		{
			expand_processor(cmd[i], env);
		}
		i++;
	}
}