/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_extention.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:03:42 by aderison          #+#    #+#             */
/*   Updated: 2024/07/17 14:51:01 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_bool	file_extention(const char *path, const char *ext)
{
	int		word_len;
	int		ext_len;
	char	**tab;
	int		i;

	ext_len = ft_strlen(ext);
	tab = ft_split(path, '/');
	if (!tab || !*tab)
		return (false);
	i = -1;
	while (tab[++i])
	{
		word_len = ft_strlen(tab[i]);
		if (ft_strnstr(tab[i], ".ber", word_len))
			if (word_len > ext_len)
				return (true);
	}
	ft_free_matrice(1, &tab);
	return (false);
}
