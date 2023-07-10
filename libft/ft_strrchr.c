/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedgonca <pedgonca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:43:51 by pedgonca          #+#    #+#             */
/*   Updated: 2023/03/06 19:06:52 by pedgonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char			*last;

	last = NULL;
	while (*str)
	{
		if (*str == (unsigned char) c)
			last = (char *) str;
		str++;
	}
	if (*str == (unsigned char) c)
		last = (char *) str;
	return (last);
}
