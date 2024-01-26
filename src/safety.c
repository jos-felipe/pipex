/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safety.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:28:45 by josfelip          #+#    #+#             */
/*   Updated: 2024/01/26 12:10:58 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_validate_user_inputs(int argc, char *argv[], char *envp[], \
t_pipex *pipex)
{
	if (argc == 5)
	{
		pipex->infile = argv[1];
		pipex->outfile = argv[4];
		pipex->cmd1 = ft_hacker_protection(argv[2]);
		if (pipex->cmd1 == NULL)
			ft_printf("Invalid cmd1\n");
		pipex->cmd2 = ft_hacker_protection(argv[3]);
		if (pipex->cmd2 == NULL)
		{
			ft_printf("Invalid cmd2\n");
			exit(EXIT_FAILURE);
		}
		if (envp[0] == NULL)
		{
			ft_printf("Environment variables not found\n");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		ft_printf("Usage:\n%s infile cmd1 cmd2 outfile\n", argv[0]);
		exit(EXIT_FAILURE);
	}
}

char	*ft_hacker_protection(char *cmd)
{
	char	*warn_msg;

	warn_msg = "Warning: Malicious input detected, possible cancel point\n";
	if (!cmd[0])
	{
		ft_printf(warn_msg);
		return (NULL);
	}
	if (ft_strchr(cmd, "'") || ft_strchr(cmd, "\"") || ft_strchr(cmd, "\\"))
	{
		ft_printf(warn_msg);
		return (NULL);
	}
	return (cmd);
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
