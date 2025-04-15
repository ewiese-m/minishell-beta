# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
#CFLAGS = -Wall -Wextra -g
INCLUDE = -I./includes -I./libft

# Directories
OBJ_DIR = obj
SRC_DIR = src
INCLUDES_DIR = includes
LIBFT_DIR = libft

# Source files
SRCS = $(SRC_DIR)/main/main.c \
       $(SRC_DIR)/main/process_command.c \
       $(SRC_DIR)/main/main_utils.c \
       $(SRC_DIR)/debug/display_command.c \
       $(SRC_DIR)/debug/display_command_details.c \
       $(SRC_DIR)/debug/display_redirections.c \
       $(SRC_DIR)/lexer_parser/count_command.c \
       $(SRC_DIR)/lexer_parser/extract_command.c \
       $(SRC_DIR)/lexer_parser/ft_add_io_file.c \
       $(SRC_DIR)/lexer_parser/ft_add_redirection.c \
       $(SRC_DIR)/lexer_parser/ft_arrange_table.c \
       $(SRC_DIR)/lexer_parser/ft_checkforgarbage.c \
       $(SRC_DIR)/lexer_parser/ft_check_redirect.c \
       $(SRC_DIR)/lexer_parser/ft_create_fullcmd.c \
       $(SRC_DIR)/lexer_parser/ft_free_cmdlist.c \
       $(SRC_DIR)/lexer_parser/ft_free_dstr.c \
       $(SRC_DIR)/lexer_parser/ft_get_redirection.c \
       $(SRC_DIR)/lexer_parser/ft_lexer.c \
       $(SRC_DIR)/lexer_parser/ft_many_cmd.c \
       $(SRC_DIR)/lexer_parser/ft_many_redirect.c \
       $(SRC_DIR)/lexer_parser/ft_parse_input.c \
       $(SRC_DIR)/lexer_parser/ft_parser.c \
       $(SRC_DIR)/lexer_parser/ft_realloc.c \
       $(SRC_DIR)/lexer_parser/ft_removesurplusspaces.c \
       $(SRC_DIR)/lexer_parser/ft_tokenize.c \
       $(SRC_DIR)/lexer_parser/parse_cmd_into_array.c \
       $(SRC_DIR)/lexer_parser/tokenize_parse_and_link_commands.c \
       $(SRC_DIR)/lexer_parser/ft_expand_variable.c \
       $(SRC_DIR)/lexer_parser/ft_extract_env_var.c \
       $(SRC_DIR)/lexer_parser/ft_process_quotes.c \
       $(SRC_DIR)/lexer_parser/handle_expansion.c \
       $(SRC_DIR)/lexer_parser/ft_resize_string_array.c \
       $(SRC_DIR)/environment_management/create_env_copy.c \
       $(SRC_DIR)/environment_management/free_env_array.c \
       $(SRC_DIR)/environment_management/free_list.c \
       $(SRC_DIR)/environment_management/ft_create_env_node.c \
       $(SRC_DIR)/environment_management/ft_env_conversion.c \
       $(SRC_DIR)/environment_management/ft_get_envp.c \
       $(SRC_DIR)/signal_handling/signal.c \
       $(SRC_DIR)/builtins/builtins_main.c \
       $(SRC_DIR)/builtins/cd.c \
       $(SRC_DIR)/builtins/cd_utils/cd_utils.c \
       $(SRC_DIR)/builtins/echo.c \
       $(SRC_DIR)/builtins/echo_utils/echo_utils.c \
       $(SRC_DIR)/builtins/env.c \
       $(SRC_DIR)/builtins/exit.c \
       $(SRC_DIR)/builtins/export.c \
       $(SRC_DIR)/builtins/export_utils/export_utils.c \
       $(SRC_DIR)/builtins/pwd.c \
       $(SRC_DIR)/builtins/unset.c \
       $(SRC_DIR)/builtins/utils.c \
       $(SRC_DIR)/builtins/env_utils/get_env_size.c \
       $(SRC_DIR)/builtins/env_utils/get_env_value.c \
       $(SRC_DIR)/builtins/env_utils/is_valid_env_name.c \
       $(SRC_DIR)/builtins/env_utils/remove_from_env.c \
       $(SRC_DIR)/builtins/env_utils/update_env.c \
       $(SRC_DIR)/execution/command_execution.c \
       $(SRC_DIR)/execution/execution_exit_status.c \
       $(SRC_DIR)/execution/execution_main.c \
       $(SRC_DIR)/path_resolution/path_env.c \
       $(SRC_DIR)/path_resolution/path_resolution.c \
       $(SRC_DIR)/path_resolution/path_utils.c \
       $(SRC_DIR)/path_resolution/error_handling.c \
       $(SRC_DIR)/pipelines/execute_pipeline_command.c \
       $(SRC_DIR)/pipelines/pipeline.c \
       $(SRC_DIR)/pipelines/pipeline_creation.c \
       $(SRC_DIR)/pipelines/pipeline_execution.c \
       $(SRC_DIR)/pipelines/pipeline_redirections.c \
       $(SRC_DIR)/pipelines/pipelines_utils.c \
       $(SRC_DIR)/pipelines/pipeline_utils.c \
       $(SRC_DIR)/redirections/heredoc.c \
       $(SRC_DIR)/redirections/input_redirection.c \
       $(SRC_DIR)/redirections/output_redirection.c \
       $(SRC_DIR)/redirections/redirections.c \
       $(SRC_DIR)/redirections/redirections_utils.c \
       $(SRC_DIR)/gc_utils/gc_memory.c \
       $(SRC_DIR)/gc_utils/gc_tracking.c

# Object files
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Target executable
NAME = minishell

# External libraries
LIBS = -L$(LIBFT_DIR) -lft -lreadline

# Rules
all: $(NAME)

# Create object files directly without explicit directory creation
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@test -d $(@D) || /bin/mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME): $(OBJS)
	@echo "Building libft..."
	@make -C $(LIBFT_DIR)
	@echo "Building minishell..."
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@echo "Build complete!"

clean:
	@echo "Cleaning object files..."
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@echo "Clean complete!"

fclean: clean
	@echo "Cleaning executable..."
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo "Full clean complete!"

re: fclean all

.PHONY: all clean fclean re
