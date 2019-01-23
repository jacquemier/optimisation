/***************************************
	Auteur : Pierre Aubert
	Mail : aubertp7@gmail.com
	Licence : CeCILL-C
****************************************/

#include "get_cycles.h"

#ifdef __i386
///Fonction qui renvoie le nombre de cycles depuis le début du programme
/**	@return nombre de cycles depuis le début du programme
*/
extern long unsigned int rdtsc(void) {
	long unsigned int x;
	__asm__ volatile ("rdtsc" : "=A" (x));
	return x;
}
#elif defined __amd64
///Fonction qui renvoie le nombre de cycles depuis le début du programme
/**	@return nombre de cycles depuis le début du programme
*/
extern long unsigned int rdtsc(void) {
	long unsigned int a, d;
	__asm__ volatile ("rdtsc" : "=a" (a), "=d" (d));
	return (d<<32) | a;
}
#endif


