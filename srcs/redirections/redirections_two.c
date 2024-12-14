/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_two.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marccarv <marccarv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 09:15:00 by marccarv          #+#    #+#             */
/*   Updated: 2024/12/14 13:23:10 by marccarv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	verefiy_redirect(char *str)
{
	int	i;
	int	j = 0;
	int	l = 0;
	int	k = 0;
	int	m = 0;
	int	n = 0;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 34 && l % 2 == 0)
			j++;
		else if (str[i] == 39 && j % 2 == 0)
			l++;
		if ((str[i] == 62 || str[i] == 60) \
		&& (str[i + 1] == 62 || str[i + 1] == 60) \
		&& (str[i + 2] == 62 || str[i + 2] == 60 \
		|| str[i + 2] == 10 || str[i + 2] == 124) \
		&& j % 2 == 0 && l % 2 == 0)
		{
			while (str[i] == 62 || str[i] == 60 || str[i] == 124)
				i++;
			g_global = 2;
			printf("bash: syntax error near unexpected token `%c'\n", str[i - 1]);
			return (3);
		}
		else if (str[i] == 62 && str[i + 1] == 60 \
		&& j % 2 == 0 && l % 2 == 0)
		{
			while (str[i] == 62 || str[i] == 60 || str[i] == 32)
				i++;
			g_global = 2;
			printf("bash: syntax error near unexpected token `%c'\n", str[i]);
			return (3);
		}
		else if (str[i] == 60 && str[i + 1] == 62 \
		&& j % 2 == 0 && l % 2 == 0)
		{
			n = i + 2;
			while(str[n] == 32)
				n++;
			if (str[n] == '\0')
			{
				g_global = 2;
				printf("bash: syntax error near unexpected token `newline'\n");
				return (3);
			}
			if (str[n] == 10 || str[n] == 124 || str[n] == 60 || str[n] == 62)
			{
				g_global = 2;
				printf("bash: syntax error near unexpected token `%c'\n", str[n]);
				return (3);
			}
			k++;
		}
		else if (str[i] == 62 && str[i + 1] == 62 \
		&& j % 2 == 0 && l % 2 == 0)
		{
			i++;
			n = i + 1;
			while(str[n] == 32)
				n++;
			if (str[n] == '\0')
			{
				g_global = 2;
				printf("bash: syntax error near unexpected token `newline'\n");
				return (3);
			}
			if (str[n] == 10 || str[n] == 124 || str[n] == 60 || str[n] == 62)
			{
				g_global = 2;
				printf("bash: syntax error near unexpected token `%c'\n", str[n]);
				return (3);
			}
			k++;
		}
		else if (str[i] == 60 && str[i + 1] == 60 \
		&& j % 2 == 0 && l % 2 == 0)
		{
			i++;
			n = i + 1;
			while(str[n] == 32)
				n++;
			if (str[n] == '\0')
			{
				g_global = 2;
				printf("bash: syntax error near unexpected token `newline'\n");
				return (3);
			}
			if (str[n] == 10 || str[n] == 124 || str[n] == 60 || str[n] == 62)
			{
				g_global = 2;
				printf("bash: syntax error near unexpected token `%c'\n", str[n]);
				return (3);
			}
			k++;
		}
		else if ((str[i] == 60 || str[i] == 62) && j % 2 == 0 && l % 2 == 0)
		{
			n = i + 1;
			while(str[n] == 32)
				n++;
			if (str[n] == '\0')
			{
				g_global = 2;
				printf("bash: syntax error near unexpected token `newline'\n");
				return (3);
			}
			if (str[n] == 10 || str[n] == 124 || str[n] == 60 || str[n] == 62)
			{
				g_global = 2;
				printf("bash: syntax error near unexpected token `%c'\n", str[n]);
				return (3);
			}
			m++;
		}
		i++;
	}
	if (k > 0)
		return (2);
	else if (m > 0)
		return (1);
	return (0);
}
