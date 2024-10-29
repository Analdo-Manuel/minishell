/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almanuel <almanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 10:47:27 by almanuel          #+#    #+#             */
/*   Updated: 2024/10/29 18:22:28 by almanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*str_alloc(char	*s1, char c)
{
	char	*p;
	size_t	i;

	i = -1;
	p = (char *) malloc(sizeof(char) * (ft_strlen(s1) + 2));
	while (s1[++i])
		p[i] = s1[i];
	p[i++] = c;
	p[i] = '\0';
	free(s1);
	return (p);
}

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
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

char	*expand_variable(char *s1, char *s2, t_valuer *val)
{
	char	*get_valuer;
	char	*str;
	size_t	j;
	int		alloc;

	j = val->i;
	alloc = 0;
	while (s2[val->i] && s2[val->i] != 32 && s2[val->i] \
			!= '$' && s2[val->i] != 34 && s2[val->i] != 39)
	{
		alloc++;
		val->i++;
	}
	str = (char *) malloc (sizeof(char) * (alloc + 1));
	alloc = 0;
	while (j < val->i)
		str[alloc++] = s2[j++];
	str[alloc] = '\0';
	get_valuer = getenv(str);
	free (str);
	if (get_valuer)
		return (ft_strjoin(s1, get_valuer));
	return (s1);
}
