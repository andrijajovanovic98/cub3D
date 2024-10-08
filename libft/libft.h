/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgebetsb <bgebetsb@students.42vienna.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:06:56 by bgebetsb          #+#    #+#             */
/*   Updated: 2024/09/20 13:40:55 by bgebetsb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <limits.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdio.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int				ft_atoi(const char *nptr);
void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t nmemb, size_t size);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);
void			*ft_memset(void *s, int c, size_t n);
char			*ft_strchr(const char *s, int c);
char			*ft_strdup(const char *s);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
size_t			ft_strlen(const char *s);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strnstr(const char *big, const char *little, size_t len);
char			*ft_strrchr(const char *s, int c);
int				ft_tolower(int c);
int				ft_toupper(int c);
char			*ft_strtrim(char const *s1, char const *set);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			**ft_split(char const *s, char c);
char			*ft_itoa(int n);
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **lst, t_list *new);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));
void			free_stuff(char **splitted, size_t word_index);

// GNL
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 128
# endif

bool			get_next_line(int fd, char **line, bool freeing);
char			*gnl_strjoin(char *str1, char *str2);
size_t			gnl_strlen(char *str);

// stringlist
typedef struct s_strbuf
{
	char	*buf;
	size_t	length;
}	t_strbuf;

typedef struct s_string
{
	t_list	*buffers;
	size_t	total_length;
	size_t	items;
	size_t	max_length;
}	t_string;

char			*string_get(t_string *str);
t_string		*string_append(t_string *str, char *new, size_t length);
char			**string_to_array(t_string *str);
void			string_clear(t_string **str);
void			strlist_delete_content(void *content);

// ft_printf

typedef struct s_properties
{
	char	type;
	char	*flags;
	int		width;
	int		precision;
}	t_properties;

typedef struct s_chars
{
	char	*charset;
	char	*prefix;
}	t_chars;

int				ft_printf(int fd, const char *format, ...);
char			*ft_itoa_base(size_t n, t_properties *properties, t_chars c);
char			*ft_itoa_printf(int n, t_properties *properties);
t_properties	*parse_format(const char **format, va_list *args);
void			handle_pointer(t_string **string,
					t_properties *prop, va_list *args);
void			handle_hex(t_string **string, t_properties *properties,
					va_list *args);
void			handle_uint(t_string **string, t_properties *properties,
					va_list *args);
void			handle_int(t_string **string, t_properties *properties,
					va_list *args);
void			handle_string(t_string **string, t_properties *prop,
					va_list *args);
void			handle_char(t_string **string, t_properties *properties,
					va_list *args);
void			handle_percent(t_string **string);

#endif
