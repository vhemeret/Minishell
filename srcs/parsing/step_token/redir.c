/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 04:18:54 by vahemere          #+#    #+#             */
/*   Updated: 2022/07/01 04:19:32 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	is_limitor(t_token *save)
{
	int	i;

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
	int	i;

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
	int	i;

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
	int	i;

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
