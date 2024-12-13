/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almanuel <almanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 10:47:27 by almanuel          #+#    #+#             */
/*   Updated: 2024/12/13 13:34:11 by almanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*str_alloc(char	*s1, char c)
{
	char	*p;
	long	i;

	i = -1;
	p = (char *) malloc(sizeof(char) * (ft_strlen(s1) + 2));
	while (s1[++i])
		p[i] = s1[i];
	p[i++] = c;
	p[i] = '\0';
	free(s1);
	return (p);
}

void	*ft_memset(void *s, int c, long n)
{
	long	i;
	char	*string;

	string = (char *)s;
	i = 0;
	while (i < n)
	{
		string[i] = c;
		i++;
	}
	return (0);
}

void	realine_prompt(t_data *data)
{
	data->command = readline("minishell% ");
	if (data->command != NULL)
	{	
		if (data->command[0] != '\0')
			add_history(data->command);
	}
}

char	*expand_var_red(char *s1)
{
	t_valuer	val;
	char	*str;

	val.i = 0;
	val.j = 0;
	val.str = (char *) malloc(sizeof(char) * 1);
	val.str[0] = '\0';
	while (s1[val.i] && s1[val.i] != '$')
		val.i++;
	val.i++;
	while (s1[val.i] && s1[val.i] != 32 && s1[val.i] != '"' && s1[val.i] != 39)
		val.str = str_alloc(val.str, s1[val.i++]);
	str = getenv(val.str);
	free(val.str);
	free(s1);
	return(ft_strdup(str));
}

char	*expand_var_heredoc(char *s1)
{
	t_valuer	val;
	char	*str;

	val.i = 0;
	val.j = 0;
	val.str = (char *) malloc(sizeof(char) * 1);
	val.str[0] = '\0';
	while (s1[val.i] && s1[val.i] != '$')
		val.i++;
	val.i++;
	while (s1[val.i] && s1[val.i] != 32 && s1[val.i] != '"' && s1[val.i] != 39)
		val.str = str_alloc(val.str, s1[val.i++]);
	str = getenv(val.str);
	free(val.str);
	return(str);
}

char	*checker_expand(t_data *data, const char *str)
{
	t_valuer	val;

	val.i = 0;
	while (data->envp[val.i])
	{
		val.str = (char *) malloc(sizeof(char) * 1);
		val.str[0] = '\0';
		val.j = 0;
		while (data->envp[val.i][val.j] && data->envp[val.i][val.j] != '=')
			val.str = str_alloc(val.str, data->envp[val.i][val.j++]);
		if (ft_strcmp(val.str, str) == 0)
		{
			free(val.str);
			return (&data->envp[val.i][++val.j]);
		}
		val.i++;
		free(val.str);
	}
	data->status = 1;
	return (NULL);
}

char	*expand_variable(t_data *data, char *s1, char *s2, t_valuer *val)
{
	char	*get_valuer;
	char	*str;
	long	j;
	long	alloc;

	j = val->i;
	alloc = 0;
	while (s2[val->i] && s2[val->i] != 32 && s2[val->i] \
			!= '$' && s2[val->i] != 34 && s2[val->i] != 39 && s2[val->i] != '=')
	{
		alloc++;
		val->i++;
	}
	str = (char *) malloc (sizeof(char) * (alloc + 1));
	alloc = 0;
	while (j < val->i)
		str[alloc++] = s2[j++];
	str[alloc] = '\0';
	get_valuer = checker_expand(data, str);
	if (get_valuer != NULL)
	{
		free (str);
		return (ft_strjoin_des(s1, get_valuer));
	}
	free (str);
	return (s1);
}
