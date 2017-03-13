#ifndef GLOBAL_H
#define GLOBAL_H

// Hmm... Je n'aime pas vraiment 'global' comme nom de fichier. C'est
// du même acabit que 'misc', 'util', 'stuff'...

// À moins qu'ils ne soient requis dans le .h lui-même, il vaut mieux
// éviter des inclusions dans les .h. Les .h sont des fichiers de
// déclarations, et ne devraient pas contenir quoi que ce soit
// d'autre. La raison est que tu ne peux pas savoir à l'avance où un
// .h va être inclus (peut-être que quelqu'un l'utilisera dans son
// projet, peut-être que TON projet va grandir et que tu en auras
// besoin dans des .c dont tu n'as même pas encore idée, etc. Je sais,
// ce n'est pas le cas ici, mais les bonnes habitudes se cultivent au
// plus tôt.)

// Ici, ce sont des headers standards, donc ça va encore. Mais fais
// attention, car si jamais un de ces fichiers venait à changer, alors
// tu auras à recompiler tous tes .c qui incluent 'global.h', et vu
// son nom et utilisation, ça risque de faire pas mal de temps de
// recompilation. Si je ne suis pas assez clair, on peut en reparler
// de vive voix.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <ctype.h>
#include <err.h>

// C'est un peu overkill de définir ça ici alors qu'il n'est utilisé
// quand dans 'main.c'. Mais l'intention est correcte.
#define FILENAME "data/S_pombe.fasta"
// Très bonne idée ces 'define'. Cependant, pour illustrer mon pavé du
// dessus, si jamais tu passes en "mode" debug, tu vas recompiler TOUS
// tes fichiers qui dépendent de 'global.h', alors que le seul fichier
// impacté par un changement de DEBUG_SEQUENCES est 'sequences.c'
#define DEBUG_SEQUENCES 0 // La sortie peut être longue car affiche toutes les séquences
// Idem ici, DEBUG_SEARCH n'est utilisé que dans 'start.c', or tu vas
// tout recompiler si tu changes sa valeur ici.
#define DEBUG_SEARCH 1
// Évite les abbréviations. Description je suppose, mais peut être
// autre chose ('DESC' est un mot-clef en SQL). Aussi, description de
// quoi? What if tu as un autre 'truc' dont tu veux définir la taille
// de description? Je sais que c'est du C, mais inutile d'être avare
// en caractères: mieux vaut être lisible.
#define DESC_SIZE 154
// Idem... le header de quoi?
#define HEADER_SIZE 274
#define SEQ_LINE_SIZE 60
#define EXIT_FAILURE 1

// J'apprécie l'effort de typage, mais c'est un peu overkill. Le C te
// propose déjà un 'false' qui est 0 et un 'true' qui est !0. En plus,
// c'est assez dangereux car si tu inverses l'ordre de déclaration
// (ie. TRUE en premier), alors 'if TRUE' devient 'if 0'... Tu peux
// éventuellement "forcer" la valeur en écrivant 'FALSE = 0', mais
// bon... Tu rajoutes une couche qui n'en vaut pas vraiment la peine.
// Et aussi, gaffe à l'utilisation des enums. Il ne faut EN AUCUN CAS
// s'en servir pour effectuer des opérations arithmétiques (s'en
// servir comme des int classiques). Je peux t'en parler plus
// longuement IRL.
typedef enum { FALSE, TRUE } bool;

// Pourquoi suffixer par '_t'? Les enums sont généralement suffixées par '_e';
enum chromosome_t {I, II, III, MT, MTR, AB325691};

// ENGLISH MOTHERFUCKER!! DO YOU SPEAK IT?!??!
// Non sérieusement... Anglais... Pour l'amour du ciel
typedef struct seq {
	char nom[17]; // le nom de la sequence sans le '>' initial, termine par '\0'
	enum chromosome_t chromosome;
	int deb; // numero de base de debut
	int fin; // et de fin
	char *description; // copie de la chaine "description"
	char *sequence;    // toute la sequence sur {A,C,G,T}  sans '\n' terminee par '\0'
	struct seq *suiv;  // pour faire une liste chainee. NULL si dernier.
} Seq;

// Nom à revoir.
typedef struct arg {
	char *searchDico; // séquence à rechercher dans le dico
	char *search; // chaine à rechercher dans les séquences
  // 32 bit pour ça? un simple 'unsigned int' ne pourrait-il pas suffire?
	uint32_t occ; // nombre d'occurences
	uint32_t transl; // valeur pour choix de traduction
} Arg;




#endif
