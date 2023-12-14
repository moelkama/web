/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moelkama <moelkama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 17:17:18 by moelkama          #+#    #+#             */
/*   Updated: 2023/01/27 11:51:01 by moelkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlenf(char *str, char c)
{
	int	len;

	len = 0;
	while (str && str[len])
	{
		if (str[len] == c)
			return (len + 1);
		len++;
	}
	return (len);
}

char	*get_next_line(int fd)
{
	static char	*ptr;
	char		*str;
	char		*swp1;
	char		*swp;

	str = (char *)malloc(BUFFER_SIZE * sizeof(char ) + sizeof(char ));
	if (str)
	{
		str[BUFFER_SIZE] = '\0';
		if (ptr && ft_check(ptr))
		{
			swp = ft_link(NULL, ptr);
			swp1 = ptr;
			ptr = ft_link(ptr + ft_strlenf(ptr, '\n'), NULL);
			ft_free(str, swp1);
			if (ft_strlenf(ptr, '\0') == 0)
				ptr = ft_free(ptr, NULL);
			return (swp);
		}
		ft_bezero(str);
		return (get_next_line2(&ptr, fd, &str, &swp));
	}
	return (NULL);
}
