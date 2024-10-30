/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binarios.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almanuel <almanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:55:15 by almanuel          #+#    #+#             */
/*   Updated: 2024/10/30 15:35:15 by almanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    builtins_echo(t_data *data)
{
    size_t  i;

    i = 1;
    if (ft_strcmp(data->matrix[1], "-n") != 0)
    {
        while (data->matrix[i])
        {
            printf("%s", data->matrix[i++]);
            if (data->matrix[i])
            printf(" ");
        }
        printf("\n");
    }
    else
    {
        while (ft_strcmp(data->matrix[i], "-n") == 0)
            i++;
        while (data->matrix[i])
        {
            printf("%s", data->matrix[i++]);
            if (data->matrix[i])
                printf(" ");
        }
    }
            
}

bool    checker_builtins(t_data *data)
{
    if (ft_strcmp(data->matrix[0], "echo") == 0)
    {
        builtins_echo(data);
        free_all(data->matrix);
        return (false);
    }
    return (true);   
}