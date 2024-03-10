# Cat_Grep
Development of Bash text utilities: cat, grep on C



## Contents

0. [Information](#information)
1. [Cat](#cat) \
   1.1. [Cat Options](#cat-options)
2. [Grep](#grep) \
   2.1. [Grep Options](#grep-options)





### Information

- The program were developed in C language of C11 standard using gcc compiler.
- The program code of the cat and grep was located on src/cat/ and src/grep/ folders, respectively  
- Outdated and legacy language constructions and library functions were not used.
- The programs were developed by POSIX.1-2017 standard.
- The program code written in Google style
- The programs has executable files with command line arguments
- The programs were built with Makefile with appropriate targets: my_cat, my_grep
- Integration tests cover all flag variants and input values, based on a comparison with the behavior of real Bash utilities 
- The programs were developed according to the principles of structured programming
- Code duplication was avoided
- The statement of the message in the case of an error does not matter
- Input via stdin is not required to be supported


### Cat

Cat is one of the most frequently used commands on Unix-like operating systems. It has three related functions with regard to text files: displaying them, combining copies of them and creating new ones.

`cat [OPTION] [FILE]...`

### Cat Options

| No. | Options | Description |
| ------ | ------ | ------ |
| 1 | -b (GNU: --number-nonblank) | numbers only non-empty lines |
| 2 | -e implies -v (GNU only: -E the same, but without implying -v) | but also display end-of-line characters as $  |
| 3 | -n (GNU: --number) | number all output lines |
| 4 | -s (GNU: --squeeze-blank) | squeeze multiple adjacent blank lines |
| 5 | -t implies -v (GNU: -T the same, but without implying -v) | but also display tabs as ^I  |


- Support of all flags (including GNU versions) specified [above](#cat-options)
- The source, header, and build files were placed in the src/cat/ directory
- The resulting executable file was placed in the directory src/cat/ and named my_cat


### Grep

Thompson wrote the first version in PDP-11 assembly language to help Lee E. McMahon analyze the text of the Federalist Papers to determine authorship of the individual papers. The ed text editor (also authored by Thompson) had regular expression support but could not be used on such a large amount of text, so Thompson excerpted that code into a standalone tool. He chose the name because in ed, the command g/re/p would print all lines matching a specified pattern. grep was first included in Version 4 Unix. Stating that it is "generally cited as the prototypical software tool", McIlroy credited grep with "irrevocably ingraining" Thompson's tools philosophy in Unix.

`grep [options] template [file_name]`

### Grep Options

| No. | Options | Description |
| ------ | ------ | ------ |
| 1 | -e | pattern |
| 2 | -i | Ignore uppercase vs. lowercase.  |
| 3 | -v | Invert match. |
| 4 | -c | Output count of matching lines only. |
| 5 | -l | Output matching files only.  |
| 6 | -n | Precede each matching line with a line number. |
| 7 | -h | Output matching lines without preceding them by file names. |
| 8 | -s | Suppress error messages about nonexistent or unreadable files. |
| 9 | -f file | Take regexes from a file. |
| 10 | -o | Output the matched parts of a matching line. |


- Support of all flags (including GNU versions) specified [above](#grep-options)
- Support of all flags, including their _pair_ combinations (e.g. `-iv`, `-in`)
- Only regex library were used for regular expressions
- The source, header and make files were placed in the src/grep/ directory
- The resulting executable file was placed in the directory src/grep/ and named my_grep
