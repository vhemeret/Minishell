/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 23:29:23 by brhajji-          #+#    #+#             */
/*   Updated: 2022/07/11 16:46:36 by brhajji-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_parsing(char *str)
{
	printf("test => %s \n", str);
	if (*str == '=' || *str == '$' || *str == '/' || *str == ' ' || *str == '.')
	{
		printf("export : `%s': not a valid identifier\n", str);
		return (1);
	}
	else
	{
		return (0);	
	}
}

char	*plus_egale(char *str, char *var, int egale)
{
	int		size;
	char	*rendu;
	int		i;

	i = -1;
	size = ft_strlen(str) + ft_strlen(var + egale + 2);
	rendu = malloc(sizeof(char) * (size + 1));
	if (!rendu)
		return (NULL);
	while (str[++i])
		rendu[i] = str[i];
	while (*(var + egale + 2))
	{
		rendu[i] = *(var + egale + 2);
		i++;
		egale++;
	}
	rendu[i] = '\0';
	return (rendu);
}