/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_built_in.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 01:50:59 by brhajji-          #+#    #+#             */
/*   Updated: 2022/07/19 04:28:00 by brhajji-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	init_env(t_exec *utils, char **envp)
{
	t_env	*tmp;
	t_env	*tmp2;
	char	*temp;
	
	if (!(*envp))
	{
		printf("test\n");
		tmp = malloc(sizeof(t_env));
		temp = malloc(sizeof(char ) * 1024);
		tmp->content = getcwd(temp, sizeof(temp));
		tmp->next = NULL;
		tmp2 = malloc(sizeof(t_env));
		tmp2->content = "SHLVL=1";
		tmp2->next = tmp;
		utils->envp_lst = tmp2;
		utils->envp = lst_to_char(utils->envp_lst);
	}
	else if (utils && envp)
	{
		utils->envp_lst = init_lst_env(envp, utils);
		printf("3%s\n", utils->envp_lst->content);
		utils->envp = lst_to_char(utils->envp_lst);
	}
	return (0);
}

int	is_built_in(t_token *token)
{
	if (!ft_strcmp(token->word, "pwd") 
		|| !ft_strcmp(token->word, "env") || !ft_strcmp(token->word, "echo"))
		return (0);
	else if (!ft_strcmp(token->word, "cd") || !ft_strcmp(token->word, "export") || !ft_strcmp(token->word, "unset")
		|| !ft_strcmp(token->word, "exit"))
		return (1);
	else 
		return (-1);
}

void	no_fork(t_token *token, t_exec *utils)
{
	if (!strcmp(token->word, "cd"))
	{
		if (get_nb_arg(token) == 2)
			cd(token->next->word, utils);
		else if (get_nb_arg(token) == 1)
			cd(NULL, utils);
		else
			write(2, "cd: too many arguments", 23);
	}
	else if (!strcmp(token->word, "export"))
	{
		if (!token->next)
			export(NULL, &utils);
		else
			while (token->next && token->next->type == ARG)
			{
				export(ft_strcpy(token->next->word), &utils);
				token = token->next;
			}
	}
	else if (!ft_strcmp(token->word, "unset"))
	{
		while (token->next && token->next->type == ARG)
		{
			unset(token->next->word, utils);
			token = token->next;
		}
	}
	else if (!ft_strcmp(token->word, "exit"))
		ft_exit(utils);
}

int	manage_built_in(t_token *token, t_exec *utils)
{
	if (!ft_strcmp(token->word, "pwd"))
	{
		pwd(utils->envp);
		return (0);	
	}
	else if (!ft_strcmp(token->word, "env"))
	{
		env(utils);
		return (0);
	}
	else if (!ft_strcmp(token->word, "echo"))
	{
		echo(token);
		return (0);
	}
	return (1);
}