/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:19:08 by josfelip          #+#    #+#             */
/*   Updated: 2024/01/23 10:41:16 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	init(t_pipex *pipex, char *argv[])
{
	pipex->infile = argv[1];
	pipex->cmd1 = argv[2];
	pipex->cmd2 = argv[3];
	pipex->outfile = argv[4];
	pipex->fd_in = -1;
	pipex->fd_out = -1;
	pipex->fd_pipe[0] = -1;
	pipex->fd_pipe[1] = -1;
	pipex->pid1 = -1;
	pipex->pid2 = -1;
	pipex->path = NULL;
	pipex->argv1 = NULL;
	pipex->argv2 = NULL;
	pipex->fn1 = NULL;
	pipex->fn2 = NULL;
	pipex->lst_memory = NULL;
	pipex->status = 0;
}

void	connect_fds(t_pipex *pipex)
{
	pipex->fd_in = open(pipex->infile, O_RDONLY);
	if (pipex->fd_in == -1)
		perror(pipex->infile);
	pipex->fd_out = open(pipex->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->fd_out == -1)
		perror(pipex->outfile);
	if (pipe(pipex->fd_pipe) == -1)
		perror(pipex->outfile);
}
