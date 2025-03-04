REM @english
REM OTHER CONTRIBUTIONS PRINTABLE CHARACTERS (COMPRESSED)
REM
REM This small example will show the (printable) CHARACTERS TABLE on the screen.
REM The buffer will be compressed with MSC1 algorithm, to save space.
REM 
REM @italian
REM VARI ALTRI CONTRIBUTI CARATTERI STAMPABILI
REM
REM Questo piccolo esempio mostra la tabella dei codici ASCII (stampabili) sullo schermo.
REM La tabella sarà compressa con l'algoritmo MSC1, per risparmiare spazio.
REM

PRINT "print ascii:"
PRINT "0123456789\|!£$%&/()=?^ABCDEFGHIJKLMNOPQRSTUVXYWZabcdefghijklmnopqrstuvxywz"

PRINT

PRINT "print raw:"
PRINT #"0123456789\|!£$%&/()=?^ABCDEFGHIJKLMNOPQRSTUVXYWZabcdefghijklmnopqrstuvxywz"

a := LOAD("examples/printable.txt") COMPRESSED

PRINT

PRINT "print buffer:"
PRINT BUFFER a

PRINT

PRINT "print raw:"
PRINT BUFFER RAW a
