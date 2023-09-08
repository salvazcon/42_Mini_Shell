/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyacoub- <cyacoub-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 08:36:37 by cyacoub-          #+#    #+#             */
/*   Updated: 2023/09/06 11:12:45 by cyacoub-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	increment_shlvl(t_env **env)
{
	t_env	*tmp;
	int		i;

	tmp = get_env(*env, "SHLVL");
	if (!tmp)
	{
		set_env(env, "SHLVL", ft_itoa(1));
		return ;
	}
	i = ft_atoi(tmp->value);
	i++;
	set_env(env, "SHLVL", ft_itoa(i));
}
