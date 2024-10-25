/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analdo <analdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 10:47:27 by almanuel          #+#    #+#             */
/*   Updated: 2024/10/25 23:38:29 by analdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*expand_variable(char *s1, char *s2, int *i)
{
	char	*get_valuer;
	char	*str;
	int		j;
	size_t	alloc;

	j = *i;
	alloc = 0;
	while (s2[*i] && s2[*i] != ' ' && s2[*i] != '$')
	{
		alloc++;
		(*i)++;
	}
	str = (char *) malloc (sizeof(char) * alloc);
	alloc = 0;
	while (j < *i)
		str[alloc++] = s2[j++];
	str[alloc] = '\0';
	get_valuer = getenv(str);
	free (str);
	return (ft_strjoin(s1, get_valuer));
}
