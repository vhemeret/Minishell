/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 15:34:49 by brhajji-          #+#    #+#             */
/*   Updated: 2022/07/10 16:57:22 by brhajji-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**sort_tab(char **tab, int size)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	tmp = 0;
	while (i < size - 1)
	{
		j = i + 1;
		while (j < size)
		{
			if (tab[i][0] > tab[j][0])
			{
				tmp = tab[i];
				tab[i] = tab[j];
				tab[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (tab);
}

void	print_tab(char **tab)
{
	while (tab && *tab)
	{
		printf("declare -x %s\n", *tab);
		tab++;
	}
}

void free_env(char **envp, int size)
{
	while (--size && envp[size])
		free(envp[size]);
	free(envp);
	envp = NULL;
}

int	size_tab(t_exec *utils)
{
	int i;

	i = 0;
	while (utils->envp[i])
	{
		i++;
	}
	return (i);
}

int	export(char *var, t_exec **utils)
{
	int		i;
	t_env	*tmp;
	
	tmp = malloc(sizeof(t_env));
	if (!tmp)
		return (-1);
	if (var && *var == '$')
		return (-1);
	i = -1;
	if (!(*utils)->envp_lst)
	{
		(*utils)->envp_lst = init_lst_env((*utils)->envp, (*utils));
		(*utils)->envp = lst_to_char((*utils)->envp_lst);
	}
	if (!var)
	{
		print_tab(sort_tab((*utils)->envp, size_tab((*utils))));
		free(tmp);
		return (0);
	}
	tmp->content = ft_strcpy(var);
	if (pos_equal(tmp->content) == - 1)
		tmp->type = 1;
	else
		tmp->type = 2;
	tmp->next = NULL;
	while ((*utils)->envp[++i] && tmp->type == 2)
	{
		if (!strncmp((*utils)->envp[i], var, pos_equal(var)))
		{
			free((*utils)->envp[i]);
			(*utils)->envp_lst = edit_var_lst(*utils, var, 0);
			free_env((*utils)->envp, size_tab(*utils));
			(*utils)->envp = lst_to_char((*utils)->envp_lst);
			return (0);
		}
	}
	//printf("test 1 = %s\n",(*utils)->envp_lst->content);
	(*utils)->envp_lst = ft_envadd_back(((*utils)->envp_lst), tmp);
	//printf("test 2 = %s\n",(*utils)->envp_lst->content);
	if ((*utils)->envp_lst)
		free_env((*utils)->envp, size_tab(*utils));
	(*utils)->envp = lst_to_char((*utils)->envp_lst);
	return (0);
}