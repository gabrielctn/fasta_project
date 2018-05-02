[![Build Status](https://travis-ci.org/gabrielctn/fasta_project.svg?branch=master)](https://travis-ci.org/gabrielctn/fasta_project)

# C Project: FASTA sequences manipulation

This project is about working on protein and nucleic sequences, stored in FASTA formatted files, in order to make specific searches (by gene name, sequence, position in the genome and sub-string), translations and later calculate distances or make sequencing simulations.

## Authors

Sophie LEMATRE & Gabriel CRETIN

## Install and execute

Compilation:

`make`

Clean *.o files:

`make clean`

Clean *.o and executable file:

`make wipeout`

Execute project:

`./fasta_project`

## Implemented functions

**Search by:**

- Gene name
- Sequence
- Position in the genome
- Sub sequence (e.g. search for sequences having this kind of regex patern: `[ATCG].*[ATCG].*[ATCG] etc`)

**Search in the dictionary-tree:**

- Full sequences
- Number of sequences starting by a given prefix

**Translation:**

Nucleic sequences are translated into their proteic sequences. Output is in `data/translation.txt`

**Assembly:**

Give the header (or a particular element of the header that is a unique identificator of that sequence) to the program and it will simulate a sequencing followed by an assembly *de novo*.
The goal is to align and merge fragments (randomly generated) of this sequence in order to reconstruct the original sequence.
You can set different parameters to change the assembly precision and number of reads:
`NB_NUCL` : average time of apparition of each base.
`READ_LENGTH` : size of each read created *de novo*.
`READ_OVERLAP_LENGTH`: length of the accepted overlap between two reads.

## Debug

Valgrind command line example to test with S_pombe.fasta file only:

`valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all --max-stackframe=3000000 ./projet_fasta -n data/S_pombe.fasta`

`--max-stackframe=3000000` is set because we initialize a huge array of structure at the begining of the program.
That means a large range of adresses to allocate, and valgrind warns for that.

Valgrind command line example to test with S_pombe_genome.fasta file only:

`valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all ./projet_fasta -a data/S_pombe_complet.fasta -c "MT dna:chromosome chromosome:ASM294v2:MT:1:19431:1"`

## Test assembly

**Working parameters for sequence assembly in the file `S_pombe_genome.fasta`**

For the 1st sequence: MT dna:chromosome chromosome:ASM294v2:MT:1:19431:1

    NB_NUCL 10
    READ_LENGTH 1000
    READ_OVERLAP_LENGTH 50

    $ ./projet_fasta -a data/S_pombe_complet.fasta -c "MT dna:chromosome chromosome:ASM294v2:MT:1:19431:1"

    Analyse des séquences du fichier...
    Taille de la séquence étudiée pour l'assemblage: 20128 nucléotides
    Génération des reads...

     100 % [===============================================>]

    Nombre de reads générés: 388

    ***************** ASSEMBLAGE DU GENOME *****************

    Le génome a bien été assemblé !

    ############## RAPPORT D'ACTIVITE DU PROGRAMME ##############
    	Temps d'analyse des séquences du fichier: 38.14 secondes
    	Temps d'assemblage du génome: 30.48 secondes


For the 3rd sequence: MTR dna:chromosome chromosome:ASM294v2:MTR:1:20128:1

    NB_NUCL 10
    READ_LENGTH 1000
    READ_OVERLAP_LENGTH 50

    $ ./projet_fasta -a data/S_pombe_complet.fasta -c "MTR"

    Analyse des séquences du fichier...
    Taille de la séquence étudiée pour l'assemblage: 20128 nucléotides
    Génération des reads...

     100 % [===============================================>]

    Nombre de reads générés: 402

    ***************** ASSEMBLAGE DU GENOME *****************

    Le génome a bien été assemblé !

    ############## RAPPORT D'ACTIVITE DU PROGRAMME ##############
    	Temps d'analyse des séquences du fichier: 39.09 secondes
    	Temps d'assemblage du génome: 32.87 secondes
