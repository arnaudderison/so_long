/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_snprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 22:31:51 by aderison          #+#    #+#             */
/*   Updated: 2024/08/19 22:32:25 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_numlen(int n)
{
	int	len;

	len = (n <= 0);
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	ft_putnbr_str(int n, char *str, int *i)
{
	if (n == -2147483648)
	{
		ft_putnbr_str(-214748364, str, i);
		str[(*i)++] = '8';
		return ;
	}
	if (n < 0)
	{
		str[(*i)++] = '-';
		n = -n;
	}
	if (n >= 10)
		ft_putnbr_str(n / 10, str, i);
	str[(*i)++] = n % 10 + '0';
}

static int	ft_vsnprintf(char *str, size_t size, const char *format, va_list ap)
{
	int	i;
	int	ret;
	int	n;

	i = 0;
	ret = 0;
	while (*format && (size_t)i < size - 1)
	{
		if (*format == '%' && *(format + 1) == 'd')
		{
			n = va_arg(ap, int);
			ret += ft_numlen(n);
			if ((size_t)(i + ft_numlen(n)) < size)
				ft_putnbr_str(n, str, &i);
			format += 2;
		}
		else
			str[i++] = *format++;
	}
	str[i] = '\0';
	return (ret);
}

int	ft_snprintf(char *str, size_t size, const char *format, ...)
{
	va_list	ap;
	int		ret;

	va_start(ap, format);
	ret = ft_vsnprintf(str, size, format, ap);
	va_end(ap);
	return (ret);
}
