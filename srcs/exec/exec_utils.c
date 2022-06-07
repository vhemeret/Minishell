/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:04:55 by brhajji-          #+#    #+#             */
/*   Updated: 2022/06/07 18:50:14 by brhajji-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


int		get_nb_arg(t_token *token)
{
	int	i;

	i = 1;
	while (token)
	{
		if (token->type == ARG)
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
	//printf("nb_arg = %i\n", nb_arg);
	arg = malloc(sizeof(char *) * (nb_arg + 1));
	*arg = token->word;
	token = token->next;
	printf("arg 0 = %s\n", arg[0]);
	while (++i < nb_arg && token->type == ARG)
	{
		arg[i] = token->word;
		printf("arg %i = %s\n",i, arg[i]);
		token = token->next;
	}
	arg[i] = NULL;
	return (arg);
}