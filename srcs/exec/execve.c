/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:46:20 by brhajji-          #+#    #+#             */
/*   Updated: 2022/06/24 15:05:56 by brhajji-         ###   ########.fr       */
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
	if (!access(cmd, X_OK))
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
		perror("fork");
		return (0);
	}
	if (pid == 0)
	{
		if (utils.node->in >= 0)
		{
			dup2(utils.node->in, STDIN_FILENO);
			if (utils.node->in > 0)
				close(utils.node->in);
			if (utils.previous_fd > 0)
				close(utils.previous_fd);
			if (utils.node->in == utils.node->here_doc_fd)
				unlink(utils.node->here_doc);
		}
		else if (num)
		{
			dup2(utils.previous_fd, STDIN_FILENO);
			if (utils.previous_fd > 0)
				close(utils.previous_fd);
		}
		if (utils.node->out >= 0)
		{
			dup2(utils.node->out, STDOUT_FILENO);
			if (utils.node->in > 0)
				close(utils.node->in);	
		}
		else if (num != utils.nb_cmd - 1)
			dup2(fd[1], STDOUT_FILENO);
		if (utils.nb_cmd > 1 && fd[1] > 0)
			close(fd[1]);
		if (fd[0] > 0)
			close(fd[0]);
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
	pid_t 	*pid;
	int		i;
	int		num;
	int		fd[2];
	t_exec	*utils;

	i = -1;
	num = 0;
	utils = NULL;
	init_exec(token, &utils);
	utils->envp = envp;
	fd[0] = 0;
	pid = malloc(sizeof(pid_t) * (utils->nb_cmd + 1));
	while (++i < utils->nb_node)
	{
		//printf("has cmd = %i\n", utils->node->has_cmd);
		if (utils->node && utils->node->has_cmd == 1)
		{
			while (token && token->type != CMD)
				token = token->next;
			utils->previous_fd = fd[0];
			if (utils->nb_cmd > 1)
				if (pipe(fd) < 0)
					return (perror("Pipe "));
			//printf("fd in = %i\n", utils->node->in);
			if (utils->node->in != -2)
				pid[i] = run(token, fd, num, *utils);
			num++;
		}
		utils->node = utils->node->next;
		token = go_next(token);
		if (utils->nb_cmd > 1 && fd[1] > 0)
			close(fd[1]);
		if (utils->previous_fd > 0)
			close(utils->previous_fd);
	}
	while (--i >= 0)
		waitpid(pid[i], &status, 0);
	ft_free_token(utils->token_tmp);
	ft_free_node(utils->node_tmp);
}