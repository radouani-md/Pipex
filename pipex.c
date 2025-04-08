/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:52:31 by mradouan          #+#    #+#             */
/*   Updated: 2025/04/08 11:37:08 by mradouan         ###   ########.fr       */
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

int create_connection(int *infile, int *outfile)
{
	int pip_fd[2];
	int id;
	int id_2;

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
	}
	return (1);
}

void fetch_path(char **envp)
{
	int i;

	i = 0;
	while (envp[i])
	{
		if ()
	}
}

int main(int argc, char **argv, char **envp)
{
	int infile;
	int outfile;
	char **cmd1;
	char **cmd2;
	
	cmd1 = md_split(argv[2], ' ');
	cmd2 = md_split(argv[3], ' ');
	if (argc != 5)
	{
		write(2, "Usage: ./pipex infile \"cmd1\" \"cmd2\" outfile\n", 45);
		return (1);
	}
	if (opening_files(argv[1], argv[4], &infile, &outfile) == 0)
		return (printf("Error of opening files\n"), 1);
	if (create_connection(&infile, &outfile) == -1)
		return (printf("Error Forking or Piping\n"));
	fetch_path(envp);
	// while (envp[i])
	// {	
	// 	printf("%s\n", envp[i]);
	// 	i++;
	// }
	// printf("hamza rami\n");
	// execve(cmd1[0], cmd1, envp);
	// printf("weld said");
	
	return (0);
}
