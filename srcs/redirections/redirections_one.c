/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_one.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almanuel <almanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:55:51 by almanuel          #+#    #+#             */
/*   Updated: 2024/11/06 12:20:37 by almanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool    checker_redirections(char **p)
{
    long    i;
    long    j;

    i = 0;
    while (p[i])
    {
        while (p[i][j])
        {
            if (p[i][j] == '>' || p[i][j] == '<')
                return (true);
            j++;
        }
        i++;
    }
    return (false);
}

void    redirections_simple(t_data, long i)
{
    long    j;
    int     fd;
    
    j = i;
    fd = open();
}

void    redirections_op(t_data *data)
{
    t_valuer val;

    val.i = -1;
    val.j = -1;
    while (data->matrix[++val.i])
    {
        if (ft_strcmp(data->matrix[val.i], ">") || ft_strcmp(data->matrix[val.i], ">"))
        {
            if (data->matrix[val.i + 2] != NULL)
            {
                printf("error de argumento\n");
                return ;
            }
            
        }
            
        while (data->matrix[val.i][++val.j])
        {
            if (data->matrix[val.i][val.j] == '>' && data->matrix[val.i][val.j + 1] == '\0')
            {
                
            }
             
        }
    }
}
