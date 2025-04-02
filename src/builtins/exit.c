/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:59:55 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/01 23:38:08 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtin_exit(t_command *cmd)
{
	int	exit_code;

	ft_putstr_fd("exit\n", 2);
	if (!cmd->args[1])
	{
		return (-1);
	}
	if (!is_valid_exit_arg(cmd->args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd->args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (255);
	}
	if (cmd->args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	exit_code = ft_atoi(cmd->args[1]);
	return (-(exit_code & 255));
}

// Cuando cmd->args[1] no es un argumento numérico válido,
// se llama a exit(255) directamente,
// lo que significa que no se liberan todos los recursos
// antes de terminar el programa.
// Esta es una decisión de diseño, pero podría ser mejor
// devolver un código que permita a la función
// principal manejar la limpieza antes de salir.
// aca llamar un garbage collector!
