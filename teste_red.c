/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste_red.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almanuel <almanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:59:27 by almanuel          #+#    #+#             */
/*   Updated: 2024/11/06 11:19:07 by almanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

#endif

static char	*ft_strdup(char *src)
{
	char	*str;
	size_t	i;

	i = 0;
	while (src[i])
		i++;
	str = (char *) malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	i = -1;
	while (src[++i])
		str[i] = src[i];
	str[i] = '\0';
	return (str);
}

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

int	main(void)
{
	char	*tmp;
	int	fd;
	
	//fd = open(0, O_RDONLY);
	tmp = get_next_line(0);

	while (tmp)
	{
		printf("%s", tmp);
		free(tmp);
		tmp = get_next_line(0);
	}
	free(tmp);
	close(fd);
	return 0;
}