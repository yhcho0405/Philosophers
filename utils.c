/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youncho <youncho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 10:30:39 by youncho           #+#    #+#             */
/*   Updated: 2021/07/11 03:16:15 by youncho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
**	< atoi_positive >
**
**	if not 1 <= num <= INTMAX
**	then return 0
*/
int	atoi_positive(const char *str)
{
	uint64_t	ans;
	size_t		len;

	ans = 0;
	while ((9 <= *str && *str <= 13) || *str == ' ')
		str++;
	if ((*str == '-' || *str == '+') && *(str++) == '-')
		return (0);
		len = 0;
	while (str[len])
		len++;
	if (len > 10 || len == 0)
		return (0);
	while ('0' <= *str && *str <= '9')
		ans = ans * 10 + *(str++) - '0';
	if (*str || (int64_t)INT_MAX < (int64_t)ans)
		return (0);
	return (ans);
}
