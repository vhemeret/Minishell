/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 12:47:03 by brhajji-          #+#    #+#             */
/*   Updated: 2022/06/06 15:24:17 by brhajji-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>
#include "../../minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	i;
	char	*new;

	if (!s1 || !s2)
		return (NULL);
	len1 = (size_t) ft_strlen(s1);
	len2 = (size_t)ft_strlen(s2);
	new = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!new)
		return (NULL);
	i = 0;
	new[len1 + len2] = '\0';
	while (++i <= len1 || i <= len2)
	{
		if ((i < len1 && s1[len1 - i]) || (i == len1))
			new[len1 - i] = (char)s1[len1 - i];
		if ((i < len2 && s2[len2 - i]) || (i == len2))
			new[len2 + len1 - i] = (char)s2[len2 - i];
	}
	return (new);
}
