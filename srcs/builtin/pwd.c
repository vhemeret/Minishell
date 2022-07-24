/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 15:09:45 by brhajji-          #+#    #+#             */
/*   Updated: 2022/07/23 17:15:50 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	pwd(char **envp)
{
	char	temp[1024];

	(void)(envp);
	getcwd(temp, sizeof(temp));
	printf("%s\n", getcwd(temp, sizeof(temp)));
	return (-1);
}
