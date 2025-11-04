#ifndef MINISHELL_H
# define MINISHELL_H

# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

extern volatile sig_atomic_t	g_sigint_received;

# define PROMPT "minishell$ "
# define TOKEN_WORD 0
# define TOKEN_PIPE '|'
# define TOKEN_REDIR_IN '<'
# define TOKEN_REDIR_OUT '>'
# define TOKEN_APPEND 1
# define TOKEN_HEREDOC 2

typedef struct s_token
{
	char			*content;
	int				type;
	struct s_token	*next;
}					t_token;

typedef enum e_redir_type
{
	R_IN,
	R_OUT,
	R_APP,
	R_HEREDOC
}					t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*content;
	struct s_redir	*next;
}					t_redir;

typedef struct s_cmd
{
	char			**args;
	t_redir			*redirs;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_shell
{
	char			**env;
	int				status;
}					t_shell;

typedef struct s_exec_ctx
{
	pid_t			*pids;
	int				pid_count;
	int				prev_pipe;
}					t_exec_ctx;

typedef struct s_expand_ctx
{
	char			*result;
	size_t			j;
	size_t			buf_size;
	size_t			i;
}					t_expand_ctx;

typedef struct s_quote_state
{
	int				in_single;
	int				in_double;
}					t_quote_state;

typedef struct s_token_context
{
	t_token			*head;
	t_token			*current;
	t_shell			*shell;
}					t_token_context;


void				init_shell(t_shell *shell, char **env);
void				shell_loop(t_shell *shell);
void				cleanup_shell(t_shell *shell);
t_token				*tokenize(char *input, t_shell *shell);
t_cmd				*parse_tokens(t_token *tokens);
t_token				*create_token(char *word, int type);
int					validate_syntax(t_token *tokens);
void				add_token_to_list(t_token **head, t_token **current,
						char *content, int type);
char				*remove_quotes(char *str);
int					should_expand_variable(char *word);
char				*parse_word(char *input, int *pos);
void				skip_whitespace(char *input, int *i);
int					handle_word_token_main(char *input, int *i,
						t_token_context *ctx);
void				handle_field_splitting_main(char *expanded_word,
						t_token **head, t_token **current);
t_cmd				*parse_commands(t_token *tokens);
void				handle_input_redir(char *input, int *i, t_token **head,
						t_token **current);
void				handle_output_redir(char *input, int *i, t_token **head,
						t_token **current);
t_redir				*add_redir_to_list(t_redir *redirs, t_redir_type type,
						char *content);
char				**add_arg_to_array(char **args, const char *new_arg);
t_cmd				*create_new_command(void);
t_token				*parse_command_tokens(t_cmd *cmd, t_token *tokens);
t_token				*handle_redir_token(t_cmd *cmd, t_token *tokens);
int					is_redir_token(int token_type);
int					execute_cmd(t_cmd *cmd, t_shell *shell);
int					execute_commands(t_cmd *cmds, t_shell *shell);
int					execute_pipeline_loop(t_cmd *cmds, t_shell *shell);
int					execute_single_command(t_cmd *cmds, t_shell *shell);
int					get_process_exit_code(int status);
int					handle_enoexec_error(char *path, char **args, char **env);
int					exec_external_command(char **args, char **env);
int					execute_builtin(t_cmd *cmd, t_shell *shell);
int					find_builtin_index(char *args);
int					builtin_echo(t_cmd *cmd);
int					builtin_cd(t_cmd *cmd, t_shell *shell);
int					builtin_pwd(void);
int					builtin_export(t_cmd *cmd, t_shell *shell);
int					builtin_unset(t_cmd *cmd, t_shell *shell);
int					builtin_env(t_shell *shell);
int					builtin_exit(t_cmd *cmd, t_shell *shell);
int					validate_exit_arg(char *arg);
int					get_exit_code(char *arg, int default_code);
char				*get_cd_path(char **args, t_shell *shell);
int					is_valid_identifier(const char *str);
int					process_export_arg(char *arg, t_shell *shell);
int					handle_heredoc(char *delimiter, t_shell *shell);
void				process_heredoc_line(char *line, int fd, int quoted,
						t_shell *shell);
char				*expand_variables(char *str, t_shell *shell);
char				*expand_variables_with_quotes(char *word, t_shell *shell);
char				**field_split(char *str);
void				resize_buffer(t_expand_ctx *ctx, size_t j);
void				handle_dollar_expansion(char *clean_word, t_expand_ctx *ctx,
						t_shell *shell);
void				expand_var(char *str, t_expand_ctx *ctx,
						t_shell *shell);
char				*get_env_value(char *name, char **env);
char				**copy_env(char **env);
char				**create_expanded_env(t_shell *shell, const char *key,
						const char *value);
int					copy_env_entries(char **new_env, char **env);
int					replace_env_value(char **env_var, const char *key,
						const char *value);
void				compact_env_array(char **env, int remove_idx);
int					set_env_var(t_shell *shell, const char *key,
						const char *value);
int					unset_env_var(t_shell *shell, const char *key);
void				setup_signals(void);
void				handle_sigint(int sig);
void				handle_sigquit(int sig);
void				setup_child_signals(void);
char				**ft_split(char const *s, char c);
char				*ft_strjoin(char const *s1, char const *s2);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strdup(const char *s1);
char				*ft_strndup(const char *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
size_t				ft_strlen(const char *s);
int					ft_isalnum(int c);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
char				*ft_itoa(int n);
char				*ft_strchr(const char *s, int c);
char				*ft_format_env(const char *key, const char *value);
void				print_errno(const char *prefix, const char *name);
void				print_cmd_error(const char *cmd, const char *message);
void				print_cmd_errno(const char *cmd);
void				write_error(const char *message);
void				write_stdout(const char *message);
char				*find_executable(char *cmd, char **env);
char				*search_in_paths(char *cmd, char **paths);
void				cleanup_str_array(char **env);
void				free_tokens(t_token *tokens);
void				free_cmds(t_cmd *cmds);
void				free_redirs(t_redir *redirs);
void				free_single_cmd(t_cmd *cmd);
void				print_exported_vars(t_shell *shell, int j);
int					count_env_vars(char **env);
int					read_heredoc_loop(int fd, char *delim, int quoted,
						t_shell *shell);
char				*extract_word(char const *s, char c, int start);
int					handle_cd_execution(char *path, t_shell *shell);
int					handle_export_with_value(char *arg, char *eq,
						t_shell *shell);
int					handle_export_without_value(char *arg);
int					process_redirections(t_cmd *cmd, t_shell *shell,
						int child_mode);
int					has_unclosed_quotes(const char *input);
int					wait_for_children(pid_t *pids, int count);
int					count_commands(t_cmd *cmds);
int					has_input_redir(t_redir *redirs);
int					has_output_redir(t_redir *redirs);

#endif
