#ifndef ASSEMBLY_H
#define ASSEMBLY_H

typedef struct read{
    char *read;
    int level;
} Read;


unsigned int generateRandom(int max);
Read *generateReads(Sequences *seq, size_t seqLength);
int maxLevelRead(Read *totalReads);
Read *mapReads(Sequences *seq);
size_t seekOverlap(char *readA, char *prefix, int index, Read *totalReads);
int overlap(char *readA, char *prefix, Read *totalReads, int totalReads_idx);
void searchLevel(int level, int index, int *prochain, Read *totalReads);
char *assembleGenome(Sequences *seq);
bool checkAssembly(char *genome, char *seq);
void printProgress(int percentage);
void writeGenome(char *genome, Sequences *seq);
Sequences *searchSequenceToAssemble(char *seqChoice, Sequences *seq);
void freeReads(Read *totalReads);

#endif
