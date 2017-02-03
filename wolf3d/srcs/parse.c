/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malexand <malexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 11:50:43 by malexand          #+#    #+#             */
/*   Updated: 2017/02/03 18:00:59 by malexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static int			check_str(char *str)
{
	int		count;

	count = 0;
	while (str[count])
	{
		if (str[count] != '0' && str[count] != '1' && str[count] != '2'
				&& str[count] != '4' && str[count] != ' '
				&& str[count] != '\n')
			return (-1);
		count++;
	}
	if (count <= 8)
		return (-1);
	return (0);
}

static int			check_line(char *str)
{
	int		count;
	int		save;
	int		square;

	count = 0;
	save = 0;
	square = 0;
	while (str[count])
	{
		if (str[count] == '\n')
		{
			if (save == 0)
				save = count + 1;
			else
			{
				if ((count + 1) % save != 0)
					return (-1);
			}
			square++;
		}
		count++;
	}
	if (save / 2 != square || square > 50)
		return (-1);
	return (0);
}

static char			***parse_array_3d(char *str, char carac1, char carac2)
{
	int		len;
	int		count;
	char	**split;
	char	***parse;

	len = 0;
	count = 0;
	split = ft_strsplit(str, carac1);
	while (split[len])
		len++;
	parse = (char ***)ft_memalloc(sizeof(*parse) * (len + 1));
	while (count < len)
	{
		parse[count] = ft_strsplit(split[count], carac2);
		ft_strdel(&split[count]);
		count++;
	}
	parse[count] = NULL;
	free(split);
	return (parse);
}

static char			*take_str(char *av, char *str)
{
	int		fd;
	int		ret;
	char	*tmp;

	fd = 0;
	ret = 0;
	str = (char*)malloc(sizeof(char));
	str[0] = '\0';
	if ((fd = open(av, O_RDONLY)) < 0)
		error(1, 1, "");
	while ((ret = get_next_line(fd, &tmp)) == 1)
	{
		str = ft_strjoin_free(str, tmp);
		str = ft_strjoin_free(str, "\n");
		ft_strdel(&tmp);
		if (check_str(str) == -1)
			return (NULL);
	}
	if (str[0] == '\0')
		error(1, 0, "Map empty!");
	if (ret == -1)
		error(1, 1, "");
	if (close(fd) < 0)
		error(1, 1, "");
	return (str);
}

char				***get_map(t_map **map, char *file)
{
	int		x;
	int		y;
	char	*str;

	str = NULL;
	x = 0;
	str = take_str(file, str);
	if (str == NULL || check_line(str) == -1)
		error(1, 0, "Bad map format!");
	(*map)->mapget = parse_array_3d(str, '\n', ' ');
	ft_strdel(&str);
	while ((*map)->mapget[x])
	{
		y = 0;
		while ((*map)->mapget[x][y])
			y++;
		x++;
	}
	(*map)->x = x;
	(*map)->y = y;
	if ((*map)->mapget == NULL)
		error(1, 0, "Bad parsing!");
	(void)file;
	return ((*map)->mapget);
}
