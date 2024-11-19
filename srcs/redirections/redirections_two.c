/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_two.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marccarv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 09:15:00 by marccarv          #+#    #+#             */
/*   Updated: 2024/11/19 09:15:07 by marccarv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int verefiy_redirect(char *str)
{
	int	i;
	int	j = 0;
	int	l = 0;
	int	k = 0;
	int	m = 0;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 34 && l % 2 == 0)
			j++;
		else if (str[i] == 39 && j % 2 == 0)
			l++;
		if (str[i] == 62 && str[i + 1] == 62 && (str[i + 2] == 62 \
		|| str[i + 2] == 60) && j % 2 == 0 && l % 2 == 0)
		{
			printf("bash: syntax error near unexpected token `%c'\n", str[i + 2]);
			return (3);
		}
		else if (str[i] == 62 && str[i + 1] == 60 \
		&& j % 2 == 0 && l % 2 == 0)
		{
			printf("bash: syntax error near unexpected token `%c'\n", str[i + 1]);
			return (3);
		}
		else if (str[i] == 62 && str[i + 1] == 62 \
		&& j % 2 == 0 && l % 2 == 0)
		{
			i++;
			k++;
		}
		else if (str[i] == 62 && j % 2 == 0 && l % 2 == 0)
			m++;
		else if (str[i] == 60 && str[i + 1] == 60 && (str[i + 2] == 60 \
		|| str[i + 2] == 62) && j % 2 == 0 && l % 2 == 0)
		{
			printf("bash: syntax error near unexpected token `%c'\n", str[i + 2]);
			return (3);
		}
		else if (str[i] == 60 && str[i + 1] == 60 \
		&& j % 2 == 0 && l % 2 == 0)
		{
			i++;
			k++;
		}
		else if (str[i] == 60 && j % 2 == 0 && l % 2 == 0)
			m++;
		i++;
	}
	if (k > 0)
		return (2); 
	else if (m > 0)
		return (1);
	return (0);
}
