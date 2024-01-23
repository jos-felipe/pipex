/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safety.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:28:45 by josfelip          #+#    #+#             */
/*   Updated: 2024/01/23 10:44:49 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	validate_user_inputs(int argc, char *argv[], t_pipex *pipex)
{
	
	if (argc == 5)
		init(pipex, argv);
	else
	{
		ft_printf("Usage:\n%s infile cmd1 cmd2 outfile\n", argv[0]);
		pipex->status = EXIT_FAILURE;
		safe_exit(pipex);
	}
}

// safe exit
void	safe_exit(t_pipex *pipex)
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
		waitpid(pipex->pid1, &pipex->status, 0);
	if (pipex->pid2 != -1)
		waitpid(pipex->pid2, &pipex->status, 0);
	if (pipex->lst_memory != NULL)
		free_heap(pipex->lst_memory);
	if (pipex->status != 0)
		exit(pipex->status);
	exit(EXIT_SUCCESS);
}