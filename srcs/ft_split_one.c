/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_one.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analdo <analdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:19:35 by almanuel          #+#    #+#             */
/*   Updated: 2024/10/22 23:48:37 by analdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char    **ft_split_one(char *str)
{
    char    **p;
    int     i;
    int     j;
    int     k;
    
    p = (char **) malloc(sizeof(char *) * 1024);
    i = 0;
    j = 0;
    while (str[i])
    {
        while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
            i++;
        p[j] = (char *) malloc(sizeof(char) * 4096);
        k = 0;
        while (str[i] && str[i] != ' ' && str[i] != '\t')
            p[j][k++] = str[i++];
        p[j][k] = '\0';
        j++;
    }
    p[j] = NULL;
    return (p);
}
