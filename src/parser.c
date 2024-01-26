/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 20:11:53 by josfelip          #+#    #+#             */
/*   Updated: 2024/01/26 12:18:18 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_process_envp(t_pipex *pipex, char *envp[])
{
	pipex->path = get_path(envp);
	if (pipex->path == NULL)
	{
		ft_printf("PATH not found\n");
		pipex->status = EXIT_FAILURE;
		ft_safe_exit(pipex);
	}
	pipex->lst_memory = ft_lstnew(pipex->path);
	if (pipex->lst_memory == NULL)
	{
		ft_printf("Memory allocation failed: new list.\n");
		pipex->status = EXIT_FAILURE;
		ft_safe_exit(pipex);
	}
}

void	ft_parse_cmd1(t_pipex *pipex)
{
	if (pipex->cmd1)
	{
		pipex->argv1 = ft_split(pipex->cmd1, ' ');
		if (pipex->argv1 == NULL)
		{
			pipex->status = EXIT_FAILURE;
			ft_printf("Memory allocation failed: %s\n", pipex->cmd1);
			ft_safe_exit(pipex);
		}
		pipex->fn1 = ft_whereis(pipex->argv1[0], pipex->path);
		if (pipex->fn1 == NULL)
			ft_printf("Command not found: %s\n", pipex->argv1[0]);
		else
			ft_lstadd_back(&pipex->lst_memory, ft_lstnew(pipex->fn1));
	}
	else
		pipex->fn1 = NULL;
}

void	ft_parse_cmd2(t_pipex *pipex)
{
	if (pipex->cmd2)
	{
		pipex->argv2 = ft_split(pipex->cmd2, ' ');
		if (pipex->argv2 == NULL)
		{
			ft_printf("Memory allocation failed: %s\n", pipex->cmd2);
			pipex->status = EXIT_FAILURE;
			ft_safe_exit(pipex);
		}
		pipex->fn2 = ft_whereis(pipex->argv2[0], pipex->path);
		if (pipex->fn2 == NULL)
		{
			ft_printf("Command not found: %s\n", pipex->argv2[0]);
			pipex->status = 127;
			ft_safe_exit(pipex);
		}
		ft_lstadd_back(&pipex->lst_memory, ft_lstnew(pipex->fn2));
	}
	else
		pipex->fn2 = NULL;
}
