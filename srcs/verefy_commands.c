/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verefy_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almanuel <almanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:59:22 by marccarv          #+#    #+#             */
/*   Updated: 2024/10/30 15:28:01 by almanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	realine_prompt(t_data *data)
{
	char	*str;

	data->son = false;
	str = ft_strjoin("\033[1m\033[32m", getenv("USER"));
	str = ft_strjoin(str, "% \033[0m");
	if (!getenv("USER"))
		data->command = readline(BOLD GREEN "minishell% " RESET);
	else
		data->command = readline(str);
	add_history(data->command);
}

static void	verefy_quotes_cont(char *str, int *i, int *quotes_2)
{
	while (str[*i] && str[*i] != 34)
	{
		(*i)++;
		if (str[*i] == 34)
		{
			(*quotes_2)++;
			(*i)++;
			break ;
		}
	}
}

static void	verefy_quotes_cont_2(char *str, int *i, int *quotes)
{
	while (str[*i] && str[*i] != 39)
	{
		(*i)++;
		if (str[*i] == 39)
		{
			(*quotes)++;
			(*i)++;
			break ;
		}
	}
}

int	verefy_quotes(char *str)
{
	int		i;
	int		quotes;
	int		quotes_2;
	bool	verfy;	

	i = 0;
	quotes = 0;
	quotes_2 = 0;
	verfy = true;
	if (str[0] == '\0')
		return (1);
	while (str[i] != '\0')
	{
		if (str[i] == 34)
		{
			i++;
			quotes_2++;
			verfy = false;
			verefy_quotes_cont(str, &i, &quotes_2);
		}
		else if (str[i] == 39)
		{
			i++;
			quotes++;
			verfy = false;
			verefy_quotes_cont_2(str, &i, &quotes);
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
