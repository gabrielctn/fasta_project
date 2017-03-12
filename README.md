# C Project: FASTA sequences manipulation

This project is about working on protein and nucleic sequences, stored in FASTA formatted files, in order to make specific searches (by gene name, sequence, position in the genome and sub-string), translations and later calculate distances or make sequencing simulations.

Install and execute
-------------------

`gcc -Wall *.c -o fasta_project`

To show usage, type: 

`./fasta_project -h`



Implemented functions
---------------------

Search by gene name:

`./fasta_project -r "SPAC212.11.1"`

Search only the 1st occurence:

`./fasta_project -n 1 -r "SPAC212.11.1"`
