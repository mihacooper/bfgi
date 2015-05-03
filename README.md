#Befunge interpreter
-------------------------------

## Building
#### Linux
 * Use build.sh shell script

#### Other
 * Not supported yet

## Modules
### BFGI - befunge interpreter
 * Is just a sample program yet
 
### BFGL - befunge interpretation library
 * Library provides inteface for interpretation of Befunge
 * Suppoted Befunge commands(see [Befunge-93](https://en.wikipedia.org/wiki/Befunge)):
  * Management: < > ^ v @
  * Input: 0-9(numbers only yet)
  * Print: . ,

## Extensions
 * Entering a long numbers:
  * Entered numbers should be splitted by spaces or other commands:
    * > 123 123 @ - enters two numbers(123 and 123)
    * > 1 2 3 @ - enters three numbers(1,2,3)
    * > 1.2.3.@ - enters and prints three numbers(1,2,3)
