#Befunge interpreter
-------------------------------

## Building
#### Linux
 * Use build.sh shell script

#### Other
 * Not supported yet

## Modules
#### BFGI - befunge interpreter
 * Simple realisation, it can execute file
 
#### BFGL - befunge interpretation library
 * Library provides inteface for interpretation of Befunge
 * Suppoted Befunge commands(see [Befunge-93](https://en.wikipedia.org/wiki/Befunge)):
  * Management: **< > ^ v @ _ | ? #**
  * Stack: **: \ &**
  * Input: **0-9(numbers only yet)**
  * Print: **. ,**
  * Arithmetic: **+ - * / %**
  * Logical: **! `** 

## Extensions
 * Entering a long numbers:
  * Entered numbers should be splitted by spaces or other commands:
    * @ 123 123 < - enters two numbers(123 and 123)
    * > 1 2 3 @ - enters three numbers(1,2,3)
    * > 1.2.3.@ - enters and prints three numbers(1,2,3)
