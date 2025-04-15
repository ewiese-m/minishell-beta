/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 10:31:37 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/15 18:37:15 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <ctype.h> // Funciones de caracteres
# include <errno.h>
# include <fcntl.h>
# include <limits.h> // Definiciones de límites de tipo
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <readline/tilde.h>
# include <signal.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h> // Utilidades generales
# include <string.h> // Funciones de cadena y memoria
# include <sys/stat.h>
# include <sys/syscall.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h> // Funciones de sistema

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

// Bloque 1: Funciones de caracteres
int						ft_isalpha(int c);
int						ft_isdigit(int c);
int						ft_isalnum(int c);
int						ft_isascii(int c);
int						ft_isprint(int c);
int						ft_toupper(int c);
int						ft_tolower(int c);
int						ft_isspace(int c);

// Bloque 2: Funciones de cadena y memoria
void					*ft_memset(void *s, int c, size_t n);
size_t					ft_strlen(const char *s);
void					ft_bzero(void *s, size_t n);
void					*ft_memchr(const void *s, int c, size_t n);
void					*ft_memcpy(void *dest, const void *src, size_t n);
void					*ft_memmove(void *dest, const void *src, size_t n);
size_t					ft_strlcpy(char *dest, const char *src, size_t size);
size_t					ft_strlcat(char *dst, const char *src, size_t dstsize);
char					*ft_strchr(const char *s, int c);
int						ft_strcmp(const char *s1, const char *s2);
char					*ft_strcpy(char *dest, const char *src);
char					*ft_strrchr(const char *s, int c);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
int						ft_memcmp(const void *s1, const void *s2, size_t n);
char					*ft_strnstr(const char *big, const char *little,
							size_t len);
char					*ft_strdup(const char *s);

// Bloque 3: Conversión y asignación de memoria
int						ft_atoi(const char *str);
long long				ft_atoll(const char *str);
void					*ft_calloc(size_t count, size_t size);

// Bloque 4: Funciones avanzadas de cadena
char					*ft_substr(char const *s, unsigned int start,
							size_t len);
char					*ft_strjoin(char const *s1, char const *s2);
char					*ft_strtrim(char const *s1, char const *set);
char					**ft_split(char const *s, char c);
char					*ft_strcat(char *dest, const char *src);
char					*ft_itoa(int n);
char					*ft_strmapi(char const *s, char (*f)(unsigned int,
								char));
void					ft_striteri(char *s, void (*f)(unsigned int, char *));
void					ft_putchar_fd(char c, int fd);
void					ft_putstr_fd(char *s, int fd);
void					ft_putendl_fd(char *s, int fd);
void					ft_putnbr_fd(int n, int fd);

// Bloque 5: Funciones de listas enlazadas
typedef struct s_list
{
	void				*content;
	struct s_list		*next;
}						t_list;

t_list					*ft_lstnew(void *content);
void					ft_lstadd_front(t_list **lst, t_list *new);
int						ft_lstsize(t_list *lst);
t_list					*ft_lstlast(t_list *lst);
void					ft_lstadd_back(t_list **lst, t_list *new);
void					ft_lstdelone(t_list *lst, void (*del)(void *));
void					ft_lstclear(t_list **lst, void (*del)(void *));
void					ft_lstiter(t_list *lst, void (*f)(void *));
t_list					*ft_lstmap(t_list *lst, void *(*f)(void *),
							void (*del)(void *));

// Bloque 6: Get next line!

char					*get_next_line(int fd);
char					*ft_strjoin_free(char const *s1, char const *s2);

// Bloque 7: Recolector de basura (Garbage Collector)

/* Estructura de nodo para la lista de punteros del recolector de basura */
typedef struct s_mem_node
{
	void				*ptr;
	struct s_mem_node	*next;
}						t_mem_node;

/* Estructura para el seguimiento de descriptores de archivo */
typedef struct s_fd_list
{
	int					*fds;
	int					count;
	int					capacity;
}						t_fd_list;

/* Estructura principal del recolector de basura */
typedef struct s_gc
{
	t_mem_node			*mem_list;
	t_fd_list			fd_list;
}						t_gc;

/* Funciones básicas del recolector de basura */
void					gc_init(t_gc *gc);
void					*gc_malloc(t_gc *gc, size_t size);
void					gc_free(t_gc *gc, void *ptr);
void					gc_free_all(t_gc *gc);
void					gc_add(t_gc *gc, void *ptr);
int						gc_remove(t_gc *gc, void *ptr);

/* Funciones para manejo de descriptores de archivo */
void					gc_track_fd(t_gc *gc, int fd);
void					gc_close_fd(t_gc *gc, int fd);
void					gc_close_all_fds(t_gc *gc);

/* Funciones seguras de manejo de memoria */
char					*safe_strdup(t_gc *gc, const char *s);
void					*safe_calloc(t_gc *gc, size_t count, size_t size);
char					*safe_substr(t_gc *gc, char const *s,
							unsigned int start, size_t len);
char					*safe_strjoin(t_gc *gc, char const *s1, char const *s2);
void					safe_exit(t_gc *gc, int status);

#endif
