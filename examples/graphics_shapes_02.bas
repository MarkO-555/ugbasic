REM @english
REM GRAPHICS PRIMITIVES DRAWING SHAPES (2)
REM
REM This example will draw random circles on the screen.
REM
REM @italian
REM PRIMITIVE DI GRAFICA CON DISEGNO DI FORME (2)
REM
REM Questo esempio disegnerà cerchi casuali sullo schermo.

    BITMAP ENABLE
    CLS
    INK RED
    GR LOCATE SCREEN WIDTH/2,SCREEN HEIGHT/2
    CIRCLE ,,45
    x=(POSITION)0
    y=(POSITION)0
    r=(POSITION)0
    DO
        INK RND(SCREEN COLORS)
        x=RND(SCREEN WIDTH/2)+20
        y=RND(SCREEN HEIGHT/2)+20
        r=RND(20)
        ' CIRCLE x,y,10
    LOOP
