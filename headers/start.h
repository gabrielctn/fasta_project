#ifndef START_H
#define START_H

// Sois consistent. camelCase ou snake_case?
void display_usage();
// Attention, 'Arg' n'est pas déclaré ici. Si jamais tu te loupes dans
// l'ordre de tes inclusions dans tes .c, tu auras une erreur de
// compilation.
void freeArg(Arg *args);
// Hmm... 'Arg' ou 'struct arg'? Aussi, cette fonction aurait plus de
// sens dans 'main.c' puisque ce n'est pas vraiment une fonction que
// tu vas utiliser dans ton code "métier".
void parseCommandLine(int argc, char *argv[], struct arg *args);

#endif
