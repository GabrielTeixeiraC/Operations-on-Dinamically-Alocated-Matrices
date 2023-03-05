# Operations on Dinamically Alocated Matrices
This program implements matrix addition, multiplication and transpose operations through dinamically alocated matrices. Matrix data is read from files and output is printed to a specified file.
## Compilation:
To compile the program, run:

    make all
## Usage:
The program works from the CLI, through the following commmands:  

    ./bin/matop <operation> -1 <matrix 1 file> -2 <matrix 2 file> -o <output file> -p <log file> -l 
    
    '-s' Sum matrices passed through the command line.

    '-m' Multiply matrices passed through the command line

    '-t' Transpose matrix passed through the command line

    '-1 <file>' Sets the file path containing data for matrix 1 to be used in the operation

    '-2 <file>' Sets the file path containing data for matrix 2 to be used in the operation (optional for addition or multiplication)

    '-o <file>' Sets the file path where the result of the chosen operation will be printed

    '-l' Sets whether all memory accesses made by the leMemLog and escreveMemLog functions should be recorded in the performance log file.

    '-p <file>' Sets the file path where performance logs will be printed (optional)

## Example:
### Addition
  Adds matrix 0.in and 1.in, outputs the result to res.out and outputs the logs to log.out if the -l flag is set. 
  
    bin/matop -s -1 matrizes/5x5/0.in -2 matrizes/5x5/1.in -o tmp/res.out -p tmp/log.out -l 

### Multiplication
  Multiplies matrix 0.in and 1.in, outputs the result to res.out and outputs the logs to log.out if the -l flag is set. 
  
    bin/matop -m -1 matrizes/5x5/0.in -2 matrizes/5x5/1.in -o tmp/res.out -p tmp/log.out -l
  
### Transpose
  Transposes matrix 0.in, outputs the result to res.out and outputs the logs to log.out if the -l flag is set. 

    bin/matop -t -1 matrizes/5x5/0.in -o tmp/res.out -p tmp/log.out -l
