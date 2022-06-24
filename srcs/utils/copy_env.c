/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 15:33:24 by vahemere          #+#    #+#             */
/*   Updated: 2022/06/22 14:24:05 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**copy_env(char **env)
{
	char	**dest;
	int		i;

	i = 0;
	while (env[i])
		i++;
	dest = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (env[++i])
		dest[i] = env[i];
	dest[i] = NULL;
	return (dest);
}
