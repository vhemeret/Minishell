/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 18:14:41 by vahemere          #+#    #+#             */
/*   Updated: 2022/04/17 23:10:39 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*####################### LIBRARIES #######################*/

# include <stdio.h> 
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

/*####################### STRUCTURES #######################*/

typedef struct s_cmd
{
	char			*cmd; //malloced
	struct s_cmd	*next;
}				t_cmd; //malloced

/*####################### PROTOTYPES #######################*/

	/*### PARSING ###*/
void	manage_cmd(char *cmd_line, t_cmd **cmd);
int		pars_cmd_line(char *cmd_line);

	/*###   EXEC  ###*/
	
	/*###  UTILS  ###*/
char	*ft_strdup(char *str);
int		ft_strlen(char *str);
int		check_pipe(char *cmd);
int		is_whitespace(char c);

	/*### CLEANING ###*/
void	free_double_array(char **arr);

#endif