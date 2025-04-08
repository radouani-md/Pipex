/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:52:31 by mradouan          #+#    #+#             */
/*   Updated: 2025/04/08 15:45:38 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int opening_files(char *in_f, char *out_f, int *infile, int *outfle)
{
	*infile = open(in_f, O_RDONLY);
	if (!*infile)
	   return (0);
	*outfle = open(out_f, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (!*outfle)
	   return (0);
	return (1);
}

int create_connection(int *infile, int *outfile, char **cmd1, char **cmd2, char **paths, char **envp)
{
	int pip_fd[2];
	int id;
	int id_2;
	char *cmd_path;

	if (pipe(pip_fd) == -1)
		return (-1);
	id = fork();
	if (id == -1)
		return (-1);
	if (id == 0)
	{
		close(pip_fd[0]);
		dup2(*infile, STDIN_FILENO); // fblast mn 9raw mn l'input 4adi n9raw mn l infile 
		dup2(pip_fd[1], STDOUT_FILENO); // fblast mn ktbo f l'output (terminal) 4anktbo fl Pipe
		close(*infile);
		close(pip_fd[1]);
		cmd_path = is_accessable(paths, cmd1);
		if (!cmd_path)
		{
			printf("Command Not Found\n");
			exit(1);	
		}
		execve(cmd_path, cmd1, envp);
		perror("execeve (cmd1)");
		exit(1);
	}
	id_2 = fork();
	if (id_2 == -1)
		return (-1);
	if (id_2 == 0)
	{	
		close(pip_fd[1]);
		dup2(pip_fd[0], STDIN_FILENO); // fblast mn 9raw mn l'input 4adi n9raw mn l infile 
		dup2(*outfile, STDOUT_FILENO); // fblast mn ktbo f l'output (terminal) 4anktbo fl Pipe
		close(*outfile);
		close(pip_fd[0]);
		cmd_path = is_accessable(paths, cmd2);
		if (!cmd_path)
		{
			printf("Command Not Found\n");
			exit(1);	
		}
		execve(cmd_path, cmd2, envp);
		perror("execeve (cmd2)");
		exit(1);
	}
	close(pip_fd[0]);
	close(pip_fd[1]);
	waitpid(id, NULL, 0);
	waitpid(id_2, NULL, 0);
	return (1);
}

char **fetch_path(char **envp)
{
	int i, j;
	char *path_value;
	char **paths;

	i = 0;
	while (envp[i])
	{
		j = 0;
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_value = envp[i] + 5;
			paths = md_split(path_value, ':');
			return (paths);
		}
		i++;
	}
	return (NULL);
}

char *is_accessable(char **path, char **cmd)
{
	int i;
	char *full_path;
	char *temp;

	i = 0;
	while (path[i])
	{
		temp = md_strjoin(path[i], "/");
		full_path = md_strjoin(temp, cmd[0]);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		i++;
	}
	return (NULL);
}

int main(int argc, char **argv, char **envp)
{
	int infile;
	int outfile;
	char **cmd1;
	char **cmd2;
	char **paths;

	if (argc != 5)
	{
		write(2, "Usage: ./pipex infile \"cmd1\" \"cmd2\" outfile\n", 45);
		return (1);
	}
	cmd1 = md_split(argv[2], ' ');
	cmd2 = md_split(argv[3], ' ');
	paths = fetch_path(envp);
	if (opening_files(argv[1], argv[4], &infile, &outfile) == 0)
		return (printf("Error of opening files\n"), 1);
	if (create_connection(&infile, &outfile, cmd1, cmd2, paths, envp) == -1)
		return (printf("Error Forking or Piping\n"));
	
	return (0);
}
