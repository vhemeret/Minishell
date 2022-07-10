/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 15:09:32 by brhajji-          #+#    #+#             */
/*   Updated: 2022/06/26 14:19:49 by brhajji-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**lst_to_char(t_env *lst)
{
	int 	i;
	t_env	*tmp;
	char	**rendu;
	
	i = 0;
	tmp = lst;
	while (tmp)
	{
		i++;
		tmp = tmp->next;	
	}
	rendu = malloc(sizeof(char *) * (i + 1));
	if (!rendu)
		return (NULL);
	i = -1;
	while(lst)
	{
		rendu[++i] = lst->content;
		lst = lst->next;
	}
	rendu[++i] = NULL;
	return (rendu);
}

int	env_size(char **envp)
{
	int	i;
	
	i = 0;
	while (envp[i])
		i++;
	return (i);
}

t_env	*ft_lstadd_back_env(t_env *lst, t_env *new)
{
	t_env	*alst;
	
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

t_env	*init_lst_env(char **envp)
{
	t_env	*rendu;
	t_env	*tmp;
	int		size;
	int		i;

	i = -1;
	size = env_size(envp);
	rendu = NULL;
	while (++i < size)
	{
		tmp = malloc(sizeof(t_env));
		tmp->content = envp[i];
		tmp->next = NULL;
		rendu = ft_lstadd_back_env(rendu, tmp);
	}
	return (rendu);
}

int	env(char **envp)
{
	if (!envp)
		return (-1);
	while (*envp)
	{
		printf("%s\n", *envp);
		envp++;
	}
	return (0);
}
