/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 15:34:45 by brhajji-          #+#    #+#             */
/*   Updated: 2022/06/27 01:53:44 by brhajji-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	unset(char *var, t_exec *utils)
{
	int		size;
	t_env	*tmp;
	t_env	*tmp_lst;
	
	size = ft_strlen(var);
	//var = ft_strcpy
	if (!utils->envp_lst)
	{
		utils->envp_lst = init_lst_env(utils->envp);
		utils->envp = lst_to_char(utils->envp_lst);
	}
	tmp_lst = utils->envp_lst;
	while (tmp_lst)
	{
		if (tmp_lst->next && !strncmp(tmp_lst->next->content, var, size))
		{
			tmp = tmp_lst->next->next;
			free(tmp_lst->next);
			tmp_lst->next = tmp;
			return (0);
		}
		tmp_lst = tmp_lst->next;
	}
	utils->envp = lst_to_char(utils->envp_lst);
	return (0);
}