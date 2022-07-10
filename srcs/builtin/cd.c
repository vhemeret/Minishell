/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 12:40:01 by brhajji-          #+#    #+#             */
/*   Updated: 2022/06/29 17:42:07 by brhajji-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void change_env_dir(t_exec	*utils, char *path)
{
	t_env	*temp;
	
	if (!utils->envp_lst)
	{
		utils->envp_lst = init_lst_env(utils->envp, utils);
		utils->envp = lst_to_char(utils->envp_lst);
	}
	temp = utils->envp_lst;
	while (temp)
	{
		if (!strncmp(temp->content, "PWD=", 4))
		{
			//free(temp->content);
			temp->content = ft_strjoin("PWD=", path);
			return ;
		}
		temp = temp->next;
	}
}
char *get_home(t_exec *utils)
{
	t_env	*tmp;
	
	tmp = utils->envp_lst;
	while (tmp)
	{
		if (!strncmp("HOME=", tmp->content, 5))
			return (tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}

int	cd(char *path, t_exec *utils)
{
	char	*tmp;
	
	utils->envp_lst = init_lst_env(utils->envp, utils);
	if (!path)
	{
		tmp = get_home(utils);
		if (tmp)
		{
			chdir(get_home(utils) + 5);
			change_env_dir(utils, get_home(utils) + 5);
			return (0);	
		}
		else
			write(2 , "cd: HOME not set", 17);
	}
	else if (opendir(path))
	{
		chdir(path);
		change_env_dir(utils, path);
		return (0);
	}
	else
		perror("cd");
	return (1);
}