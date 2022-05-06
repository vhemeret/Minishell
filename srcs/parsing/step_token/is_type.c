/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_type.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 03:37:05 by vahemere          #+#    #+#             */
/*   Updated: 2022/05/06 05:04:03 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	is_limitor(t_token *save)
{
	int i;

	i = -1;
	while (save->word[++i])
		if (save->word[i] != '<')
			return (0);
	if (i != 2)
		return (0);
	else
		return (1);
	return (0);
}

int	is_outfile_drout(t_token *save)
{
	int i;

	i = -1;
	while (save->word[++i])
		if (save->word[i] != '>')
			return (0);
	if (i != 2)
		return (0);
	else
		return (1);
	return (0);
}

int	is_drin(t_token *tmp)
{
	int i;

	i = -1;
	while (tmp->word[++i])
		if (tmp->word[i] != '<')
			return (0);
	if (i != 2)
		return (0);
	else
		return (1);
	return (0);
}

int	is_drout(t_token *tmp)
{
	int i;

	i = -1;
	while (tmp->word[++i])
		if (tmp->word[i] != '>')
			return (0);
	if (i != 2)
		return (0);
	else
		return (1);
	return (0);
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