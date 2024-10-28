/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_one.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almanuel <almanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:19:35 by almanuel          #+#    #+#             */
/*   Updated: 2024/10/28 16:34:10 by almanuel         ###   ########.fr       */
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
static size_t second_alloc(const char *str, int i)
{
    size_t  j;

    j = 0;
    while (str[i] && str[i] != 32)
    {
        if (str[i] == 34)
        {
            while (str[++i] != 34)
                j++;
            break;
        }
        else if (str[i] == 39)
        {
            while (str[++i] != 39)
                j++;
            break;
        }
        j++;
        i++;
    }
    return (j);
}

char	**ft_split_one(char *str)
{
	char	**p;
	int		i;
	int		j;
	int		k;
	bool	sinal;
	bool	s;

	p = (char **) malloc(sizeof(char *) * (word_count(str, ' ') + 2));
	i = 0;
	j = 0;
	while (str[i])
	{
		sinal = false;
		s = false;
		while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
			i++;
		p[j] = (char *) malloc(sizeof(char) * (second_alloc(str, i) + 2));
		k = 0;
		while (str[i] && str[i] != ' ' && str[i] != '\t')
		{
			if (str[i] == 34)
            {
				i++;
                while (str[i] != 34)
                {
					if (str[i] == '$' && str[i + 1] != 34)
			        {
			        	p[j][k] = '\0';
						i++;
				        p[j] = expand_variable(p[j], str, &i);
				        sinal = true;
						s = true;
				        break ;
		        	}
                	p[j][k++] = str[i++];
                }
				i++;
				if (s == false)
					p[j][k] = '\0';
				break;
			}
			p[j][k++] = str[i++];
		}
		if (sinal == false)
			p[j][k] = '\0';
		j++;
	}
	p[j] = NULL;
	return (p);
}
