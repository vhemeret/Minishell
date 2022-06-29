/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 15:34:49 by brhajji-          #+#    #+#             */
/*   Updated: 2022/06/27 14:35:55 by brhajji-         ###   ########.fr       */
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
	while (i < size)
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
	while (--size >= 0)
		free(envp[size]);
	free(envp);
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

int	export(char *var, t_exec *utils)
{
	int		i;
	int		size;
	t_env	tmp;
	
	size = ft_strlen(var);
	//var = ft_strcpy
	i = -1;
	if (!utils->envp_lst)
	{
		utils->envp_lst = init_lst_env(utils->envp);
		utils->envp = lst_to_char(utils->envp_lst);
	}
	if (!var)
	{
		print_tab(sort_tab(utils->envp, size_tab(utils)));
	}
	while (utils->envp[++i])
	{
		if (!strncmp(utils->envp[i], var, size))
		{
			free(utils->envp[i]);
			utils->envp[i] = var;
			return 0;
		}
	}
	tmp.content = var;
	tmp.content = NULL;
	ft_lstadd_back_env(utils->envp_lst, &tmp);
	free_env(utils->envp, i);
	utils->envp = lst_to_char(utils->envp_lst);
	return (0);
}