/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_memory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 10:30:40 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/15 16:43:23 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Wrapper for strdup that uses the shell's garbage collector
 */
char	*shell_strdup(t_minishell *shell, const char *s)
{
	if (!shell || !s)
		return (NULL);
	return (safe_strdup(&shell->gc, s));
}

/**
 * Wrapper for calloc that uses the shell's garbage collector
 */
void	*shell_calloc(t_minishell *shell, size_t count, size_t size)
{
	if (!shell)
		return (NULL);
	return (safe_calloc(&shell->gc, count, size));
}

/**
 * Wrapper for substr that uses the shell's garbage collector
 */
char	*shell_substr(t_minishell *shell, char const *s, unsigned int start,
		size_t len)
{
	if (!shell || !s)
		return (NULL);
	return (safe_substr(&shell->gc, s, start, len));
}

/**
 * Wrapper for strjoin that uses the shell's garbage collector
 */
char	*shell_strjoin(t_minishell *shell, char const *s1, char const *s2)
{
	if (!shell || !s1 || !s2)
		return (NULL);
	return (safe_strjoin(&shell->gc, s1, s2));
}

/**
 * Clean up all resources and exit
 */
void	shell_cleanup(t_minishell *shell, int status)
{
	int		i;
	t_env	*current_env;
	t_env	*next_env;

	if (!shell)
		exit(status);
	rl_clear_history();
	if (shell->env_array)
	{
		i = 0;
		while (shell->env_array[i])
			i++;
	}
	current_env = shell->envs;
	while (current_env)
	{
		next_env = current_env->next;
		current_env = next_env;
	}
	gc_close_all_fds(&shell->gc);
	gc_free_all(&shell->gc);
	exit(status);
}
