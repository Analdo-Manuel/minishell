/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marccarv <marccarv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:21:18 by marccarv          #+#    #+#             */
/*   Updated: 2024/11/27 15:50:00 by marccarv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_wordcount(const char *str, char c)
{
	int	i;
	int	count;

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

static int	ft_wordcpy(const char *str, char c, int i)
{
	int	j;

	j = 0;
	while (str[i + j] && str[i + j] != c)
		j++;
	return (j);
}

char	**ft_split_pipe(char const *str, char c)
{
	char	**p;
	int		i;
	int		j;
	int		k;

	p = (char **) malloc(sizeof(char *) * (ft_wordcount(str, c) + 1));
	i = 0;
	j = 0;
	while (str[i])
	{
		p[j] = (char *) malloc(sizeof(char) * (ft_wordcpy(str, c, i) + 2));
		k = 0;
		while (str[i] && str[i] != c)
			p[j][k++] = str[i++];
		if (str[i] == c)
		{
			i++;
		}
		p[j][k] = '\0';
		j++;
	}
	p[j] = NULL;
	return (p);
}
