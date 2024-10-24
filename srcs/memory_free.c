/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almanuel <almanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 10:47:50 by almanuel          #+#    #+#             */
/*   Updated: 2024/10/23 23:35:26 by analdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_all(char **p)
{
	size_t	i;

	i = 0;
	while (p[i])
		free(p[i++]);
	free(p);
}

void	free_total(t_data *data)
{
	free(data->path_main);
	free_all(data->matrix);
	free(data->command);
}
