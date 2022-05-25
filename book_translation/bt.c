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

#define MAX_TARGETS 100
#define MAX_TRANSLATORS 4500



int main() {
	printf("Max target languages: %d\nMax translators: %d\n", MAX_TARGETS, MAX_TRANSLATORS);

	return EXIT_SUCCESS;
}

