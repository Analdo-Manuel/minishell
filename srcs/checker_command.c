/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almanuel <almanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:33:37 by almanuel          #+#    #+#             */
/*   Updated: 2024/10/23 14:22:59 by almanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*find_executable(t_data *data)
{
    char    *str;
    size_t  i;

    if (access(data->matrix[0], X_OK) == 0 || access(data->matrix[0], F_OK) == 0)
    {
        data->son = true;
        return (data->matrix[0]);
    }
	data->path = getenv("PATH");
	data->path = ft_strdup(data->path);
	data->p = ft_split(data->path, ':');
	free(data->path);
	i = 0;
    while (data->p[i])
	{
		str = ft_strjoin(data->p[i++], data->matrix[0]);
        if (access(str, X_OK) == 0)
        {
        	free_all(data->p);
			return (str);
		}
		free(str);
    }
    free_all(data->p);
    return (NULL);
}
