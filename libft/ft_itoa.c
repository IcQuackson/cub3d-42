/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedgonca <pedgonca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 19:44:48 by pedgonca          #+#    #+#             */
/*   Updated: 2023/03/06 19:05:53 by pedgonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static char	*reverse(char *s)
{
	int		length;
	int		c;
	int		i;
	int		j;

	length = ft_strlen(s);
	i = 0;
	j = length - 1;
	while (i < j)
	{
		c = s[i];
		s[i] = s[j];
		s[j] = c;
		i++;
		j--;
	}
	return (s);
}

static int	count_digits(int n)
{
	int		n_digits;

	n_digits = 0;
	if (n == 0)
		n_digits = 1;
	while (n != 0)
	{
		n /= 10;
		n_digits++;
	}
	return (n_digits);
}

static char	*putnbr(int n, char *str, int sign)
{
	int		i;

	i = 0;
	if (n == 0)
		str[i++] = '0';
	while (n != 0)
	{
		str[i] = n % 10 + '0';
		n /= 10;
		i++;
	}
	if (sign == -1)
		str[i++] = '-';
	str[i] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	int		n_digits;
	int		sign;
	char	*str;

	n_digits = count_digits(n);
	sign = 1;
	if (n < 0)
	{
		str = malloc((n_digits + 2) * sizeof(char));
		if (n == -2147483648)
		{
			ft_memcpy(str, "-2147483648", 12);
			return (str);
		}
		sign = -1;
		n = -n;
	}
	else
		str = malloc((n_digits + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str = putnbr(n, str, sign);
	return (reverse(str));
}
