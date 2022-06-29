/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_built_in.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 01:50:59 by brhajji-          #+#    #+#             */
/*   Updated: 2022/06/27 14:34:47 by brhajji-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	init_env(t_exec *utils)
{
	t_env	*tmp;
	t_env	*rendu;
	char	*temp;
	
	tmp = malloc(sizeof(t_env));
	temp = malloc(sizeof(char ) * 1024);
	rendu = NULL;
	tmp->content = getcwd(temp, sizeof(temp));
	tmp->next = NULL;
	ft_lstadd_back_env(rendu, tmp);
	tmp = malloc(sizeof(t_env));
	tmp->content = "SHLVL=1";
	tmp->next = NULL;
	ft_lstadd_back_env(rendu, tmp);
	utils->envp_lst = rendu;
	utils->envp = lst_to_char(utils->envp_lst);
	return (0);
}

int	is_built_in(t_token *token)
{
	if (!ft_strcmp(token->word, "cd") || !ft_strcmp(token->word, "export") || !ft_strcmp(token->word, "unset") 
		|| !ft_strcmp(token->word, "pwd") || !ft_strcmp(token->word, "env") || !ft_strcmp(token->word, "echo"))
		return (0);
	else 
		return (-1);
}

int	manage_built_in(t_token *token, t_exec *utils)
{
	if (!ft_strcmp(token->word, "pwd"))
	{
		pwd(utils->envp);
		return (0);	
	}
	else if (!ft_strcmp(token->word, "export"))
	{
		if (token->next)
			export(token->next->word, utils);
		else
			export(NULL, utils);
		return (0);
	}
	else if (!ft_strcmp(token->word, "unset"))
	{
		unset(token->next->word, utils);
		return (0);
	}
	else if (!ft_strcmp(token->word, "env"))
	{
		env(utils->envp);
		return (0);
	}
	return (1);
}