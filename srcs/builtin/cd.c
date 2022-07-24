/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 12:40:01 by brhajji-          #+#    #+#             */
/*   Updated: 2022/07/23 17:43:23 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	change_env_dir(t_exec	*utils)
{
	t_env	*temp;
	char	temp2[1024];

	getcwd(temp2, sizeof(temp2));
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
			temp->content = ft_strjoin("PWD=", ft_strcpy(temp2));
			return ;
		}
		temp = temp->next;
	}
}

char	*get_home(t_exec *utils)
{
	t_env	*tmp;

	tmp = utils->envp_lst;
	while (tmp && tmp->content)
	{
		if (!strncmp("HOME=", tmp->content, 5))
			return (tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}

int	manage_open_cd(char *path, t_exec *utils)
{
	if (opendir(path))
	{
		chdir(path);
		change_env_dir(utils);
		utils->err = 0;
		return (0);
	}
	else
	{
		perror("cd");
		utils->err = 1;
	}
	return (1);
}

void	add_old(t_exec *utils)
{
	t_env	*temp;
	char	temp2[1024];

	temp = utils->envp_lst;
	getcwd(temp2, sizeof(temp2));
	while (temp)
	{
		if (!strncmp(temp->content, "OLDPWD=", 7))
		{
			temp->content = ft_strjoin(ft_strcpy("OLDPWD"), ft_strcpy(temp2));
			return ;
		}
		temp = temp->next;
	}
	temp = ft_new_env(ft_strjoin(ft_strcpy("OLDPWD="), temp2));
	utils->envp_lst = ft_envadd_back(utils->envp_lst, temp);
}

int	cd(char *path, t_exec *utils)
{
	char	*tmp;

	utils->envp_lst = init_lst_env(utils->envp, utils);
	add_old(utils);
	if (!path)
	{
		tmp = get_home(utils);
		if (tmp)
		{
			chdir(get_home(utils) + 5);
			change_env_dir(utils);
			return (0);
		}
		else
		{
			write(2, "cd: HOME not set\n", 17);
			utils->err = 1;
		}
	}
	if (utils->err != 1 && !manage_open_cd(path, utils))
		return (0);
	return (1);
}
