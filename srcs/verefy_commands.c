/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verefy_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marccarv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:59:22 by marccarv          #+#    #+#             */
/*   Updated: 2024/10/30 12:36:32 by marccarv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	verefy_quotes(char *str)
{
	int	i;
	int	quotes;
	int	quotes_2;
	bool	verfy;	

	i = 0;
	quotes = 0;
	quotes_2 = 0;
	verfy = true;
	while (str[i] != '\0')
	{
		if (str[i] == 34)
		{
			i++;
			quotes_2++;
			verfy = false;
			while (str[i] && str[i] != 34)
			{
				i++;
				if (str[i] == 34)
				{
					quotes_2++;
					i++;
					break ;
				}
			}
		}
		else if (str[i] == 39)
		{
			i++;
			quotes++;
			verfy = false;
			while (str[i] && str[i] != 39)
			{
				i++;
				if (str[i] == 39)
				{
					quotes++;
					i++;
					break ;
				}
			}
		}
		if (verfy == true)
			i++;
		verfy = true;
	}
	if ((quotes % 2 != 0) || (quotes_2 % 2 != 0))
	{
		printf("Error quotes not closed\n");
		return (1);
	}
	return (0);
}
