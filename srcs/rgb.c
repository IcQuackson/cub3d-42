/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-per <joao-per@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 16:48:27 by joao-per          #+#    #+#             */
/*   Updated: 2023/08/15 16:48:42 by joao-per         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * The function "copy_into_rgb_array" takes an array of strings
 * representing RGB values, converts them
 * to integers, and stores them in an integer array.
 * 
 * @param rgb_to_convert A pointer to a pointer to a character array
 * (a 2D array of characters)
 * representing the RGB values to be converted.
 * @param rgb The parameter `rgb` is a pointer to an integer array.
 * 
 * @return a pointer to an integer array.
 */
int	*copy_into_rgb_array(char **rgb_to_convert, int *rgb)
{
	int		i;

	i = -1;
	while (rgb_to_convert[++i])
	{
		rgb[i] = ft_atoi(rgb_to_convert[i]);
		if (rgb[i] == -1 || no_digit(rgb_to_convert[i]) == 1)
		{
			free_tab((void **)rgb_to_convert);
			free(rgb);
			return (0);
		}
	}
	free_tab((void **)rgb_to_convert);
	return (rgb);
}

/**
 * The function "set_rgb" takes a string representing
 * RGB values separated by commas, splits the string
 * into an array, checks if there are exactly 3 values,
 * allocates memory for an integer array, and
 * copies the values from the string array into the integer array.
 * 
 * @param line A string representing an RGB color in the
 * format "R,G,B" where R, G, and B are integers
 * between 0 and 255.
 * 
 * @return a pointer to an integer array.
 */
int	*set_rgb(char *line)
{
	char	**rgb_to_convert;
	int		*rgb;
	int		count;

	rgb_to_convert = ft_split(line, ',');
	count = 0;
	while (rgb_to_convert[count])
		count++;
	if (count != 3)
	{
		free_tab((void **)rgb_to_convert);
		return (0);
	}
	rgb = malloc(sizeof(int) * 3);
	if (!rgb)
		return (0);
	return (copy_into_rgb_array(rgb_to_convert, rgb));
}
