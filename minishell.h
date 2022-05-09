/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 18:14:41 by vahemere          #+#    #+#             */
/*   Updated: 2022/05/09 13:32:00 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*####################### LIBRARIES #######################*/

# include <stdio.h> 
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

#define ICI printf("ICI\n");

/*####################### STRUCTURES #######################*/

typedef enum s_type
{
	CMD, // cmd								0
	ARG, // argument						1
	R_IN, // <								2
	R_OUT, // >								3
	DR_OUT, // >>							4
	DR_IN, // << (HERE_DOC)					5
	INFILE,	// word following <				6
	OUTFILE, // word following >			7
	LIMITOR, // word following <<			8
	OUTFILE_DROUT, // word following >>		9
	PIPE,//									10
}			t_type;

char	*types[11] = {"CMD", "ARG", "R_IN", "R_OUT", "DR_IN", "DR_OUT", "INFILE", "OUTFILE", "LIMITOR", "OUTFILE_DROUT", "PIPE"};
typedef struct s_quote
{
	int	is_quote;
	int	is_dquote;
}				t_quote;

typedef struct s_token
{
	char			*word;
	int				index;
	struct s_token	*next;
	enum s_type		type;
} 				t_token;

/*####################### PROTOTYPES #######################*/

	/*### PARSING ###*/
void	manage_cmd(char *cmd_line);
int		pars_cmd_line(char *cmd_line);
void	tokenizer(char **cmd);

	/*###   EXEC  ###*/

	/*###  UTILS  ###*/
char	*ft_strdup(char *str);
int		ft_strlen(char *str);
int		is_sep(char c);
void	quoting_state(char c, t_quote *state);
int		next_dquote(char *cmd);
int		next_squote(char *cmd);
int		next_dquote_len(char *cmd, int i);
int		next_squote_len(char *cmd, int i);
int		is_whitespace(char c);
int		sp_word(char *cmd, int i, t_quote *state);
int		pipe_word(char *cmd, int i, t_quote *state);
int		redir_word(char *cmd, int i, t_quote *state);
int		is_drout(t_token *tmp);
int		is_drin(t_token *tmp);
int		is_outfile_drout(t_token *save);
int		is_limitor(t_token *save);
int		is_type(t_token *tmp);

	/*### CLEANING ###*/
void	free_double_array(char **arr);

#endif