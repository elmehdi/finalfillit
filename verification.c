/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verification.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elfetoua <elfetoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 17:54:49 by elfetoua          #+#    #+#             */
/*   Updated: 2019/07/05 22:02:39 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int	dashes_per_bloc(char *file)
{
	int		fd;
	int		i;
	int		dash_cnt;
	char	*line;

	fd = open(file, O_RDONLY);
	i = 1;
	while (get_next_line(fd, &line))
	{
		if (i == 1)
			dash_cnt = 0;
		while (*line)
		{
			if (*line == '#')
				dash_cnt++;
			line++;
		}
		i++;
		if (i / 5 == 1 && dash_cnt != 4)
			return (0);
		if (i / 5 == 1 && dash_cnt == 4)
			i = 0;
	}
	close(fd);
	return (1);
}

int	verification(char *file)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	if (verifi(fd) == 0)
		return (0);
	close(fd);
	if (dashes_per_bloc(file) == 0)
		return (0);
	return (1);
}

int	verifi(int fd)
{
	int		i;
	char	*line;
	int		j;

	i = 1;
	while (get_next_line(fd, &line))
	{
		if ((ft_strlen(line) != 4 && i % 5 != 0) ||
			(ft_strlen(line) != 0 && i % 5 == 0))
			return (0);
		j = 0;
		if (i % 5 != 0)
		{
			while (line[j])
			{
				if (!ft_strchr(".#", line[j]))
					return (0);
				j++;
			}
		}
		i++;
	}
	if (i % 5 != 0)
		return (0);
	return (1);
}

int	check(char **str)
{
	int		i;
	int		j;
	char	c;
	int		dash_cnx;

	c = character(str);
	i = 0;
	j = 0;
	dash_cnx = cnx_count(str, i, j, c);
	if (dash_cnx == 3 || dash_cnx == 4)
		return (1);
	return (0);
}

int	cnx_per_bloc(char ***str, int num_tit)
{
	int		i;

	i = 0;
	while (i < num_tit)
	{
		if (check(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}
