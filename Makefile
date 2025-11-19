# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vpoelman <vpoelman@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/19 02:53:18 by vpoelman          #+#    #+#              #
#    Updated: 2025/11/19 02:53:19 by vpoelman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iincludes
LDFLAGS = -lreadline

SRCS = src/core/minishell_core.c \
       src/core/signals_setup.c \
       src/parser/parser_main.c \
       src/parser/parser_helpers.c \
       src/parser/tokenizer.c \
       src/parser/word_parser.c \
       src/parser/word_parser_helpers.c \
       src/parser/syntax_validator.c \
       src/parser/command_builder.c \
       src/parser/command_token_handlers.c \
       src/execution/executor_command.c \
       src/execution/executor_single.c \
       src/execution/executor_pipeline.c \
       src/execution/executor_execve_error.c \
       src/execution/executor_process_utils.c \
       src/expansion/expansion_variable_handlers.c \
       src/redirection/redirect.c \
       src/redirection/redirect_heredoc.c \
       src/utils/ft_string.c \
       src/utils/ft_string_advanced.c \
       src/utils/conversion_utils.c \
       src/utils/file_path_utils.c \
       src/utils/memory_macros.c \
       src/utils/split_utils.c \
       src/builtins/builtin_main.c \
       src/builtins/builtin_echo.c \
       src/builtins/builtin_cd_pwd.c \
       src/builtins/builtin_export_unset.c \
       src/builtins/export_arg_handlers.c \
       src/builtins/builtin_env_exit.c \
       src/builtins/builtin_exit_helpers.c \
       src/expansion/expansion.c \
       src/env/env_utils.c \
       src/env/env_set.c \
       src/utils/cleanup.c \
       src/utils/env_basic_utils.c \
       src/utils/error_utils.c \
       src/utils/error_format.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re 