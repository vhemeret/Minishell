/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:23:06 by vahemere          #+#    #+#             */
/*   Updated: 2022/04/17 22:56:19 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	get_cmd(char *cmd_line, t_cmd **cmd)
{
	int i;
	int	len;

	i = -1;
	len = 0;
	while (cmd_line[++i] && cmd_line[i] != '|')
		len++;
	(*cmd)->cmd = malloc(sizeof(char) * (len + 1));
	if (!(*cmd)->cmd)
		return ;
	i = -1;
	while (cmd_line[++i] && cmd_line[i] != '|')
		(*cmd)->cmd[i] = cmd_line[i];
	(*cmd)->cmd[i] = '\0';
}

static int	index_until_next_pipe(char *cmd_line, int j)
{
	while (cmd_line[j] && cmd_line[j] != '|')
		j++;
	if (cmd_line[j] == '|' && cmd_line[j + 1])
		j++;
	return (j);
}

static void	create_node_cmd(char *cmd_line, t_cmd **cmd, int nb_pipe)
{
	int		i;
	int		j;
	t_cmd	*tmp;

	i = -1;
	j = 0;
	tmp = *cmd;
	get_cmd(cmd_line, &tmp);
	while (++i < nb_pipe)
	{
		tmp->next = malloc(sizeof(t_cmd));
		if (!tmp->next)
			return ;
		tmp = tmp->next;
		j = index_until_next_pipe(cmd_line, j);
		get_cmd(&cmd_line[j], &tmp);
	}
	tmp->next = NULL;
}

void	manage_cmd(char *cmd_line, t_cmd **cmd)
{
	int		nb_pipe;
	
	nb_pipe = check_pipe(cmd_line);
	*cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return ;
	if (nb_pipe == 0)
	{
		(*cmd)->next = NULL;
		(*cmd)->cmd = ft_strdup(cmd_line);
		return ;
		//suite
	}
	else
	{
		create_node_cmd(cmd_line, cmd, nb_pipe);
		return ;
		//suite
	}
}
