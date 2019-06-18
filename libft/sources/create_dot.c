/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_dot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnovikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 11:12:13 by nnovikov          #+#    #+#             */
/*   Updated: 2019/06/15 11:12:17 by nnovikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dot   create_dot(int x, int y)
{
    t_dot dot;

    dot.x = x;
    dot.y = y;
    return (dot);
}
