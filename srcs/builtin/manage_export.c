/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 02:28:43 by brhajji-          #+#    #+#             */
/*   Updated: 2022/07/23 19:39:23 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**malloc_and_put_lst(t_env *lst, int i)
{
	t_env	*tmp;
	char	**rendu;

	rendu = ft_malloc(sizeof(char *) * (i + 1));
	if (!rendu)
		return (NULL);
	i = -1;
	tmp = lst;
	while (tmp)
	{
		if (tmp->type != 3)
			rendu[++i] = tmp->content;
		tmp = tmp->next;
	}
	rendu[++i] = NULL;
	return (rendu);
}

char	**lst_to_char_env(t_env *lst)
{
	int		i;
	t_env	*tmp;

	i = 0;
	if (!lst || !lst->content)
		return (NULL);
	tmp = lst;
	while (tmp)
	{
		if (tmp->type != 3)
			i++;
		tmp = tmp->next;
	}
	return (malloc_and_put_lst(lst, i));
}

int	pos_equal(char *str)
{
	int	x;

	x = 0;
	while (str[x] && str[x] != '=' && str[x] != '+')
	{
		if (str[x] == ' ')
			return (-1);
		x++;
	}
	if (str[x] != '=' && str[x] != '+')
		return (-1);
	return (x);
}

t_env	*edit_var_lst_run(t_env *tmp, char *var, int join, char *char_tmp)
{
	while (tmp && var)
	{
		if (!strncmp(tmp->content, var, pos_equal(var)))
		{
			if (!join)
			{
				ft_free(tmp->content);
				tmp->content = var;
			}
			else if (join == 1)
			{
				char_tmp = plus_egale(tmp->content, var, pos_equal(var));
				ft_free(tmp->content);
				ft_free(var);
				tmp->content = char_tmp;
			}
			tmp->type = 3;
			return (g_all.utils->envp_lst);
		}
		tmp = tmp->next;
	}
	return (g_all.utils->envp_lst);
}

t_env	*edit_var_lst(t_exec *utils, char *var, int join)
{
	t_env	*tmp;
	char	*char_tmp;

	char_tmp = NULL;
	tmp = utils->envp_lst;
	return (edit_var_lst_run(tmp, var, join, char_tmp));
}
