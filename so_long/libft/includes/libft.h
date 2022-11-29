/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 11:15:57 by albaur            #+#    #+#             */
/*   Updated: 2022/11/15 16:28:01 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdint.h>
# include <errno.h>
# include <stdio.h>

# define BUFFER_SIZE 50

typedef struct s_list
{
	void			*content;
	struct s_list	*prev;
	struct s_list	*next;
}					t_list;

typedef struct s_node
{
	void			*content;
	struct s_node	*prev;
	struct s_node	*next;
}					t_node;

typedef struct s_stack
{
	size_t			length;
	struct s_node	*top;
	struct s_node	*bottom;
}					t_stack;

// arr
int		ft_arrlen(char **array);
char	**ft_arrjoin(char **arr1, char **arr2);
char	**ft_arrdup(char **arr);
char	**ft_arrndup(char **str, int i);
char	**ft_arrstrndup(char **str, int i);
char	**ft_arrdup_before(char **str, char *name);
char	**ft_arrdup_after(char **str, char *name);
void	ft_arr_freer(char **str);
void	free_uint_arr(uint32_t **arr, size_t size);
char	**ft_arr_freer_index(char **arr, size_t index);
int		**free_int_arr_index(int **arr, size_t index);
double	**free_double_arr_index(double **arr, size_t index);
void	**free_void_arr_index(void **arr, size_t index);
void	ft_arr_display(char **arr);
void	ft_print_int_arr(int **arr, size_t height, size_t width);
void	ft_print_double_arr(double **arr, size_t height, size_t width);

// gnl
char	*get_next_line(int fd);
char	*gnl_strchr(char *s, int c);
char	*gnl_strjoin(char *keep, char *buff);

// is
int		ft_isalpha(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_isspace(int c);

// lst
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	ft_lstsort(t_list **begin_list, int (*cmp)());
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));

// mem
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memset(void *b, int c, size_t len);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memsalloc(size_t count, size_t size, int c);

// put
int		ft_putstr(char *str);
int		ft_putptr(unsigned long long ptr);
int		ft_putnbr(int nb);
int		ft_putchar(int c);
int		ft_itohex(unsigned int num, const char format);
int		ft_putint_unsigned(unsigned int n);
void	ft_putchar_fd(char c, int fd);

// str
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_tolower(int c);
int		ft_toupper(int c);
int		ft_atoi(const char *str);
int		ft_strtololo(const char *str);
int		ft_intlen(long n);
int		ft_dectobin(long nb);
int		ft_getlastint(int i);
int		ft_printf(const char *str, ...);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strrchr(const char *s, int c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strcpy(char *dest, char *src);
char	*ft_itoa(int n);
char	*ft_strcat(char *dest, char *src);
char	*ft_concat(char *s1, char *s2);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(const char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
char	*ft_strstr(const char *haystack, const char *needle);

//error
void	throw_error(char *msg, int err);
int		ret_err(char *str, char *str2, int i);
void	ret_null(char *str, char *str2);
void	ft_puterror(const char *str);
void	throw_err_ex(const char *str);

// Doubly linked list functions
t_stack	*ft_stacknew(void);
t_stack	*ft_stackadd_top(t_stack *stack, t_node *new);
t_stack	*ft_stackadd_bottom(t_stack *stack, t_node *new);
t_stack	*ft_stackinsert(t_stack *stack, t_node *node, int position);
t_node	*ft_newnode(void *content);
void	ft_stackdelone(t_stack *stack, t_node *node, void (*del)(void *));
void	ft_stackclear(t_stack *stack, void (*del)(void *));
void	ft_stackiter(t_stack *stack, void (*f)(void *));
void	ft_stacksort(t_stack *begin_list, int (*cmp)());
void	ft_stackiter_if(t_stack *stack, void (*f)(void *), void *data_ref,
			int (*cmp)());
void	ft_stack_remove_if(t_stack *begin_list, void *data_ref, int (*cmp)());
int		ft_stacksize(t_stack *stack);
char	**ft_create_chartab(t_stack *stack);
t_stack	*ft_charr_to_stack_converter(char **arr);
int		ft_stacklen(t_stack *stack);
int		ft_stacktablen(t_stack **stack);
void	node_del(t_node *node, t_stack **av);

#endif
