/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almanuel <almanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 11:09:30 by almanuel          #+#    #+#             */
/*   Updated: 2024/10/21 16:15:38 by almanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static size_t   count_alloc_1(char *str, char c)
{
    size_t  i;
    size_t  j;

    i = 0;
    j = 0;
    while (str[i] == c)
        i++;
    while (str[i])
    {
        if (str[i] == c)
            j++;
        i++;
    }
    return (j);
}

static size_t   count_alloc_2(char *str, char c, size_t i)
{
    size_t  j;

    j = 0;
    while (str[i])
    {
        if (str[i] == c)
            break ;
        j++;
        i++;
    }
    return (j);
}

char    **ft_split(char *str, char c)
{
    char    **p;
    int     i;
    int     j;
    int     k;
    
    p = (char **) malloc(sizeof(char *) * (count_alloc_1(str, c) + 1));
    if (!p)
        return (NULL);
    i = 0;
    j = 0;
    while (str[i])
    {
        p[j] = (char *) malloc(sizeof(char) * (count_alloc_2(str, c, i) + 1));
        k = 0;
        while (str[i] && str[i] != c)
            p[j][k++] = str[i++];
        if (str[i++] == ':')
            p[j][k++] = '/';
        p[j][k] = '\0';
        j++;
    }
    p[j] = NULL;
    return (p);
}
