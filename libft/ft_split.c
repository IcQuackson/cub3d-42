/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedgonca <pedgonca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:00:57 by pedgonca          #+#    #+#             */
/*   Updated: 2023/03/06 19:06:47 by pedgonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	*ft_calloc_int(int nelem)
{
	int		*arr;
	int		i;

	arr = malloc(nelem * sizeof(int));
	if (arr == NULL)
		return (NULL);
	i = 0;
	while (i < nelem)
		arr[i++] = 0;
	return (arr);
}

static int	*get_word_count(int *word_count, char const *s, char c)
{
	int			*words_sizes;
	int			can_count;
	int			i;

	can_count = 1;
	i = 0;
	words_sizes = ft_calloc_int(ft_strlen(s));
	while (words_sizes != NULL && *s)
	{
		if (*s != c && can_count)
		{
			*word_count = *word_count + 1;
			can_count = 0;
		}
		else if (*s == c && !can_count)
		{
			can_count = 1;
			i++;
		}
		if (*s != c)
			words_sizes[i]++;
		s++;
	}
	return (words_sizes);
}

static char	**fill_words(char **split, int *words_sizes, char const *s, char c)
{
	int			i;
	int			can_count;

	i = 0;
	can_count = 1;
	while (split != NULL && *s)
	{
		if (*s != c && can_count)
		{
			split[i] = malloc((words_sizes[i] + 1) * sizeof(char));
			if (split[i] == NULL)
				return (NULL);
			ft_memcpy(split[i], s, words_sizes[i]);
			split[i][words_sizes[i]] = '\0';
			i++;
			can_count = 0;
		}
		else if (*s == c && !can_count)
			can_count = 1;
		s++;
	}
	split[i] = NULL;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char		**split;
	int			*words_sizes;
	int			word_count;

	word_count = 0;
	words_sizes = get_word_count(&word_count, s, c);
	split = malloc((word_count + 1) * sizeof(char *));
	if (split == NULL)
		return (NULL);
	fill_words(split, words_sizes, s, c);
	free(words_sizes);
	return (split);
}
