/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 10:58:02 by brhajji-          #+#    #+#             */
/*   Updated: 2022/07/23 15:44:23 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_exec	*init_exec(char **envp)
{
	t_exec	*utils1;

	utils1 = ft_malloc(sizeof(t_exec));
	if (!utils1)
		return (NULL);
	if (!utils1)
	{
		ft_free(utils1);
		return (NULL);
	}
	utils1->err = 0;
	utils1->node = NULL;
	utils1->envp_lst = NULL;
	utils1->on_here_doc = 0;
	utils1->can_run = 1;
	if (!envp || !utils1->envp_lst)
		init_env(utils1, envp);
	return (utils1);
}

void	refresh_all_node(t_token *token, t_exec *utils, t_node *node, int i)
{
	while (++i < utils->nb_node)
	{
		node = ft_malloc(sizeof(t_node));
		node->num = i;
		node->here_doc_fd = -1;
		node->here_doc = NULL;
		here_doc_init(node, token);
		set_r_in(node, token);
		set_r_out(node, token);
		node->next = NULL;
		node->has_cmd = 0;
		while (token && token->type != PIPE)
		{
			if (token->type == CMD)
				node->has_cmd = 1;
			token = token->next;
		}
		if (token)
			token = token->next;
		utils->node = ft_lstadd_back((utils->node), node);
	}
	token = utils->token_tmp;
	utils->node_tmp = utils->node;
}

void	refresh(t_token *token, t_exec *utils)
{
	t_node	*node;
	int		i;

	utils->node = NULL;
	utils->nb_cmd = nb_cmd(token);
	utils->nb_node = nb_node(token);
	utils->token_tmp = token;
	node = NULL;
	i = -1;
	refresh_all_node(token, utils, node, i);
}
