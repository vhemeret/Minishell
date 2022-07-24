/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_run.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 17:53:58 by vahemere          #+#    #+#             */
/*   Updated: 2022/07/23 17:58:49 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	export_run(char *var, t_exec **utils, t_env *tmp, int i)
{
	tmp->content = ft_strcpy(var);
	if (pos_equal(tmp->content) == -1)
		tmp->type = 1;
	else
		tmp->type = 2;
	tmp->next = NULL;
	while ((*utils)->envp[++i] && tmp->type == 2)
	{
		if (!strncmp((*utils)->envp[i], var, pos_equal(var)))
		{
			if (*(var + pos_equal(var)) == '=')
				(*utils)->envp_lst = edit_var_lst(*utils, var, 0);
			else
				(*utils)->envp_lst = edit_var_lst(*utils, var, 1);
			free_env((*utils)->envp, size_tab((*utils)->envp));
			(*utils)->envp = lst_to_char((*utils)->envp_lst);
			return (0);
		}
	}
	free_env((*utils)->envp, size_tab((*utils)->envp));
	(*utils)->envp_lst = ft_envadd_back(((*utils)->envp_lst), tmp);
	(*utils)->envp = lst_to_char((*utils)->envp_lst);
	return (0);
}
