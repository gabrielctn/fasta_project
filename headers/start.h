#ifndef START_H
#define START_H

void display_usage();
void freeArg(Arg *args);
void parseCommandLine(int argc, char *argv[], struct arg *args);

#endif
