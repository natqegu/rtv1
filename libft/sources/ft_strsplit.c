/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnovikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 13:48:46 by nnovikov          #+#    #+#             */
/*   Updated: 2018/10/31 13:41:30 by nnovikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_word_len(char const *s, char c)
{
	int i;
	int k;

	i = 0;
	k = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			k++;
			i++;
		}
	}
	return (k);
}

int		ft_count_words(char const *s, char c)
{
	int i;
	int w;
	int k;

	i = 0;
	w = 0;
	k = 0;
	while (s[i])
	{
		if (!k && s[i] != c)
		{
			k = 1;
			w++;
		}
		if (k && s[i] == c)
			k = 0;
		i++;
	}
	return (w);
}

char	**ft_strsplit(char const *s, char c)
{
	int		i;
	int		k;
	int		j;
	char	**arr;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	if (!(arr = (char **)malloc(sizeof(char *) * (ft_count_words(s, c) + 1))))
		return (NULL);
	while (i < ft_count_words(s, c))
	{
		k = 0;
		if (!(arr[i] = ft_strnew(ft_word_len(&s[j], c))))
			arr[i] = NULL;
		while (s[j] == c)
			j++;
		while (s[j] != c && s[j])
			arr[i][k++] = s[j++];
		i++;
	}
	arr[i] = 0;
	return (arr);
}
