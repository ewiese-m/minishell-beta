/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_io_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 20:23:15 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/13 22:35:59 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char **ft_add_io_file(char **old_files, char *new_file, int len_redirection)
{
    int     size;
    char    **files;
    int     i;
    char    *file_path;

    printf("DEBUG [ft_add_io_file]: old_files: %p, new_file: '%s', len: %d\n",
           old_files, new_file ? new_file : "NULL", len_redirection);

    size = 0;
    if (old_files)
    {
        while (old_files[size])
            size++;
    }

    printf("DEBUG [ft_add_io_file]: Cantidad de archivos existentes: %d\n", size);

    files = (char **)malloc((size + 2) * sizeof(char *));
    if (!files)
        return (NULL);

    i = 0;
    while (i < size)
    {
        files[i] = old_files[i];
        i++;
    }

    // Crear una nueva variable para verificar la substring
    file_path = ft_substr(new_file, len_redirection, ft_strlen(new_file));
    printf("DEBUG [ft_add_io_file]: Archivo después de substring: '%s'\n",
           file_path ? file_path : "NULL");

    files[size] = file_path;
    files[size + 1] = NULL;

    if (old_files)
        free(old_files);

    return (files);
}
