/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 18:21:11 by maemaldo          #+#    #+#             */
/*   Updated: 2024/06/11 14:31:38 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_close_all(t_pipex *pipex)
{
	close(pipex->tube[0]);
	close(pipex->tube[1]);
	close(pipex->infile);
	close(pipex->outfile);
	return (1);
}

int	ft_cmd1(t_pipex pipex, char *arg, char *envp[])
{
	if (dup2(pipex.tube[1], 1) == -1)
		return (ft_close_all(&pipex));
	close(pipex.tube[0]);
	close(pipex.tube[1]);
	if (dup2(pipex.infile, 0) == -1)
		return (ft_close_all(&pipex));
	close(pipex.infile);
	close(pipex.outfile);
	pipex.cmd_args = ft_token(arg, ' ');
	if (pipex.cmd_args && pipex.cmd_args[0])
	{
		pipex.cmd = ft_get_cmd_path(pipex.cmd_paths, pipex.cmd_args, envp);
		if (pipex.cmd && execve(pipex.cmd, pipex.cmd_args, envp) == -1)
		{
			perror(pipex.cmd);
		}
	}
	else
		ft_putstr_fd("command not found:\n", 2);
	ft_free_tab(pipex.cmd_args);
	return (127);
}

int	ft_cmd2(t_pipex pipex, char *arg, char *envp[])
{
	if (dup2(pipex.tube[0], 0) == -1)
		return (ft_close_all(&pipex));
	close(pipex.tube[1]);
	close(pipex.tube[0]);
	if (dup2(pipex.outfile, 1) == -1)
		return (ft_close_all(&pipex));
	close(pipex.infile);
	close(pipex.outfile);
	pipex.cmd_args = ft_token(arg, ' ');
	if (pipex.cmd_args && pipex.cmd_args[0])
	{
		pipex.cmd = ft_get_cmd_path(pipex.cmd_paths, pipex.cmd_args, envp);
		if (pipex.cmd && execve(pipex.cmd, pipex.cmd_args, envp) == -1)
		{
			perror(pipex.cmd);
		}
	}
	else
		ft_putstr_fd("command not found:\n", 2);
	ft_free_tab(pipex.cmd_args);
	return (1);
}

void	ft_open_files(char **argv, t_pipex *pipex)
{
	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile < 0)
		perror(argv[1]);
	pipex->outfile = open(argv[4], O_CREAT | O_TRUNC | O_RDWR, 0666);
	if (pipex->outfile < 0)
		perror(argv[4]);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc != 5)
		return (1);
	ft_memset(&pipex, 0, sizeof(t_pipex));
	ft_open_files(argv, &pipex);
	if (pipe(pipex.tube) < 0)
		ft_putstr_fd("pipe() failed\n", 2);
	pipex.paths = ft_find_path(envp);
	pipex.cmd_paths = ft_split(pipex.paths, ':');
	pipex.pid1 = fork();
	if (pipex.pid1 == -1)
		return (0);
	if (pipex.pid1 == 0)
	{
		ft_cmd1(pipex, argv[2], envp);
		ft_free_tab(pipex.cmd_paths);
		return (127);
	}
	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
	{
		ft_cmd2(pipex, argv[3], envp);
		ft_free_tab(pipex.cmd_paths);
		return (127);
	}
	close(pipex.tube[1]);
	close(pipex.tube[0]);
	close(pipex.infile);
	close(pipex.outfile);
	while (1)
		if (waitpid(-1, NULL, 0) == -1)
			break ;
	ft_free_tab(pipex.cmd_paths);
	return (0);
}
