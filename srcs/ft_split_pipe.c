/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marccarv <marccarv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:21:18 by marccarv          #+#    #+#             */
/*   Updated: 2024/12/11 12:36:50 by marccarv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_word_matrix(const char *str, char c)
{
	int	i;
	int	count;
	int	m = 0;
	int	n = 0;

	i = 0;
	m = 0;
	n = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == 34 && m % 2 == 0)
			n++;
		else if (str[i] == 39 && n % 2 == 0)
			m++;
		if (str[i] == c && m % 2 == 0 && n % 2 == 0) // analisar melhor
			count++;
		i++;
	}
	return (count);
}

static int	ft_wordcpy(const char *str, char c, int i)
{
	int	j;
	int	m = 0;
	int	n = 0;

	j = 0;
	while (str[i + j])
	{
		if (str[i + j] == 34 && m % 2 == 0)
			n++;
		else if (str[i + j] == 39 && n % 2 == 0)
			m++;
		if (str[i + j] == c && m % 2 == 0 && n % 2 == 0)
			break ;
		j++;
	}
	return (j);
}
// Tinha um erro aqui no ft_wordcpy, estava retornando j - 1 porque começa com zero, o que fazia com que o último caractere não fosse copiado
char	**ft_split_pipe(char const *str, char c)
{
	char	**p;
	int		i;
	int		j;
	int		k;
	int		m = 0;
	int		n = 0;

	i = 0;
	j = 0;
	p = (char **) malloc(sizeof(char *) * (ft_word_matrix(str, c) + 2));
	while (str[i])
	{
		p[j] = (char *) malloc(sizeof(char) * (ft_wordcpy(str, c, i) + 2));
		k = 0;
		while (str[i])
		{
			if (str[i] == 34 && m % 2 == 0)
				n++;
			else if (str[i] == 39 && n % 2 == 0)
				m++;
			if (str[i] == c && m % 2 == 0 && n % 2 == 0)
				break ;
			p[j][k++] = str[i++];
		}
		if (str[i] == c)
		{
			i++;
		}
		p[j][k] = '\0';
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;
		j++;
	}
	p[j] = NULL;
	return (p);
}
