/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_one.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almanuel <almanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:19:35 by almanuel          #+#    #+#             */
/*   Updated: 2024/10/25 16:42:06 by almanuel         ###   ########.fr       */
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

char	**ft_split_one(char *str)
{
	char	**p;
	int		i;
	int		j;
	int		k;
	bool	sinal;

	p = (char **) malloc(sizeof(char *) * (word_count(str, ' ') + 1));
	i = 0;
	j = 0;
	while (str[i])
	{
		sinal = false;
		while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
			i++;
		p[j] = (char *) malloc(sizeof(char) * (count(str, ' ', i) + 2));
		k = 0;
		while (str[i] && str[i] != ' ' && str[i] != '\t')
		{	
			if (str[i] == '$')
			{
				i++;
				p[j][k] = '\0';
				p[j] = expand_variable(p[j], str, &i);
				sinal = true;
				break ;
			}
			p[j][k++] = str[i++];
		}
		if (!sinal)
			p[j][k] = '\0';
		j++;
	}
	p[j] = NULL;
	return (p);
}
