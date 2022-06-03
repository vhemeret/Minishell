/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:22:13 by vahemere          #+#    #+#             */
/*   Updated: 2022/05/18 10:36:00 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_double_array(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
	{
		free(arr[i]);
		arr[i] = NULL;
	}
	free(arr);
	arr = NULL;
}

int	print_and_free(char *str, t_token **lst)
{
	t_token	*tmp;
	
	if (str)
		dprintf(2, "%s\n", str);
	while (tmp)
	{
		tmp = (*lst);
		(*lst) = (*lst)->next;
		free(tmp->word);
		free(tmp);
		tmp = NULL;
	}
	return (0);
}