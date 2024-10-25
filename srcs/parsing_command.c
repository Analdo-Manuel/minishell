/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almanuel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 10:47:27 by almanuel          #+#    #+#             */
/*   Updated: 2024/10/25 10:47:29 by almanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*extract_comand(char *input, int *i)
{
	char	*variable;
	int	j;

	j = 0;
	variable = (char *) malloc(sizeof(char) * (ft_strlen(input) + 1));
	while(input[i] && input[i] != ' ' || input[i] != '\t' || input[i] != '\n' || input[i] != 34)
	{
		variable[j] =  input[i];
		j++;
		*i += 1;
	}
	variable = '\0';
	return (variable);
}

char	*expand_empty_variable(char *input)
{
	char	*result;
	int	i;
	int	j;

	i = 0;
	j = 0;
	result = (char *) malloc(sizeof(char) * (ft_strlen(input) + 1));
	while (input[i])
	{
		if (input[i] == '$')
		{
			i++;
			variable_name = extract_comand(input, &i);
			variable_value = getenv(variable_name);
			if (variable_value)
			{
				strcpy(&result[j], variable_value);
				j += ft_strlen(variable_value);
			}
			free(variable_name);
		}
		else
			result[j++] = input[i++];
	}
	result[j] = '\0';
	return (result);
}
