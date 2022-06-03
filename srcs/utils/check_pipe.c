/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:13:11 by vahemere          #+#    #+#             */
/*   Updated: 2022/04/10 18:04:18 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_pipe(char *cmd)
{
	int i;
	int	nb_pipe;

	i = -1;
	nb_pipe = 0;
	if (cmd)
	{
		while (cmd[++i])
		{
			if (cmd[i] == '|')
				nb_pipe++;
		}
		return (nb_pipe);
	}
	return (0);
}
