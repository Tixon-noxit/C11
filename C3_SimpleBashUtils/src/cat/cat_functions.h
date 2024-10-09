#ifndef CAT_FUNCTION_H
#define CAT_FUNCTION_H

void numberNonblankLines(char **line, int lineNumberGlobal, int flag_t);  // -b
void replaceEndOfLineWithDollarSigns(char **line);                        // -e
void numberAllLines(char **line, int lineNumber, int flag_t);             // -n
void squeezeAdjacentBlankLines(char **line, int *display);                // -s
void displayTabsAsCaretI(char **buffer);                                  // -t
void displayNonPrintableCharacters(char *buffer);                         // -v

#endif
