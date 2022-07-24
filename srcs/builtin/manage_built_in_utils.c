/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_built_in_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 16:29:05 by vahemere          #+#    #+#             */
/*   Updated: 2022/07/23 19:39:03 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	manage_built_in1(t_token *token)
{
	if (!ft_strcmp(token->word, "pwd"))
	{
		pwd(g_all.utils->envp);
		return (1);
	}
	else if (!ft_strcmp(token->word, "env"))
	{
		env(g_all.utils);
		return (1);
	}
	else if (!ft_strcmp(token->word, "echo"))
	{
		echo(token);
		return (1);
	}
	return (0);
}

int	manage_built_in2(t_token *token)
{
	if (!ft_strcmp(token->word, "cd"))
	{
		if (get_nb_arg(token) == 2)
			cd(token->next->word, g_all.utils);
		else if (get_nb_arg(token) == 1)
			cd(NULL, g_all.utils);
		else
		{
			write(2, "cd: too many arguments", 23);
			g_all.utils->err = 1;
		}
		return (1);
	}
	return (0);
}

int	manage_built_in3(t_token *token, t_exec *utils)
{
	if (!ft_strcmp(token->word, "export"))
	{
		if (!token->next || is_last(token))
			export(NULL, &utils);
		else
		{
			while (token->next && token->next->type == ARG)
			{
				export(ft_strcpy(token->next->word), &utils);
				token = token->next;
			}
		}
		return (1);
	}
	return (0);
}

int	manage_built_in4(t_token *token)
{
	if (!ft_strcmp(token->word, "unset"))
	{
		while (token->next && token->next->type == ARG)
		{
			unset(token->next->word, g_all.utils);
			token = token->next;
		}
		return (1);
	}
	return (0);
}
