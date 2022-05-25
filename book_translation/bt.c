/*================================================================================
 *                              Book Translation
 * DMOJ problem ecna16d
 *
 * You want a book translated into n target languages. You've found m translators.
 * Each knows how to translate between two languages for a given cost c. To reach
 * a given target language may require multiple translations. For example, if you
 * want to translate between English and Bengali, but there is no tranlator for
 * these languages, so you have to translate from English to Spanish then Spanish
 * to Bengali. Your goal is to minimize the number of translations to a target
 * language; if there are multiple, choose the one with minimum total cost.
 *
 * Input: one test case with the following lines:
 *         1. A line with 2 integers n and m. n is the number of target languages
 *             and m is the number of translators.
 *         2. A line containing n strings, each naming a target languagle (English
 *             is the starting language and will not be in n)
 *         3. m lines, each giving information for one translator. Each contains
 *             three space-sparated tokens: a language, a second language, and a
 *             positive integer cost to translate between them. At most one
 *             translator per pair of languages.
 *
 * Output: the minimum monetary cost to translate the book into all of the target
 *         languages while minimizing the number of translations to each.
 *         If there is no way to translate the book into all of the target
 *         languages, output "Impossible".
 *
 *==============================================================================*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LANGS 101
#define WORD_LENGTH 16
#define MAX_TRANSLATORS 4500

typedef struct edge {
	int to_lang, cost;
	struct edge *next;
} edge;

typedef int board[MAX_LANGS];
typedef int positions[MAX_LANGS];

char *read_word(int size);

int main(void) {
	static edge *adj_list[MAX_LANGS] = {NULL};
	static char *lang_names[MAX_LANGS];
	int i, num_targets, num_translators, cost, from_index, to_index;
	char *from_lang, *to_lang;
	edge *e;
	static board min_costs;
	scanf("%d %d\n", &num_targets, &num_translators);
	lang_names[0] = "English";

	for (i = 1; i <= num_targets; i++)
		lang_names[i] = read_word(WORD_LENGTH);

	for (i = 0; i < num_translators; i++) {
		from_lang = read_word(WORD_LENGTH);
		to_lang = read_word(WORD_LENGTH);
		scanf("%d\n", &cost);
		from_index = find_lang(lang_names, from_lang);
		to_index = fing_lang(lang_names, to_lang);
		e = malloc(sizeof(edge));
		if (e == NULL) {
			fprintf(stderr, "malloc error\n");
			exit(EXIT_FAILURE);
		}
		e->to_lang = to_index;
		e->cost = cost;
		e->next = adj_list[from_index];
		adj_list[from_index] = e;
		e = malloc(sizeof(edge));
		if (e == NULL) {
			fprintf(stderr, "malloc error\n");
			exit(EXIT_FAILURE);
		}
		e->to_lang = from_index;
		e->cost = cost;
		e->next = adj_list[to_index];
		adj_list[to_index] = e;
	}
	find_distances(adj_list, num_targets + 1, min_costs);
	solve(num_targets + 1, min_costs);

	return EXIT_SUCCESS;
}

char *read_word(int size) {
	char *str;
	int ch;
	int len = 0;
	str = malloc(size);
	if (str == NULL) {
		fprintf(stderr, "malloc error\n");
		exit(EXIT_FAILURE);
	}
	while ((ch = getchar()) != EOF && (ch != ' ') && (ch != '\n')) {
		str[len++] = ch;
		if (len == size) {
			size = size * 2;
			str = realloc(str, size);
			if (str == NULL) {
				fprintf(stderr, "realloc error\n");
				exit(EXIT_FAILURE);
			}
		}
	}
	str[len] = '\0';
	return str;
}
