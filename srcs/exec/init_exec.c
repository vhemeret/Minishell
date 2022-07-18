/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 10:58:02 by brhajji-          #+#    #+#             */
/*   Updated: 2022/07/18 04:08:46 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	nb_node(t_token *token)
{
	int	x;

	x = 0;
	while (token)
	{
		if (token->type == PIPE || !token->next)
			x++;
		token = token->next;
	}
	//printf("nb node = %i\n", x);
	return (x);
}

t_node	*ft_lstadd_back(t_node *lst, t_node *new)
{
	t_node	*alst;
	
	alst = lst;
	if (!alst)
		return (new);
	else
	{
		while ((alst)->next)
			alst = (alst)->next;
		(alst)->next = new;
	}
	return (lst);
}

t_token *go_next(t_token *token)
{
	while (token && token->type != PIPE)
		token = token->next;
	if (token && token->type == PIPE)
		token = token->next;
	return (token);
}

t_exec	*init_exec(t_token *token, char **envp)
{
	t_node	*node;
	int		i;
	t_exec *utils;
	
	utils = malloc(sizeof(t_exec ));
	utils->node = NULL;
	utils->nb_cmd = nb_cmd(token);
	utils->nb_node = nb_node(token);
	utils->envp_lst = NULL;
	//utils->envp = envp;
	utils->token_tmp = token;
	node = NULL;
	i = -1;
	while (++i < utils->nb_node)
	{
		node = malloc(sizeof(t_node ));
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
		//printf("num ava = %i\n", (*utils)->node->num);
	}
	utils->node_tmp = utils->node;
	if (!envp || !utils->envp_lst)
		init_env(utils, envp);
	return (utils);
}

void	refresh(t_token *token, t_exec *utils)
{
	t_node	*node;
	int		i;
	
	utils->node = NULL;
	utils->nb_cmd = nb_cmd(token);
	utils->nb_node = nb_node(token);
	//utils->envp_lst = NULL;
	utils->token_tmp = token;
	node = NULL;
	i = -1;
	while (++i < utils->nb_node)
	{
		node = malloc(sizeof(t_node ));
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
		//printf("num ava = %i\n", (*utils)->node->num);
	}
	token = utils->token_tmp;
	utils->node_tmp = utils->node;
}
