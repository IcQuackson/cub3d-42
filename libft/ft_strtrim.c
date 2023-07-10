/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedgonca <pedgonca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 14:47:54 by pedgonca          #+#    #+#             */
/*   Updated: 2023/03/06 19:06:52 by pedgonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	ft_is_in_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed;
	char	*t_cpy;
	int		trimmed_len;
	int		i;
	int		j;

	i = 0;
	while (s1[i] && ft_is_in_set(s1[i], set))
		i++;
	j = ft_strlen(s1) - 1;
	while (j >= i && ft_is_in_set(s1[j], set))
		j--;
	trimmed_len = j - i + 1;
	trimmed = malloc((trimmed_len + 1) * sizeof(char));
	if (trimmed == NULL)
		return (NULL);
	t_cpy = trimmed;
	while (trimmed_len--)
		*t_cpy++ = s1[i++];
	*t_cpy = '\0';
	return (trimmed);
}
