/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 18:21:11 by maemaldo          #+#    #+#             */
/*   Updated: 2024/05/01 20:40:01 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_close_all(t_pipex *pipex)
{
	// ⚠️ protege le dernier close fdp
	if (close(pipex->tube[0]) == -1)
		printf("close err1");
	if (close(pipex->tube[1]) == -1)
		printf("close err1");
	if (close(pipex->infile) == -1)
		printf("close err infile");
	close(pipex->outfile);
	return (1);
}

int	ft_cmd1(t_pipex pipex, char *arg, char *envp[])
{
	// ⚠️ doit proteger les close()
	if (dup2(pipex.tube[1], 1) == -1)
		return (ft_close_all(&pipex));
	close(pipex.tube[0]);
	close(pipex.tube[1]);
	if (dup2(pipex.infile, 0) == -1)
		return (ft_close_all(&pipex));
	close(pipex.infile);
	close(pipex.outfile);
	pipex.cmd_args = ft_split(arg, ' ');
	if (pipex.cmd_args)
	{
		pipex.cmd = ft_get_cmd_path(pipex.cmd_paths, pipex.cmd_args[0]);
		if (pipex.cmd)
		{
			execve(pipex.cmd, pipex.cmd_args, envp);
			free(pipex.cmd);
		}
		ft_free_tab(pipex.cmd_args);
	}
	return (1);
}

int	ft_cmd2(t_pipex pipex, char *arg, char *envp[])
{
	// ⚠️ doit proteger les close()
	if (dup2(pipex.tube[0], 0) == -1)
		return (ft_close_all(&pipex));
	close(pipex.tube[1]);
	close(pipex.tube[0]);
	if (dup2(pipex.outfile, 1) == -1)
		return (ft_close_all(&pipex));
	close(pipex.infile);
	close(pipex.outfile);
	pipex.cmd_args = ft_split(arg, ' ');
	if (pipex.cmd_args)
	{
		pipex.cmd = ft_get_cmd_path(pipex.cmd_paths, pipex.cmd_args[0]);
		if (pipex.cmd)
		{
			execve(pipex.cmd, pipex.cmd_args, envp);
			free(pipex.cmd);
		}
		ft_free_tab(pipex.cmd_args);
	}
	return (1);
}

void	ft_open_files(char **argv, t_pipex *pipex)
{
	// ⚠️ doit verifier qu'il a le droit d'acceder aux fichiers!!!
	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile < 0)
		ft_err_exit("infile ne infile pas");
	pipex->outfile = open(argv[4], O_CREAT | O_TRUNC | O_RDWR, 0666);
	if (pipex->outfile < 0)
		ft_err_exit("outfile ne outfile pas");
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	// ⚠️ ameliorer les erreurs
	if (argc != 5)
		return (1);
	ft_open_files(argv, &pipex);
	if (pipe(pipex.tube) < 0)
		ft_err_exit("pipex ne pipex pas");
	pipex.paths = ft_find_path(envp);
	pipex.cmd_paths = ft_split(pipex.paths, ':');
	pipex.pid1 = fork();
	if (pipex.pid1 == -1)
		return (0);
	if (pipex.pid1 == 0)
		ft_cmd1(pipex, argv[2], envp);
	else
		ft_cmd2(pipex, argv[3], envp);
	ft_free_tab(pipex.cmd_paths);
	waitpid(pipex.pid1, NULL, 0);
	return (0);
}
