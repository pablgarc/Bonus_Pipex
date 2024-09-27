/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablgarc <pablgarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 11:45:02 by pablgarc          #+#    #+#             */
/*   Updated: 2024/09/22 11:45:06 by pablgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

size_t	ft_strlen_gnl(const char *s, char stop);
size_t	ft_strlcat_gnl(char *dst, const char *src, size_t size);
char	*ft_joindup(char *s1, char *s2, size_t size, int free_s);
int		check(char **line);
char	*update_line(char **line, int size);
int		initialize_line(int fd, char **line, char **buf);
int		read_and_process(int fd, char **line, char **buf, int *ret);
char	*get_next_line(int fd);

#endif
