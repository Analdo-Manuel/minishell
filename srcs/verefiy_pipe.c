/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verefiy_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almanuel <almanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 12:53:18 by marccarv          #+#    #+#             */
/*   Updated: 2024/12/11 12:44:46 by almanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	verefiy_pipe(char *str)
{
	int	i;
	int	j = 0;
	int	l = 0;
	int m = 0;
    int pipe = 0;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 34 && l % 2 == 0)
			j++;
		else if (str[i] == 39 && j % 2 == 0)
			l++;
		if (str[0] == 124 && j % 2 == 0 && l % 2 == 0)
		{
			while (str[i] == 124)
				i++;
			printf("bash: syntax error near unexpected token `%c'\n", str[i - 1]);
			return (3);
		}
		else if (str[i] == 124 && str[i + 1] == 124 \
		&& j % 2 == 0 && l % 2 == 0)
		{
			while (str[i] == 124)
				i++;
			printf("bash: syntax error near unexpected token `%c'\n", str[i - 1]);
			return (3);
		}
		else if (str[i] == 124 && str[i + 1] == 124 \
		&& str[i + 2] == 124 && j % 2 == 0 && l % 2 == 0)
		{
			while (str[i] == 124)
				i++;
			printf("bash: syntax error near unexpected token `%c'\n", str[i - 1]);
			return (3);
		}
		else if (str[i] == 124 \
		&& j % 2 == 0 && l % 2 == 0)
		{
			m = i;
			m++;
			while (str[m] && (str[m] == 32 || str[m] == 9))
				m++;
			if (str[m] == '\0' || str[m] == 124)
			{
				printf("bash: syntax error near unexpected token `|'\n");
				return (3);
			}
		}
		if (str[i] == 124 && str[i + 1] != 124 \
		&& str[i -1] != 124 && j % 2 == 0 && l % 2 == 0)
			pipe++;
		i++;
	}
	if (pipe > 0)
		return (1);
	return (0);
}