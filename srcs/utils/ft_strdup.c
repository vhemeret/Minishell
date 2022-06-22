/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 03:39:51 by vahemere          #+#    #+#             */
/*   Updated: 2022/06/22 14:24:45 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strdup(char *str)
{
	char	*dest;
	int		i;

	i = -1;
	if (!str)
	{
		str = malloc(sizeof(char) * 1);
		if (!str)
			return (NULL);
		str[0] = '\0';
		return (str);
	}
	dest = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!dest)
		return (NULL);
	while (str[++i])
		dest[i] = str[i];
	dest[i] = '\0';
	return (dest);
}
