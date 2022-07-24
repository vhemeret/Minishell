/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 17:44:08 by vahemere          #+#    #+#             */
/*   Updated: 2022/07/23 17:47:22 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	**malloc_and_put_lst(t_env *lst, int i, t_env *tmp)
{
	char	**rendu;

	rendu = ft_malloc(sizeof(char *) * (i + 1));
	if (!rendu)
		return (NULL);
	i = -1;
	tmp = lst;
	while (tmp)
	{
		if (tmp->content)
			rendu[++i] = ft_strcpy(tmp->content);
		tmp = tmp->next;
	}
	rendu[++i] = NULL;
	return (rendu);
}

char	**lst_to_char(t_env *lst)
{
	int		i;
	t_env	*tmp;

	i = 0;
	if (!lst || !lst->content)
		return (NULL);
	tmp = lst;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (malloc_and_put_lst(lst, i, tmp));
}
