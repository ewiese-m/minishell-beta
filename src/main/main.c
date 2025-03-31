/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 21:30:00 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/03/31 23:04:24 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			g_exit_status = 0;

static void	setup_signals(void)
{
	signal(SIGINT, ft_signal_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	rl_catch_signals = 0;
}

static int	process_command(char *line, t_env *env_list, char **env_copy)
{
	t_command	*cmds;
	int			exit_status;

	// char		**envps;
	exit_status = 0;
	if (!line || *line == '\0')
		return (0);
	add_history(line);
	cmds = ft_parse_input(line, env_list);
	if (cmds)
	{
		if (ft_strcmp(cmds->command, "exit") == 0)
			exit_status = builtin_exit(cmds);
		else if (is_builtin(cmds->command))
		{
			// envps = ft_create_env_array(env_list);
			exit_status = execute_builtin(cmds, env_copy);
		}
		else
			exit_status = execute_commands(cmds, env_list);
		ft_free_cmdlist(&cmds);
	}
	free(line);
	return (exit_status);
}

static void	cleanup_resources(t_env *env_list)
{
	t_env	*current;
	t_env	*next;

	current = env_list;
	while (current)
	{
		next = current->next;
		if (current->key)
			free(current->key);
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
	clear_history();
}

static void	minishell_loop(t_env *env_list, char **env_copy)
{
	char	*line;
	int		exit_status;

	while (1)
	{
		line = readline("minishell> ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		exit_status = process_command(line, env_list, env_copy);
		if (exit_status < 0)
		{
			exit(g_exit_status);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env_list;
	char	**env_copy;

	(void)argc;
	(void)argv;
	env_copy = create_env_copy(envp);
	setup_signals();
	env_list = ft_get_envp(envp);
	if (!env_list)
	{
		fprintf(stderr, "Error: Failed to initialize environment\n");
		return (1);
	}
	// g_minishell.envs = env_list;
	minishell_loop(env_list, env_copy);
	cleanup_resources(env_list);
	free_env_copy(env_copy);
	return (0);
}
