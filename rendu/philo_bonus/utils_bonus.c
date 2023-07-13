/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 20:22:55 by rahmed            #+#    #+#             */
/*   Updated: 2022/01/30 20:23:25 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	atoi_lite(const char *str)
{
	size_t				i;
	unsigned long int	res;
	int					sign;

	i = 0;
	sign = 1;
	res = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign *= -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res *= 10;
		res += str[i++] - '0';
	}
	if (!((str[i] >= '0') && (str[i] <= '9')) && str[i] != '\0')
		return (0);
	return (res * sign);
}

char	*ft_itoa_lite(int n)
{
	int		len;
	int		nb;
	char	*str;

	nb = n;
	len = 1;
	while (nb >= 10)
	{
		nb /= 10;
		len++;
	}
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (n == 0)
		str[len - 1] = '0';
	str[len] = '\0';
	while (n > 0)
	{
		str[--len] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}

char	*ft_strjoin_del_str2(char const *s1, char *s2)
{
	char	*str;
	size_t	len_s1;
	size_t	len_s2;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	str = malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!str)
		return (NULL);
	while (i < len_s1)
		str[i++] = s1[j++];
	j = 0;
	while (i < (len_s1 + len_s2))
		str[i++] = s2[j++];
	str[len_s1 + len_s2] = '\0';
	free(s2);
	return (str);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	if (!s)
		return (0);
	while (s[len])
		len++;
	return (len);
}
