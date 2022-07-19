/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 02:28:43 by brhajji-          #+#    #+#             */
/*   Updated: 2022/07/19 04:25:51 by brhajji-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**lst_to_char_env(t_env *lst)
{
	int		i;
	t_env	*tmp;
	char	**rendu;

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
	rendu = malloc(sizeof(char *) * (i + 1));
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

t_env	*edit_var_lst(t_exec *utils, char *var, int	join)
{
	t_env	*tmp;
	char	*char_tmp;

	tmp = utils->envp_lst;
	while (tmp && var)
	{
		if (!strncmp(tmp->content, var, pos_equal(var)))
		{
			if (!join)
			{
				free(tmp->content);
				tmp->content = var;
			}
			else if (join == 1)
			{
				char_tmp = plus_egale(tmp->content, var, pos_equal(var));
				free(tmp->content);
				free(var);
				tmp->content= char_tmp;
			}
			tmp->type = 3;
			return (utils->envp_lst);
		}
		tmp = tmp->next;
	}
	return (utils->envp_lst);
}