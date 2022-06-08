/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:46:20 by brhajji-          #+#    #+#             */
/*   Updated: 2022/06/08 18:00:25 by brhajji-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_cmd_path(char *cmd, char **envp)
{
	int		i;
	char	*tmp;
	char 	**path;

	i = -1;
	path = get_path(envp);
	if (!access(cmd, F_OK))
		return (cmd);
	while (path[++i])
	{
		tmp = ft_strjoin(path[i], "/");
		tmp = ft_strjoin(tmp, cmd);
		if (access(tmp, F_OK) == 0)
			return (tmp);
		free(tmp);
	}
	return (NULL);
}

pid_t	run(t_token *token, int *fd, int num, t_exec utils)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("Fork ");
		return (0);
	}
	if (pid == 0)
	{
		if (num == 0)
		{
			if (utils.in >= 0)
			{
				dup2(utils.in, STDIN_FILENO);
				close(utils.in);	
			}
			if (utils.out >= 0)
			{
				dup2(utils.out, STDOUT_FILENO);
				close(utils.in);	
			}
			else
				dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
		}
		else
		{
			if (utils.in >= 0)
			{
				dup2(utils.in, STDIN_FILENO);
				close(utils.in);	
			}
			else
			{
				dup2(utils.previous_fd, STDIN_FILENO);
			}
			if (utils.out >= 0)
			{
				dup2(utils.out, STDOUT_FILENO);
				close(utils.in);	
			}
			else if (num != utils.nb_cmd - 1)
				dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
		}
		if (execve(get_cmd_path(token->word, utils.envp), get_arg(token), utils.envp) == -1)
			perror("Execve ");
	}
	return (pid);
}

int		nb_cmd(t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		if (token->type == 0)
			i++;
		token = token->next;
	}
	return (i);
}

void	exec(t_token *token, char **envp)
{
	int		status;
	pid_t *pid;
	int		i;
	int		fd[2];
	t_exec	utils;

	i = -1;
	utils.nb_cmd = nb_cmd(token);
	utils.envp = envp;
	utils.in = -2;
	utils.out = -2;
	fd[0] = 0;
	pid = malloc(sizeof(pid_t) * (utils.nb_cmd + 1));
	while (++i < utils.nb_cmd)
	{
		set_r_in(&utils, token);
		while (token->type != CMD)
			token = token->next;
		set_r_out(&utils, token);
		utils.previous_fd = fd[0];
		if (utils.nb_cmd > 1)
			if (pipe(fd) < 0)
				return (perror("Pipe "));
		pid[i] = run(token, fd, i, utils);
		while (token && token->type != PIPE)
			token = token->next;
		if (token && token->type == PIPE)
			token = token->next;
		close(fd[1]);
		if (utils.previous_fd)
			close(utils.previous_fd);
	}
	while (--i >= 0)
		waitpid(pid[i], &status, 0);
}