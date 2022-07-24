/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 15:09:32 by brhajji-          #+#    #+#             */
/*   Updated: 2022/07/23 17:44:47 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	env_size(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return (0);
	while (envp[i])
		i++;
	return (i);
}

t_env	*ft_envadd_back(t_env *lst, t_env *new)
{
	t_env	*alst;

	alst = lst;
	if (!alst)
		alst = new;
	else
	{
		while ((alst)->next)
			alst = (alst)->next;
		(alst)->next = new;
	}
	return (lst);
}

t_env	*ft_new_env(char *content)
{
	t_env	*new;

	new = ft_malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->type = 0;
	new->content = content;
	return (new);
}

t_env	*init_lst_env(char **envp, t_exec *utils)
{
	t_env	*rendu;
	t_env	*tmp;
	int		size;
	int		i;

	i = -1;
	size = env_size(envp);
	rendu = NULL;
	(void)utils;
	while (++i < size)
	{
		tmp = ft_new_env(ft_strcpy(envp[i]));
		if (!rendu)
			rendu = tmp;
		else
			rendu = ft_envadd_back(rendu, tmp);
	}
	return (rendu);
}

int	env(t_exec *utils)
{
	t_env	*tmp;

	tmp = utils->envp_lst;
	if (!tmp)
		return (-1);
	while (tmp && tmp->content)
	{
		if (tmp->content && *(tmp->content) && tmp->type != 1)
			printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
	utils->err = 0;
	return (0);
}
