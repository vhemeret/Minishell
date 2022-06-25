/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 15:09:32 by brhajji-          #+#    #+#             */
/*   Updated: 2022/06/25 16:35:31 by brhajji-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env	*init_lst_env(char **envp)
{
	t_env	
	while ()
}

int	env(char **envp)
{
	if (!envp)
		return (-1);
	while (*envp)
	{
		printf("%s\n", *envp);
		envp++;
	}
	return (0);
}