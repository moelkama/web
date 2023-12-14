/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moelkama <moelkama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 17:16:16 by moelkama          #+#    #+#             */
/*   Updated: 2023/01/18 09:17:57 by moelkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE

#  define BUFFER_SIZE 1

# endif

# include <stdlib.h>

# include <unistd.h>

char	*get_next_line(int fd);
char	*get_next_line2(char **ptr, int fd, char **str, char **swp);
char	*ft_free(char *s1, char *s2);
int		ft_check(char *str);
char	*ft_link(char *s1, char *s2);
int		ft_strlenf(char *str, char c);
void	ft_bezero(char *str);

#endif
