SRCS		= srcs/main.c \
			  srcs/readline/prompt.c \
			  srcs/readline/commands.c \
			  srcs/readline/history.c \
			  srcs/tools/utils.c \
			  srcs/tools/signals.c \
			  srcs/parsing/var_env.c \
			  srcs/parsing/test.c \
			  srcs/parsing/ft_split_cmds.c \
			  srcs/parsing/ft_split_cmd.c \
			  srcs/parsing/trim_quote.c \
			  srcs/exec/path.c \
			  srcs/exec/here_doc.c \
			  srcs/exec/infile_outfile.c \
			  srcs/exec/infile_outfile2.c \
			  srcs/exec/pipes.c \
			  srcs/exec/exec.c \
			  srcs/exec/error.c \
			  srcs/exec/dup.c \
			  srcs/exec/builtins.c \
			  srcs/builtin/ft_cd.c \
			  srcs/builtin/ft_exit.c \
			  srcs/builtin/ft_echo.c \
			  srcs/builtin/ft_pwd.c \
			  srcs/builtin/ft_unset.c \
			  srcs/builtin/ft_env.c \
			  srcs/builtin/export/ft_export.c \
			  srcs/builtin/export/check_export.c \
			  srcs/builtin/export/display_export.c \
			  srcs/builtin/export/parse_export.c \
			  srcs/builtin/export/setvar_export.c

OBJS		= ${SRCS:.c=.o}

LFT			= ./libft/libft.a

HEAD		= ./includes -I ~/.brew/opt/readline/include

NAME		= minishell

CC			= gcc

CFLAGS		= -g -Wall -Wextra -Werror

.c.o:		
			${CC} ${CFLAGS} -I ${HEAD} -Ilibft -c $< -o ${<:.c=.o} 

${NAME}:	${LFT} ${OBJS}
			${CC} ${CFLAGS} ${OBJS} -L ./libft -L ~/.brew/opt/readline/lib -lft -lreadline -ltermcap -o ${NAME}

${LFT}:
			make -s -C libft

all:		${NAME}

bonus:		all

clean:
			${RM} ${OBJS} ${OBJS_BONUS}
			make clean -C libft

fclean:		clean
			${RM} ${NAME}
			make fclean -C libft

re:			fclean all

.PHONY:		all clean fclean re
