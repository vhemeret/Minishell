/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_darr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 20:30:51 by vahemere          #+#    #+#             */
/*   Updated: 2022/06/22 14:24:13 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	len_darr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}
