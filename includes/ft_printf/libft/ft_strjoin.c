/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 11:32:19 by thuynguy          #+#    #+#             */
/*   Updated: 2022/11/02 11:44:50 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len1;
	int		len2;
	int		ret;
	char	*res;

	if (!s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	ret = len1 + len2 + 1;
	res = (char *) malloc(sizeof(*s1) * ret);
	if (!res)
		return (NULL);
	ft_memmove(res, s1, len1);
	res[len1] = '\0';
	ft_strlcat(res, s2, ret);
	return (res);
}
