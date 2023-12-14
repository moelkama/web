/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moelkama <moelkama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 14:04:34 by moelkama          #+#    #+#             */
/*   Updated: 2023/12/12 17:43:10 by moelkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

int	ft_find_charset(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_count_strs(char *str, char *charset)
{
	int	count_strs;
	int	m;

	count_strs = 0;
	while (*str)
	{
		while (*str && ft_find_charset(*str, charset))
			str++;
		m = 0;
		while (*str && !ft_find_charset(*str, charset))
		{
			m = 1;
			str++;
		}
		if (m == 1)
			count_strs++;
	}
	return (count_strs);
}

char	**ft_split(char *str, char *charset)
{
	char	**strs;
	int		count_strs;
	int		index;
	int		i;
	int		j;

	count_strs = ft_count_strs(str, charset);
	strs = new char*[count_strs + 1]();
	i = 0;
	while (i < count_strs)
	{
		while (*str && ft_find_charset(*str, charset))
			str++;
		j = 0;
		while (str[j] && !ft_find_charset(str[j], charset))
			j++;
		strs[i] = new char[j + 1];
		index = 0;
		while (index < j)
			strs[i][index++] = *(str++);
		strs[i][index] = '\0';
		i++;
	}
	strs[i] = 0;
	return (strs);
}
int	main(int c, char **v){char **ptr = ft_split(v[1], v[2]);while (ptr && *ptr){std::cout<<*(ptr++)<<std::endl;}}
