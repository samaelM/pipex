/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 18:21:11 by maemaldo          #+#    #+#             */
/*   Updated: 2024/04/11 14:45:41 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_cmd1(t_pipex pipex, char *arg, char *envp[])
{
	pipex.cmd_args = ft_split(arg, ' ');
	pipex.cmd = ft_get_cmd_path(pipex.cmd_paths, pipex.cmd_args[0]);
	dup2(pipex.tube[1], 1);
	close(pipex.tube[0]);
	dup2(pipex.infile, 0);
	if (pipex.cmd)
	{
		execve(pipex.cmd, pipex.cmd_args, envp);
		free(pipex.cmd);
	}
	ft_free_tab(pipex.cmd_args);
}

void	ft_cmd2(t_pipex pipex, char *arg, char *envp[])
{
	pipex.cmd_args = ft_split(arg, ' ');
	pipex.cmd = ft_get_cmd_path(pipex.cmd_paths, pipex.cmd_args[0]);
	dup2(pipex.tube[0], 0);
	close(pipex.tube[1]);
	dup2(pipex.outfile, 1);
	if (pipex.cmd)
	{
		execve(pipex.cmd, pipex.cmd_args, envp);
		free(pipex.cmd);
	}
	ft_free_tab(pipex.cmd_args);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc != 5)
		return (1);
	pipex.infile = open(argv[1], O_RDONLY);
	if (pipex.infile < 0)
		ft_err_exit("pas de file 1");
	pipex.outfile = open(argv[4], O_TRUNC | O_RDWR);
	if (pipex.outfile < 0)
		ft_err_exit("pas de file 2");
	if (pipe(pipex.tube) < 0)
		ft_err_exit("pipex ne pipex pas");
	pipex.paths = ft_find_path(envp);
	pipex.cmd_paths = ft_split(pipex.paths, ':');
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		ft_cmd1(pipex, argv[2], envp);
	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
		ft_cmd2(pipex, argv[3], envp);
	close(pipex.tube[0]);
	close(pipex.tube[1]);
	ft_free_tab(pipex.cmd_paths);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	return (0);
}
