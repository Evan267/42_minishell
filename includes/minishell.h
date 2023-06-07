#ifndef MAKEFILE_H
# define MAKEFILE_H
# include "../libft/libft.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <termios.h>
# include <termcap.h>

/*Builtins*/
int		ft_echo(int argc, char **argv);
int		ft_cd(int argc, char **argv, char ***env);
int		ft_pwd(int argc, char **argv);
int		ft_unset(int argc, char **argv, char ***env);
int		ft_env(int argc, char **argv, char ***env);
int		ft_exit(int argc, char **argv, char ***env, int *in_out);
int		ft_export(int argc, char **argv, char ***env);
int		call_export(char **env);
void	put_export(char	*str);
char	**del_var(char **var, int bin);
int		laws_env(char *var);
char	**new_env(char ***var, char **env);
char	**parse_var(char **str);
char	**same_var(char **var);
int		fund_equal(char *str);
int		longest_word(char *s1, char *s2);

/*Exec*/
char	*ft_path(char **args, char *envpath);
void	exec(char *cmd, char **env[]);
int		exec_builtins(char *cmd, char ***env, int whichBuiltins, int *in_out);
int		builtins(char **args, char ***env, int builtin, int *in_out);
int		test_builtins(char *cmds);
void	dup_cond(int *in_out, int *i, int **pipes);
void	dup_in_out(int in, int out);
void	saved_dup(int *in_out);
void	stop_pipes(int **pipes, int len_cmds);
int		**create_pipes(int len_cmds);
void	close_pipes(int **pipes, int len_cmds);
void	close_infile_outfile(int in, int out);
char	*infile_outfile(char *cmd, int *in_out, int **pipes, int *i);
char	*delete_infile_outfile(char **split);
int		here_doc(char *limiter);
void	error_open(char *file, int fd, int must_exit);

/*Tools*/
char	*join_3_str(char *str1, char *str2, char *str3);
char	*ft_joinsplit(char **split);
void	trim_by_char(char **ret, char c);
char	*empty_str(char *str);
void	ctrl_d(char *promtp, char **envp, int sw);
void	set_signals(void);
void	exit_sig(void);
void	heredoc_sigint(void);
void	pipe_sigint(void);
int		setstop(int nb);
int		getstop(void);

/*Parsing*/
int		test_quote(char *command);/*a verifier*/
char	**test_space(char **ret);/*a verifier*/
char	*test_ech(char *command);/*a verifier*/
char	*test_sh(char *command);/*a verifier*/
int		permission_denied(char *command);/*a verifier*/
int		command_not_found(char *command);/*a verifier*/
char	*getvaluevar(char *var_name, char **env);
char	*replace_env_var(char *line, int status, char ***env);
char	**ft_split_cmds(char const *s, char c);
char	*delete_char(char *str, char *c);
char	*delete_quote(char *str, char c);
char	**ft_trim_builtins(char **arg);
char	*delete_pipe_outfile(char *line);

/* Readline */
char	*readline_with_prompt(char **env);
int		execute_cmds(char *line, char **env[], int status);
void	save_history(char *line, char *history_file, char **env);
void	reload_history(char *history_file, char **env);

# endif
