/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 15:34:49 by brhajji-          #+#    #+#             */
/*   Updated: 2022/07/19 01:36:53 by brhajji-         ###   ########.fr       */
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
	int	i;

	i = -1;
	while (++i <= size)
		free(envp[size]);
	free(envp);
	envp = NULL;
}

int	size_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
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
		print_tab(sort_tab((*utils)->envp, size_tab((*utils)->envp)));
		free(tmp);
		return (0);
	}
	else if (!check_parsing(var))
	{
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
				if (*(var + pos_equal(var)) == '=')
					(*utils)->envp_lst = edit_var_lst(*utils, var, 0);
				else
					(*utils)->envp_lst = edit_var_lst(*utils, var, 1);
				free_env((*utils)->envp, size_tab((*utils)->envp));
				(*utils)->envp = lst_to_char((*utils)->envp_lst);
				return (0);
			}
		}
		//printf("test 1 = %s\n",(*utils)->envp_lst->content);
		//printf("test 2 = %s\n",(*utils)->envp_lst->content);
		free_env((*utils)->envp, size_tab((*utils)->envp));
		(*utils)->envp_lst = ft_envadd_back(((*utils)->envp_lst), tmp);
		(*utils)->envp = lst_to_char((*utils)->envp_lst);
	}
	return (0);
}