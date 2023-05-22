/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   source.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:18:08 by albaur            #+#    #+#             */
/*   Updated: 2023/05/22 15:20:09 by albaur           ###   ########.fr       */
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
	int atoi_result;
	size_t len;
	bool bool_result;
	char str [4];
	char scanf_str [31];
	char stars_str [9];
	unsigned long i;
	int strcmp_result;
	int j;
	int scanf_return;
	unsigned long unsigned_index_compare;

	printf("Please enter key: ");
	scanf_return = scanf("%s", scanf_str);
	if (scanf_return != 1) {
	  no();
	}
	if (scanf_str[1] != '2') {
	  no();
	}
	if (scanf_str[0] != '4') {
	  no();
	}
	fflush(STDIN_FILENO);
	memset(stars_str,0,9);
	stars_str[0] = '*';
	str[3] = '\0';
	i = 2;
	j = 1;
	while( true ) {
	  len = strlen(stars_str);
	  unsigned_index_compare = i;
	  bool_result = false;
	  if (len < 8) {
	    len = strlen(scanf_str);
	    bool_result = unsigned_index_compare < len;
	  }
	  if (!bool_result) break;
	  str[0] = scanf_str[i];
	  str[1] = scanf_str[i + 1];
	  str[2] = scanf_str[i + 2];
	  atoi_result = atoi(str);
	  stars_str[j] = (char)atoi_result;
	  i = i + 3;
	  j = j + 1;
	}
	stars_str[j] = '\0';
	strcmp_result = strcmp(stars_str,"********");
	if (strcmp_result == -2) {
	  no();
	}
	else if (strcmp_result == -1) {
	  no();
	}
	else if (strcmp_result == 0) {
	  ok();
	}
	else if (strcmp_result == 1) {
	  no();
	}
	else if (strcmp_result == 2) {
	  no();
	}
	else if (strcmp_result == 3) {
	  no();
	}
	else if (strcmp_result == 4) {
	  no();
	}
	else if (strcmp_result == 5) {
	  no();
	}
	else if (strcmp_result == 0x73) {
	  no();
	}
	else {
	  no();
	}
	return 0;
}