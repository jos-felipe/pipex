/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 13:15:59 by josfelip          #+#    #+#             */
/*   Updated: 2024/01/25 18:32:50 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_init(t_pipex *pipex)
{
	pipex->infile = NULL;
	pipex->cmd1 = NULL;
	pipex->cmd2 = NULL;
	pipex->outfile = NULL;
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
	{
		perror(pipex->infile);
		pipex->status = EXIT_FAILURE;
	}
	pipex->fd_out = open(pipex->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->fd_out == -1)
	{
		perror(pipex->outfile);
		pipex->status = EXIT_FAILURE;
		ft_safe_exit(pipex);
	}
	if (pipe(pipex->fd_pipe) == -1)
		perror(pipex->outfile);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;

	ft_init(&pipex);
	ft_validate_user_inputs(argc, argv, &pipex);
	connect_fds(&pipex);
	process_envp(&pipex, envp);
	ft_parse_cmd1(&pipex);
	ft_parse_cmd2(&pipex);
	process_fns(&pipex);
	ft_tty1(&pipex, envp);
	ft_tty2(&pipex, envp);
	ft_safe_exit(&pipex);
}
