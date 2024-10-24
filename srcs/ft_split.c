/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almanuel <almanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 11:09:30 by almanuel          #+#    #+#             */
/*   Updated: 2024/10/23 23:34:22 by analdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static size_t	word_count(const char *str, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != c && (i == 0 || str[i - 1] == c))
			count++;
		i++;
	}
	return (count);
}

static size_t	count(const char *str, char c, size_t i)
{
	size_t	j;

	j = 0;
	while (str[i + j] && str[i + j] != c)
		j++;
	return (j);
}

char	**ft_split(const char *str, char c)
{
	char	**p;
	int		i;
	int		j;
	int		k;

	p = (char **) malloc(sizeof(char *) * (word_count(str, c) + 1));
	i = 0;
	j = 0;
	while (str[i])
	{
		p[j] = (char *) malloc(sizeof(char) * (count(str, c, i) + 2));
		k = 0;
		while (str[i] && str[i] != c)
			p[j][k++] = str[i++];
		if (str[i] == c)
		{
			i++;
			p[j][k++] = '/';
		}
		p[j][k] = '\0';
		j++;
	}
	p[j] = NULL;
	return (p);
}
