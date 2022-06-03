/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:04:55 by brhajji-          #+#    #+#             */
/*   Updated: 2022/05/09 16:13:10 by brhajji-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


int		get_nb_arg(t_token *token)
{
	int	i;

	i = 0;
	while (token->next && token->next->type == 1)
	{
		i++;
		token = token->next;
	}
	return (i);
}

char	**get_arg(t_token *token)
{
	char	**arg;
	int		nb_arg;
	int		i;

	i = 0;
	nb_arg = get_nb_arg(token);
	arg = malloc(sizeof(char *) * (nb_arg + 1));
	*arg = token->word;
	token = token->next;
	while (++i < nb_arg && token)
	{
		arg[i] = token->word;
		token = token->next;
	}
	return (arg);
}