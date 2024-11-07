/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almanuel <almanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 10:47:50 by almanuel          #+#    #+#             */
/*   Updated: 2024/11/07 15:53:05 by almanuel         ###   ########.fr       */
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
	if (data->home != NULL)
		free(data->home);
	if (data->envp != NULL)
		free_all(data->envp);
	if (data->export != NULL)
		free_all(data->export);
	//free(data->command);
}
