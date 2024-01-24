/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 13:15:59 by josfelip          #+#    #+#             */
/*   Updated: 2024/01/24 13:16:07 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;

	validate_user_inputs(argc, argv, &pipex);
	connect_fds(&pipex);
	process_envp(&pipex, envp);
	process_cmds(&pipex);
	process_fns(&pipex);
	tty1(&pipex, envp);
	tty2(&pipex, envp);
	safe_exit(&pipex);
}
