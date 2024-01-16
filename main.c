#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int	main(int argc, char *argv[]) {
	int	in;
	int	out;
	int	fd[2];
	char	*infile;
	char	*outfile;

	if (argc == 5)
	{
		infile = argv[1];
		outfile = argv[4];
	}
	else
	{
		printf("Usage: ./pipex file1 cmd1 cmd2 file2\n");
		exit(1);
	}
	
	// Sanity checks on user input
	if (access(infile, F_OK) == -1) 
	{
		perror(infile);
		exit(1);
	}
	else if (access(infile, R_OK) == -1) 
	{
		perror(infile);
		exit(1);
	}
	
	// Creates the news file descriptors
	in = open(infile, O_RDONLY);
	if (in == -1) 
	{
		perror(infile);
		exit(3);
	}
	out = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (out == -1) 
	{
		perror(outfile);
		exit(3);
	}
	if (pipe(fd) == -1) {
		return (1);
	}

	// cmd1
	int pid1 = fork();
	if (pid1 < 0) {
		return 2;
	}
	if (pid1 == 0) {
		dup2(in, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execlp("cat", "cat", NULL);
	}

	// cmd2
	int pid2 = fork();
	if (pid2 < 0) {
		return 3;
	}

	if (pid2 == 0) {
		dup2(fd[0], STDIN_FILENO);
		dup2(out, STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execlp("grep", "grep", "call", NULL);
	}

	close(out);
	close(fd[0]);
	close(fd[1]);

	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return 0;
}