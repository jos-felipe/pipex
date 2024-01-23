#include "../includes/pipex.h"

int	main(int argc, char *argv[], char *envp[]) {
	t_pipex	pipex;

	validate_user_inputs(argc, argv, &pipex);
	connect_fds(&pipex);
	process_envp(&pipex, envp);
	process_cmds(&pipex);
	process_fns(&pipex);
	tty1(&pipex);
	tty2(&pipex);
	safe_exit(&pipex);
}
