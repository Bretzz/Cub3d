/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yft.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 02:09:18 by totommi           #+#    #+#             */
/*   Updated: 2025/06/21 17:56:37 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef YFT_H
# define YFT_H

/* The idea is that you can load up your font, and the function will create
an mlx image with the string passed using your font. Your choice of what
to do with that image (similar to xpm functions) */

/* import your font */
int		yft_is_better(const char *path);

/* get a sprite like image as in 'xmp_file_to_image' */
void	*yft_string_to_image(void *mlx_ptr, const char *font_name,
			const char *string, int scale);

/* puts the string directly on the image passed */
int		yft_string_put(void *img_ptr, int x, int y, const char *string);

#endif