/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 21:30:00 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/05 18:18:13 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	setup_signals(void)
{
	signal(SIGINT, ft_signal_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
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
			break ;
		}
		exit_status = process_command(line, env_list, env_copy);
		if (exit_status < 0)
		{
			update_exit_status(env_list, -exit_status);
			break ;
		}
		else
		{
			update_exit_status(env_list, exit_status);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env_list;
	char	**env_copy;
	int		final_status;

	final_status = 0;
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
	add_exit_status_var(env_list);
	minishell_loop(env_list, env_copy);
	final_status = get_exit_status(env_list);
	cleanup_resources(env_list);
	free_env_array(env_copy);
	return (final_status);
}
