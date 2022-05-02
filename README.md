# Track-variants-of-a-virus

The Story...
Alpha, Beta, Gamma, Delta, and now the highly infectious Omicron variant! The SARS-CoV-2 (a.k.a., COVID-19) virus has kept mutating, creating new variants continuously. But how do scientists track the different variants of the virus? In this assignment, we will take a sneak peek at a key step in the virus variant tracking process – mapping the genome of a new variant to that of a reference genome (i.e., the genome of a reference virus), which helps identify the genes that have mutated in the vari- ant comparing with the reference virus. You do not need to be a biologist to complete this assign- ment. This assignment specification contains sufficient background knowledge. For further information on virus variant tracking, you may also take a look at a web page on Genomic Surveillance

To track variants of a virus, scientists obtain “isolates”, which are virus isolated from infected patients. DNA or RNA are extracted from the isolates, which need to be translated into a sequence of bases. DNA consists of four bases: adenine (A), cytosine (C), guanine (G), and thymine (T), while the four bases of RNA are adenine (A), cytosine (C), guanine (G), and uracil (U). This translation process is referred to as sequencing. After sequencing, the DNA of a virus is represented as a sequence (that is, a string) consisting of four letters ‘A’, ‘C’, ‘G’, and ‘T’1. Different virus variants can be compared using their DNA strings, and sub-strings of specific patterns (e.g., a gene that makes a variant more infectious) can be identified from the DNA. For example, below are the first 350 bases of the Wuhan-Hu-1 isolate of the SARS-CoV-2 virus:2
ATTAAAGGTTTATACCTTCCCAGGTAACAAACCAACCAACTTTCGATCTCTTGTAGATCTGTTCTCTAAA
CGAACTTTAAAATCTGTGTGGCTGTCACTCGGCTGCATGCTTAGTGCACTCACGCAGTATAATTAATAAC
TAATTACTGTCGTTGACAGGACACGAGTAACTCGTCTATCTTCTGCAGGCTGCTTACGGTTTCGTCCGTG
TTGCAGCCGATCATCAGCACATCTAGGTTTCGTCCGGGTGTGACCGAAAGGTAAGATGGAGAGCCTTGTC
CCTGGTTTCAACGAGAAAACACACGTCCAACTCAGTTTGCCTGTTTTACAGGTTCGCGACGTGCTCGTAC
As a preparation step, the DNA of a virus isolate needs to be broken into short pieces, that is, DNA fragments, because it is more difficult to recognise the bases accurately from long DNA fragments. A sequencer machine then recognises the bases from DNA fragments and converts them into short pieces of DNA sequences called reads, which are represented by short strings consisting of four letters ‘A’, ‘C’, ‘G’, and ‘T’. Below is an example record of a read (using the FASTQ format).
@MT734046.1-1990/1
TTTGCGCATCTGTTATGAAATAGTTTTTAACTGTACTATCCATAGGAATAAAATCTTCTA
+
CCCGGGCGGGGGGCCGGGGGGGGGGGGGGCCGG=GGGGGGGGGGGGGGGGGGGGGGGCGG

The record of a read consists of four lines:
• Line 1: An Identifier line starting with ‘@’ (You may assume at least 2 and up to 100 characters in this line).
• Line 2: A DNA sequence consisting of four letters ‘A’, ‘C’, ‘G’, and ‘T’, where each character represents a DNA base (You may assume at least 2 and up to 100 characters in this line).
• Line 3: A line with a single plus sign ‘+’.
• Line 4: A line of characters of the same length as Line 2. Each character represents a quality score of a base in Line 2, which reflects how confident the sequencer machine is when recognising a base. For example, the first base of the example read, ‘T’, has a quality score of ‘C’ (67), while the last base, ‘A’, has a quality score of ‘G’ (71). The characters in this line have ASCII values between 33 and 73. We will detail how these characters are converted to sequencer machine error probabilities later.
A challenging problem in DNA sequencing is how to map the reads (that is, short sub-strings) of a new virus variant to a reference DNA sequence, such that the complete DNA sequence of the new virus variant can be reconstructed. This assignment works on a simplified version of the problem.
