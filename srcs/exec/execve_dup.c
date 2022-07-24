/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_dup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 00:58:56 by brhajji-          #+#    #+#             */
/*   Updated: 2022/07/24 00:58:56 by brhajji-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_r_in(t_exec utils, int num)
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
}

void	handle_r_out(t_exec utils, int *fd, int num)
{
	if (utils.node->out >= 0)
	{
		dup2(utils.node->out, STDOUT_FILENO);
		if (utils.node->in > 0)
			close(utils.node->in);
	}
	else if (num != utils.nb_cmd - 1 && fd[1] > 0)
		dup2(fd[1], STDOUT_FILENO);
	if (utils.nb_cmd > 1 && fd[1] > 0)
		close(fd[1]);
	if (fd[0] > 0)
		close(fd[0]);
}

int	check_path_exec(char *word, t_exec utils)
{
	if (!get_cmd_path(word, utils.envp))
	{
		write(2, word, ft_strlen(word));
		write(2, " : command not found\n", 21);
		return (1);
	}
	else
		return (0);
}

int	run_built_on_fork(t_token *tk, t_exec *utils)
{
	if (is_built_in(tk) == 1)
	{
		manage_built_in(tk, utils);
		ft_free_all();
		exit(0);
	}
	return (0);
}

int	launch_all(int *fd, int *x, pid_t *pid, t_token *token)
{
	while (g_all.utils->node)
	{
		if (g_all.utils->node && g_all.utils->node->has_cmd == 1 && ++x[1] >= 0)
		{
			while (token && token->type != CMD)
				token = token->next;
			g_all.utils->previous_fd = fd[0];
			if (g_all.utils->nb_cmd > 1 && pipe(fd) < 0)
				return (-1);
			if (g_all.utils->node->in != -2)
			{
				if (is_built_in(token) == 1 && g_all.utils->nb_cmd == 1)
					manage_built_in(token, g_all.utils);
				else
					pid[x[0]++] = run(token, fd, x[1], *(g_all.utils));
			}
		}
		g_all.utils->node = g_all.utils->node->next;
		token = go_next(token);
		if (g_all.utils->nb_cmd > 1 && fd[1] > 0)
			close(fd[1]);
		if (g_all.utils->previous_fd > 0)
			close(g_all.utils->previous_fd);
	}
	return (x[0]);
}
