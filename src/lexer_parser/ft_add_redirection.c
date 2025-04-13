/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 20:22:23 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/13 22:36:32 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_add_redirection(char **table, t_command *cmd, int index, int len)
{
    int count;

    printf("DEBUG [ft_add_redirection]: Entrada - table[%d]: '%s', len: %d\n",
           index, table[index] ? table[index] : "NULL", len);

    count = 0;
    while (table[index][count] && (table[index][count] == '<' || table[index][count] == '>'))
        count++;

    printf("DEBUG [ft_add_redirection]: count de caracteres de redirección: %d\n", count);

    if (count != len)
        return (printf("syntax error near unexpected token `%c'\n", table[index][0]), 1);

    if (table[index][len] == '\0')
    {
        printf("DEBUG [ft_add_redirection]: Token de redirección sin archivo, pasando al siguiente\n");
        len = 0;
        index++;
        if (table[index] == NULL)
        {
            return (printf("syntax error near unexpected token `newline'\n"), 1);
        }
    }

    printf("DEBUG [ft_add_redirection]: Procesando con index: %d, len: %d\n", index, len);
    printf("DEBUG [ft_add_redirection]: Archivo a procesar: '%s'\n", table[index] + len);

    if (cmd->redirect & IN_REDIR)
    {
        printf("DEBUG [ft_add_redirection]: Añadiendo archivo de entrada\n");
        cmd->from_file = ft_strdup(table[index] + len);
        printf("DEBUG [ft_add_redirection]: from_file después de strdup: '%s'\n",
               cmd->from_file ? cmd->from_file : "NULL");
    }
    else if (cmd->redirect & HEREDOC)
    {
        printf("DEBUG [ft_add_redirection]: Añadiendo heredoc\n");
        cmd->hdocs_end = ft_many_redirect(cmd->hdocs_end, table[index], len);
    }
    else
    {
        printf("DEBUG [ft_add_redirection]: Añadiendo archivo de salida\n");
        cmd->to_file = ft_many_redirect(cmd->to_file, table[index], len);
    }

    return (0);
}

