/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 15:34:49 by brhajji-          #+#    #+#             */
/*   Updated: 2022/07/23 17:59:11 by vahemere         ###   ########.fr       */
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

void	free_env(char **envp, int size)
{
	int	i;

	i = -1;
	while (++i <= size)
		ft_free(envp[size]);
	ft_free(envp);
	envp = NULL;
}

int	size_tab(char **tab)
{
	int	i;

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

	tmp = ft_malloc(sizeof(t_env));
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
		ft_free(tmp);
		return (0);
	}
	else if (!check_parsing(var))
		return (export_run(var, utils, tmp, i));
	return (0);
}
