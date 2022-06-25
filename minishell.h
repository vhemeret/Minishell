/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 18:14:41 by vahemere          #+#    #+#             */
/*   Updated: 2022/06/24 19:15:26 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*####################### LIBRARIES #######################*/

# include <stdio.h> 
# include <stdlib.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <sys/types.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <unistd.h>
# include <dirent.h>

/*####################### STRUCTURES #######################*/

typedef struct s_exec
{
	char 			**envp;
	int				nb_node;
	int				nb_cmd;
	int				previous_fd;
	struct s_node	*node;
	struct s_node	*node_tmp;
	struct s_token	*token_tmp;
}			t_exec;

typedef struct s_node
{
	int				in;
	int				out;
	int				here_doc_fd;
	char			*here_doc;
	int				has_cmd;
	int				num;
	struct s_node	*next;
}			t_node;

typedef enum s_type
{
	CMD,
	ARG,
	R_IN,	
	R_OUT,
	DR_OUT,
	DR_IN,
	FD,
	PIPE,
}			t_type;

typedef struct s_quote
{
	int	is_quote;
	int	is_dquote;
}				t_quote;

typedef struct s_expand
{
	char	*str;
	int		len;
	int		found;
}				t_expand;

typedef struct s_token
{
	char			*word;
	int				index;
	int				nb_words;
	struct s_token	*next;
	struct s_token	*back;
	enum s_type		type;
}				t_token;

/*####################### PROTOTYPES #######################*/

	/*### PARSING ###*/

int		is_word(char *cmd, int i, t_quote *state);
int		end_word(char *cmd, int i, t_quote *state);
int		sep_word(char c);
int		first_check(char *cmd);
t_token	*manage_cmd(char *cmd_line, char **env);
// int		nb_words(char *cmd_line, t_quote *state);
void	tokenizer(char **cmd, t_token **lst, int len);
int		is_type(t_token *tmp);
int		syntax_check(t_token **lst);
int		check_quote(char *cmd_line, t_quote *state);
int		is_drout(t_token *tmp);
int		is_drin(t_token *tmp);
int		is_outfile_drout(t_token *save);
int		is_limitor(t_token *save);
void	expand(t_token **lst, t_quote *state, char **env);
char	**split_word(char *word, t_quote *state);

	/*###   EXEC  ###*/

char	**get_arg(t_token *token);
void	exec(t_token *token, char **envp);
void	set_r_in(t_node	*node, t_token *token);
void	set_r_out(t_node *node, t_token *token);
char	**get_path(char **envp);
void	init_exec(t_token *token, t_exec **utils);
int		nb_cmd(t_token *token);
void 	here_doc_init(t_node *node, t_token *token);
t_token *go_next(t_token *token);
	
	/*###   BUILT IN  ###*/

int	env(char **envp);
int pwd(char **envp);
int	cd(char *path);

	/*###  UTILS  ###*/

char	*ft_strdup(char *str);
int		ft_strlen(char *str);
void	quoting_state(char c, t_quote *state);
int		next_dquote(char *cmd);
int		next_squote(char *cmd);
int		next_dquote_len(char *cmd, int i, t_quote *state);
int		next_squote_len(char *cmd, int i, t_quote *state);
int		is_whitespace(char c);
int		pipe_word(char *cmd, int i, t_quote *state);
int		redir_word(char *cmd, int i, t_quote *state);
char	**copy_env(char **env);
char	*ft_strcpy(char *src);
char	**ft_split(char *s, char c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_itoa(int n);
int		ft_strcmp(char *s1, char *s2);
int		len_darr(char **arr);

	/*### CLEANING ###*/
void	free_double_array(char **arr);
int		print_and_free(char *str, t_token **lst);
void 	ft_free_node(t_node *node);
void 	ft_free_token(t_token *token);

#endif
