/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:46:20 by brhajji-          #+#    #+#             */
/*   Updated: 2022/07/23 19:40:09 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_cmd_path(char *cmd, char **envp)
{
	int		i;
	char	*tmp;
	char	**path;

	i = -1;
	if (!access(cmd, X_OK))
		return (cmd);
	else if (access(cmd, X_OK) && *cmd == '/')
		return (NULL);
	path = get_path(envp);
	while (path && path[++i])
	{
		tmp = ft_strjoin(path[i], "/");
		tmp = ft_strjoin(tmp, cmd);
		if (!access(tmp, F_OK))
			return (tmp);
		ft_free(tmp);
	}
	return (NULL);
}

pid_t	run(t_token *tk, int *fd, int num, t_exec utils)
{
	pid_t	pid;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (0);
	}
	if (pid == 0)
	{
		handle_r_in(utils, num);
		handle_r_out(utils, fd, num);
		if (!run_built_on_fork(tk, &utils) && !check_path_exec(tk->word, utils))
			if (execve(get_cmd_path(tk->word, utils.envp),
					get_arg(tk), utils.envp) == -1)
				perror(tk->word);
		ft_free_all();
		exit(127);
	}
	return (pid);
}

int	nb_cmd(t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		if (token->type == CMD)
			i++;
		token = token->next;
	}
	return (i);
}

void	exec(t_token *token)
{
	int		status;
	pid_t	*pid;
	int		x[2];
	int		fd[2];

	x[0] = 0;
	x[1] = -1;
	fd[0] = 0;
	pid = ft_malloc(sizeof(pid_t) * (g_all.utils->nb_cmd + 1));
	x[0] = launch_all(fd, x, pid, token);
	if (x[0] == -1)
		perror("Pipe ");
	while (--x[0] >= 0)
	{
		waitpid(pid[x[0]], &status, 0);
		if (WIFEXITED(status))
			g_all.utils->err = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			g_all.utils->err = WTERMSIG(status);
	}
	ft_free(pid);
}
