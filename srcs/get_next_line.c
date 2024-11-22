/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almanuel <almanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:59:27 by almanuel          #+#    #+#             */
/*   Updated: 2024/11/22 15:03:39 by almanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	checker_int(int i, char	*buffer)
{
	buffer[i] = '\0';
	if (i == 0)
		return (1);
	return (0);
}

char    *get_next_line(int fd)
{
    static char    buffer[BUFFER_SIZE];
    char           str[7000000];
    static  int     i;
    static  int     size;
    static  int     b_size;

    if (fd < 0 || BUFFER_SIZE < 1)
        return (NULL);
    i = 0;
    while (1)
    {
        if (b_size >= size)
        {
            size = read(fd, buffer, BUFFER_SIZE);
            b_size = 0;
            if (size <= 0)
                break;            
        }
        str[i++] = buffer[b_size++];
        if (str[i - 1] == '\n')
            break;
    }
    if (checker_int(i, buffer))
		return (NULL);
	return (ft_strdup(buffer));
}