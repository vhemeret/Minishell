/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_type.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 03:37:05 by vahemere          #+#    #+#             */
/*   Updated: 2022/07/01 04:29:48 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static int	is_type2(t_token *tmp)
{
	if (tmp->word[0] == '>' && tmp->word[1] == '\0')
		return (3);
	else if (tmp->word[0] == '<' && tmp->word[1] == '\0')
		return (2);
	else
	{
		if (is_drout(tmp))
			return (4);
		else if (is_drin(tmp))
			return (5);
	}
	return (-1);
}

int	is_type(t_token *tmp)
{
	int	i;

	i = -1;
	if (tmp->word[0] == '>')
		while (tmp->word[++i])
			if (tmp->word[i] != '>')
				return (-1);
	if (i > 2)
		return (-1);
	if (tmp->word[0] == '<')
		while (tmp->word[++i])
			if (tmp->word[i] != '<')
				return (-1);
	if (i > 2)
		return (-1);
	return (is_type2(tmp));
}
