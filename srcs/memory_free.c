/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almanuel <almanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 10:47:50 by almanuel          #+#    #+#             */
/*   Updated: 2024/12/15 05:15:16 by almanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_all(char **p)
{
	size_t	i;

	i = 0;
	if (p == NULL)
		return ;
	while (p[i])
		free(p[i++]);
	free(p);
}

void	free_total(t_data *data)
{
	if (data->path_main)
		free(data->path_main);
	if (data->matrix)
		free_all(data->matrix);
	if (data->envp)
		free_all(data->envp);
	if (data->export)
		free_all(data->export);
	if (data->command)
		free(data->command);
	printf("exit\n");
	exit(g_global);
}
void	free_total_exit(t_data *data)
{
	if (data->path_main)
		free(data->path_main);
	if (data->matrix)
		free_all(data->matrix);
	if (data->envp)
		free_all(data->envp);
	if (data->export)
		free_all(data->export);
	if (data->command)
		free(data->command);
}
