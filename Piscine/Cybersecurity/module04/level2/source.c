/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:10:33 by albaur            #+#    #+#             */
/*   Updated: 2023/05/22 14:38:43 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

void	ok(void)
{
	puts("Good job.");
	return;
}

void	no(void)
{
	puts("Nope.");
	exit(1);
}

int	main(void)
{
  size_t		len;
  int			atoi_result;
  bool			bool_result;
  char			ascii_str[4];
  char			scanf_str[24];
  char			str[9];
  unsigned int	i;
  int			j;
  int			scanf_return;
  unsigned int	unsigned_index_compare;
  
  printf("Please enter key: ");
  scanf_return = scanf("%s", scanf_str);
  if (scanf_return != 1) {
    no();
  }
  if (scanf_str[1] != '0') {
    no();
  }
  if (scanf_str[0] != '0') {
    no();
  }
  fflush(STDIN_FILENO);
  memset(str,0,9);
  str[0] = 'd';
  ascii_str[3] = 0;
  i = 2;
  j = 1;
  while( true ) {
    len = strlen(str);
    unsigned_index_compare = i;
    bool_result = false;
    if (len < 8) {
      len = strlen(scanf_str);
      bool_result = unsigned_index_compare < len;
    }
    if (!bool_result)
		break;
    ascii_str[0] = scanf_str[i];
	ascii_str[1] = scanf_str[i + 1];
	ascii_str[2] = scanf_str[i + 2];
    atoi_result = atoi(ascii_str);
    str[j] = (char)atoi_result;
    i = i + 3;
    j = j + 1;
  }
  str[j] = '\0';

  atoi_result = strcmp(str,"delabere");
  if (atoi_result == 0) {
    ok();
  }
  else {
    no();
  }
  return 0;
}