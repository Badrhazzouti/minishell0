/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhazzout <bhazzout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:36:24 by bhazzout          #+#    #+#             */
/*   Updated: 2023/04/27 15:17:47 by bhazzout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct t_env
{
	char			*env_name;
	char			*env_value;
	struct t_env	*next;
} t_env;

typedef enum t_enum
{
	CMD_NAME = 1,
	CMD_ARG,
	R_IN_SIG,
	R_OUT_SIG,
	R_OUT_FILE,
	PIPE,
	R_APP_SIG,
	R_APP_FILE,
	R_IN_FILE,
	HEREDOC_SIG,
	HEREDOC_LIM,
	EMPTY,
} t_enum;

char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *s, size_t n);
int		ft_strlen(const char *str);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	get_env(char **env);
t_env	*ft_lstnew(char *name, char *value, t_env *new);
void	ft_lstadd_back(t_env **lst, t_env *new);
char	*add_spaces(char *input);
char	*ft_substr(char const *s, int start, int len);
char	*ft_strjoin(const char *s1, const char *s2);
int		calc_words(const char *s, char c);
int		ft_wordlen(const char *s, int i, char c);
char	*ft_charge(const char *s, int i, char c);
void	*freeini(char **string, int len);
char	**ft_split(const char *s, char sep);
int		ft_strncmp(const char *s1, const char *s2, int n);
int		ft_strcmp(char *s1, char *s2);
int 	check_pipe(char *input);
int		check_redirec_op(char *input);
int 	check_line(char *input);
char	*skip_spaces(char *input);
int		check_quotes(char *input);
int		check_outside(int count);
void	op_order(int *token);


#endif