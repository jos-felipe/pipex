/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 14:07:02 by josfelip          #+#    #+#             */
/*   Updated: 2024/01/23 14:37:22 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	tty1(t_pipex *pipex, char *envp[])
{
	if (pipex->fd_in > -1 && pipex->fn1 && pipex->fn2 && pipex->fd_out > -1)
	{
		pipex->pid1 = fork();
		if (pipex->pid1 < 0) 
		{
			ft_printf("Fork failed: pid1.\n");
			pipex->status = EXIT_FAILURE;
			safe_exit(pipex);
		}
		if (pipex->pid1 == 0) {
			dup2(pipex->fd_in, STDIN_FILENO);
			dup2(pipex->fd_pipe[1], STDOUT_FILENO);
			close(pipex->fd_pipe[0]);
			close(pipex->fd_pipe[1]);
			execve(pipex->fn1, pipex->argv1, envp);
		}
	}
}

void	tty2(t_pipex *pipex, char *envp[])
{
	if (pipex->fn2)
	{
		pipex->pid2 = fork();
		if (pipex->pid2 < 0) 
		{
			ft_printf("Fork failed: pid2.\n");
			pipex->status = EXIT_FAILURE;
			safe_exit(pipex);
		}
		if (pipex->pid2 == 0) {
			dup2(pipex->fd_pipe[0], STDIN_FILENO);
			dup2(pipex->fd_out, STDOUT_FILENO);
			close(pipex->fd_pipe[0]);
			close(pipex->fd_pipe[1]);
			execve(pipex->fn2, pipex->argv2, envp);
		}
	}
}
