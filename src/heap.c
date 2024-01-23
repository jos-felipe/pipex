/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 20:11:53 by josfelip          #+#    #+#             */
/*   Updated: 2024/01/23 10:35:56 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	process_envp(t_pipex *pipex, char *envp[])
{
	pipex->path = get_path(envp);
	if (pipex->path == NULL) 
	{
		ft_printf("PATH not found\n");
		exit(EXIT_FAILURE);
	}
	pipex->lst_memory = ft_lstnew(pipex->path);
	if (pipex->lst_memory == NULL) {
		ft_printf("Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
}