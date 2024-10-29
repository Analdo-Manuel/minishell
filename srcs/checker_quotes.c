/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marccarv <marccarv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 09:48:11 by almanuel          #+#    #+#             */
/*   Updated: 2024/10/29 08:34:43 by marccarv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static size_t	checker(const char *str)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	while (str[i])
	{
		if (str[i] == 34)
			j++;
		if (str[i] == 39)
			k++;
		i++;
	}
	if (j % 2 == 0 && k % 2 == 0)
		return (1);
	else
		return (0);
}

size_t	checker_quotes(const char *str)
{
}

static size_t	primary_alloc(const char *str)
{
	char	c;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == 34)
		{
			i++;
			while (str[i++] != 34)
				;
		}
		else if (str[i] == 39)
		{
			i++;
			while (str[i++] != 39)
				;
		}
		if (str[i] == ' ')
			j++;
		i++;
	}
	return (j);
}

static size_t	second_alloc(const char *str)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[i] && str[i] != 32 && str[i] != 34 && str[i++] != 39)
		j++;
	return (j);
}

static size_t	second_alloc(const char *str)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[i] && str[i] != 32)
	{
		if (str[i] == 34)
		{
			while (str[++i] != 34)
				j++;
			break ;
		}
		else if (str[i] == 39)
		{
			while (str[++i] != 39)
				j++;
			break ;
		}
		j++;
		i++;
	}
	return (j);
}

char	**quotes_split(const char *str)
{
	char	**p;
	int	i;
	int	j;
	int	k;
	bool	s;

	i = 0;
	j = 0;
	p = (char **) malloc(sizeof(char *) * (primary_alloc(str) + 1));
	while (str[i])
	{
		while (str[i] || str[i] == ' ')
			i++;
		s = false;
		k = 0;
		p[j] = (char *) malloc(sizeof(char) * (second_alloc(str + i) + 1));
		while (str[i] && str[i] != ' ')
		{
			if (str[i] == 34 || str[i] == 39)
			{
				if (str[i] == 39)
				{
				}
				else if (str[i] == 34)
				{
					if (str[i] == '$')
					{
						i++;
						p[j][k] = '\0';
						p[j] = expand_variable(p[j], str, &i);
						s = true;
						break ;
					}
				}
				break;
			}
			p[j][k++] = str[i++];
		}
		if (s == true)
			p[j][k] = '\0';
		j++;
	}
}
