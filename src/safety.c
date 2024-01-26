/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safety.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:28:45 by josfelip          #+#    #+#             */
/*   Updated: 2024/01/25 11:46:54 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_validate_user_inputs(int argc, char *argv[], t_pipex *pipex)
{
	if (argc == 5)
	{
		pipex->infile = argv[1];
		pipex->cmd1 = argv[2];
		pipex->cmd2 = argv[3];
		pipex->outfile = argv[4];
	}
	else
	{
		ft_printf("Usage:\n%s infile cmd1 cmd2 outfile\n", argv[0]);
		exit(EXIT_FAILURE);
	}
}

void	ft_safe_exit(t_pipex *pipex)
{
	if (pipex->fd_in != -1)
		close(pipex->fd_in);
	if (pipex->fd_out != -1)
		close(pipex->fd_out);
	if (pipex->fd_pipe[0] != -1)
		close(pipex->fd_pipe[0]);
	if (pipex->fd_pipe[1] != -1)
		close(pipex->fd_pipe[1]);
	if (pipex->pid1 != -1)
		;
	if (pipex->pid2 != -1)
	{
		waitpid(pipex->pid2, &pipex->status, 0);
		pipex->status = ft_get_exit_status(pipex->status);
	}
	if (pipex->argv1 != NULL)
		free_split(pipex->argv1);
	if (pipex->argv2 != NULL)
		free_split(pipex->argv2);
	if (pipex->lst_memory != NULL)
		free_heap(pipex->lst_memory);
	if (pipex->status != 0)
		exit(pipex->status);
	exit(EXIT_SUCCESS);
}
