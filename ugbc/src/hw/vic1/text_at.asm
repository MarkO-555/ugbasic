; /*****************************************************************************
;  * ugBASIC - an isomorphic BASIC language compiler for retrocomputers        *
;  *****************************************************************************
;  * Copyright 2021 Marco Spedaletti (asimov@mclink.it)
;  *
;  * Licensed under the Apache License, Version 2.0 (the "License");
;  * you may not use this file except in compliance with the License.
;  * You may obtain a copy of the License at
;  *
;  * http://www.apache.org/licenses/LICENSE-2.0
;  *
;  * Unless required by applicable law or agreed to in writing, software
;  * distributed under the License is distributed on an "AS IS" BASIS,
;  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
;  * See the License for the specific language governing permissions and
;  * limitations under the License.
;  *----------------------------------------------------------------------------
;  * Concesso in licenza secondo i termini della Licenza Apache, versione 2.0
;  * (la "Licenza"); è proibito usare questo file se non in conformità alla
;  * Licenza. Una copia della Licenza è disponibile all'indirizzo:
;  *
;  * http://www.apache.org/licenses/LICENSE-2.0
;  *
;  * Se non richiesto dalla legislazione vigente o concordato per iscritto,
;  * il software distribuito nei termini della Licenza è distribuito
;  * "COSì COM'è", SENZA GARANZIE O CONDIZIONI DI ALCUN TIPO, esplicite o
;  * implicite. Consultare la Licenza per il testo specifico che regola le
;  * autorizzazioni e le limitazioni previste dalla medesima.
;  ****************************************************************************/
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                                                                             *
;*                      TEXT AT GIVEN POSITION ON VIC-I                       *
;*                                                                             *
;*                             by Marco Spedaletti                             *
;*                                                                             *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

TEXTPTR = $20
TEXTSIZE = $24
TABSTODRAW = $36
TEXTPEN = $2B
TEXTPAPER = $2D
SCREENCODE = $2E

TEXTATDECODE:
    CMP #32
    BCS TEXTATXSP128
    JMP TEXTATSP128
TEXTATXSP128:
    CMP #64
    BCS TEXTATXSP0
    JMP TEXTATDECODE0
TEXTATXSP0:
    CMP #96
    BCS TEXTATXSM64
    JMP TEXTATSM64
TEXTATXSM64:
    CMP #160
    BCS TEXTATXSP64
    JMP TEXTATSP64
TEXTATXSP64:
    CMP #192
    BCS TEXTATX2SM64
    JMP TEXTATSM64
TEXTATX2SM64:
    CMP #224
    BCS TEXTATX2SM128
    JMP TEXTATSM128
TEXTATX2SM128:
    JMP TEXTATDECODE0
TEXTATSP64:
    CLC
    ADC #64
    JMP TEXTATDECODE0
TEXTATSP128:
    ADC #128
    JMP TEXTATDECODE0
TEXTATSM64:
    SBC #63
    JMP TEXTATDECODE0
TEXTATSM128:
    SBC #127
    JMP TEXTATDECODE0
TEXTATDECODE0:
    STA SCREENCODE
    RTS

TEXTAT:
    LDA TEXTSIZE
    BNE TEXTATGO
    RTS

TEXTATGO:
    LDA TEXTADDRESS
    STA COPYOFTEXTADDRESS
    LDA TEXTADDRESS+1
    STA COPYOFTEXTADDRESS+1
    LDA #0
    STA TABSTODRAW
    LDA COLORMAPADDRESS
    STA COPYOFCOLORMAPADDRESS
    LDA COLORMAPADDRESS+1
    STA COPYOFCOLORMAPADDRESS+1
    LDA _PAPER
    STA TEXTPAPER

    SEI
    LDA CURRENTMODE
    CMP #0
    BNE TEXTATGO0X
    JMP TEXTATTILEMODE
TEXTATGO0X:
    CMP #1
    BNE TEXTATGO1X
    JMP TEXTATTILEMODE
TEXTATGO1X:
    CMP #2
    BNE TEXTATGO2X
    JMP TEXTATBITMAPMODE
TEXTATGO2X:
    CMP #3
    BNE TEXTATGO3X
    JMP TEXTATBITMAPMODE
TEXTATGO3X:
    CMP #4
    BNE TEXTATGO4X
    JMP TEXTATTILEMODE
TEXTATGO4X:
    CLI
    RTS
    
;-----------------------------------------------------------------------------
; BITMAP MODE
;-----------------------------------------------------------------------------

TEXTATBITMAPMODE:

;     RTS
    
;     LDX XCURSYS
;     LDY YCURSYS

;     CLC

;     LDA PLOTVBASELO,Y          ;table of $A000 row base addresses
;     ADC PLOT8LO,X              ;+ (8 * Xcell)
;     STA PLOTDEST               ;= cell address

;     LDA PLOTVBASEHI,Y          ;do the high byte
;     ADC PLOT8HI,X
;     STA PLOTDEST+1

;     CLC

;     TXA
;     ADC PLOTCVBASELO,Y          ;table of $8400 row base addresses
;     STA PLOTCDEST               ;= cell address

;     LDA #0
;     ADC PLOTCVBASEHI,Y          ;do the high byte
;     STA PLOTCDEST+1

;     LDX TEXTSIZE
;     LDY #$0
; TEXTATBMLOOP2:

;     LDA TABSTODRAW
;     BEQ TEXTATBMNSKIPTAB
;     JMP TEXTATBMSKIPTAB

; TEXTATBMNSKIPTAB:
;     LDA (TEXTPTR),Y

;     CMP #31
;     BCS TEXTATBMXCC
;     JMP TEXTATBMCC

; TEXTATBMXCC:
;     JSR TEXTATDECODE
;     JMP TEXTATBMSP0

; TEXTATBMTAB:
;     LDA XCURSYS
; TEXTATBMTAB2:
;     CMP TABCOUNT
;     BCC TEXTATBMTAB3
;     SEC
;     SBC TABCOUNT
;     JMP TEXTATBMTAB2
; TEXTATBMTAB3:
;     STA TMPPTR
;     LDA TABCOUNT
;     SEC
;     SBC TMPPTR
;     STA TABSTODRAW
;     JMP TEXTATBMNEXT

; TEXTATBMCC:
;     CMP #09
;     BEQ TEXTATBMTAB
;     CMP #01
;     BEQ TEXTATBMPEN
;     CMP #02
;     BEQ TEXTATBMPAPER
;     CMP #03
;     BEQ TEXTATBMCMOVEPREPARE
;     CMP #04
;     BEQ TEXTATBMXAT
;     JMP TEXTATBMNEXT

; TEXTATBMXAT:
;     JMP TEXTATBMAT

; TEXTATBMPEN:
;     INC TEXTPTR
;     DEX
;     LDA TEXTWW
;     AND #$2
;     BEQ TEXTATBMPENDISABLED
;     LDA (TEXTPTR), Y
;     ASL A
;     ASL A
;     ASL A
;     ASL A
;     STA TEXTPEN
; TEXTATBMPENDISABLED:
;     INC TEXTPTR
;     DEY
;     JMP TEXTATBMNEXT

; TEXTATBMPAPER:
;     INC TEXTPTR
;     DEX
;     LDA TEXTWW
;     AND #$1
;     BEQ TEXTATBMPAPERDISABLED
;     LDA (TEXTPTR), Y
;     STA TEXTPAPER
; TEXTATBMPAPERDISABLED:
;     INC TEXTPTR
;     DEY
;     JMP TEXTATBMNEXT

; TEXTATBMCMOVEPREPARE:
;     INC TEXTPTR
;     DEX
;     LDA (TEXTPTR), Y
;     STA CLINEX
;     INC TEXTPTR
;     DEX
;     LDA (TEXTPTR), Y
;     STA CLINEY

; TEXTATBMCMOVE:
;     CLC
;     LDA CLINEX
;     ADC XCURSYS
;     STA XCURSYS
;     LDA CLINEY
;     ADC YCURSYS
;     STA YCURSYS

;     JMP TEXTATBMNEXT

; TEXTATBMAT:
;     INC TEXTPTR
;     DEX
;     LDA (TEXTPTR), Y
;     SEC
;     SBC XCURSYS
;     STA CLINEX
;     INC TEXTPTR
;     DEX
;     LDA (TEXTPTR), Y
;     SEC
;     SBC YCURSYS
;     STA CLINEY
;     JMP TEXTATBMCMOVE

; TEXTATBMSP0:

;     TYA
;     PHA

;     TXA
;     PHA

;     LDX XCURSYS
;     LDY YCURSYS

;     CLC

;     LDA PLOTVBASELO,Y          ;table of $A000 row base addresses
;     ADC PLOT8LO,X              ;+ (8 * Xcell)
;     STA PLOTDEST               ;= cell address

;     LDA PLOTVBASEHI,Y          ;do the high byte
;     ADC PLOT8HI,X
;     STA PLOTDEST+1

;     CLC

;     TXA
;     ADC PLOTCVBASELO,Y          ;table of $8400 row base addresses
;     STA PLOTCDEST               ;= cell address

;     LDA #0
;     ADC PLOTCVBASEHI,Y          ;do the high byte
;     STA PLOTCDEST+1

;     CLC

;     TXA
;     ADC PLOTC2VBASELO,Y          ;table of $8400 row base addresses
;     STA PLOTC2DEST               ;= cell address

;     LDA #0
;     ADC PLOTC2VBASEHI,Y          ;do the high byte
;     STA PLOTC2DEST+1

;     PLA
;     TAX
    
;     PLA
;     TAY

;     TYA
;     PHA
;     LDY #0

;     LDA SCREENCODE
;     STA TMPPTR
;     LDA #0
;     STA TMPPTR+1

;     CLC
;     ASL TMPPTR
;     ROL TMPPTR+1
;     CLC
;     ASL TMPPTR
;     ROL TMPPTR+1
;     CLC
;     ASL TMPPTR
;     ROL TMPPTR+1

;     CLC
;     LDA #$0
;     ADC TMPPTR
;     STA TMPPTR
;     LDA #$98
;     ADC TMPPTR+1
;     STA TMPPTR+1
; TEXTATBMSP0L1:
;     LDA CURRENTMODE
;     CMP #3
;     BEQ TEXTATBMSP0L1B3

; TEXTATBMSP0L1B2:
;     LDA (TMPPTR),Y
;     STA (PLOTDEST),Y
;     JMP TEXTATBMSP0L1X

; TEXTATBMSP0L1B3:
;     LDA (TMPPTR),Y
;     CLC
;     ASL
;     ORA (TMPPTR),Y
;     STA (PLOTDEST),Y
;     JMP TEXTATBMSP0L1X

; TEXTATBMSP0L1X:
;     INY
;     CPY #8
;     BNE TEXTATBMSP0L1

;     LDA CURRENTMODE
;     CMP #3
;     BEQ TEXTATBMC3

;     LDA TEXTWW
;     AND #$2
;     BEQ TEXTATBMCNOPEN
;     LDY #0
;     LDA (PLOTCDEST),Y
;     ORA TEXTPEN
;     STA (PLOTCDEST),Y
; TEXTATBMCNOPEN:
;     LDA TEXTWW
;     AND #$1
;     BEQ TEXTATBMCNOPAPER
;     LDA (PLOTCDEST),Y
;     AND #$f0
;     ORA TEXTPAPER
;     STA (PLOTCDEST),Y
; TEXTATBMCNOPAPER:
;     JMP TEXTATBMF

; TEXTATBMC3:
;     LDA TEXTWW
;     AND #$2
;     BEQ TEXTATBMC3NOPEN
;     LDY #0
;     LDA TEXTPEN
;     STA (PLOTC2DEST),Y
;     LDA #0
;     STA (PLOTCDEST),Y
;     LDA TEXTPEN
;     ASL
;     ASL
;     ASL
;     ASL
;     ORA (PLOTCDEST),Y
;     STA (PLOTCDEST),Y
; TEXTATBMC3NOPEN:
;     JMP TEXTATBMF

; TEXTATBMF:
;     PLA
;     TAY
;     JMP TEXTATBMINCX

; TEXTATBMSKIPTAB:
;     DEC TABSTODRAW
;     JMP TEXTATBMINCX

; TEXTATBMINCX:
;     INC XCURSYS
;     LDA XCURSYS
;     CMP CURRENTTILESWIDTH
;     BEQ TEXTATBMNEXT2
;     JMP TEXTATBMNEXT
; TEXTATBMNEXT2:
;     LDA #0
;     STA XCURSYS
;     INC YCURSYS
;     LDA YCURSYS
;     CMP CURRENTTILESHEIGHT

;     BEQ TEXTATBMNEXT3
;     JMP TEXTATBMNEXT
; TEXTATBMNEXT3:

;     ; scrolling ?

; TEXTATBMNEXT:
;     LDA TABSTODRAW
;     BEQ TEXTATBMXLOOP2
;     JMP TEXTATBMLOOP2
; TEXTATBMXLOOP2:
;     INY
;     DEX
;     BEQ TEXTATBMEND
;     JMP TEXTATBMLOOP2
; TEXTATBMEND:
;     CLI
    RTS

;-----------------------------------------------------------------------------
; TILE MODE
;-----------------------------------------------------------------------------

TEXTATTILEMODE:    
    LDX YCURSYS
    BEQ TEXTATSKIP
TEXTATLOOP1:
    CLC
    LDA CURRENTTILESWIDTH
    ADC COPYOFTEXTADDRESS
    STA COPYOFTEXTADDRESS
    LDA #0
    ADC COPYOFTEXTADDRESS+1
    STA COPYOFTEXTADDRESS+1
    DEX
    BNE TEXTATLOOP1

    LDX YCURSYS
TEXTATLOOPC1:
    CLC
    LDA CURRENTTILESWIDTH
    ADC COPYOFCOLORMAPADDRESS
    STA COPYOFCOLORMAPADDRESS
    LDA #0
    ADC COPYOFCOLORMAPADDRESS+1
    STA COPYOFCOLORMAPADDRESS+1
    DEX
    BNE TEXTATLOOPC1

TEXTATSKIP:
    CLC
    LDA XCURSYS
    ADC COPYOFTEXTADDRESS
    STA COPYOFTEXTADDRESS
    LDA #0
    ADC COPYOFTEXTADDRESS+1
    STA COPYOFTEXTADDRESS+1

    CLC
    LDA XCURSYS
    ADC COPYOFCOLORMAPADDRESS
    STA COPYOFCOLORMAPADDRESS
    LDA #0
    ADC COPYOFCOLORMAPADDRESS+1
    STA COPYOFCOLORMAPADDRESS+1

    LDX TEXTSIZE
    LDY #$0
TEXTATLOOP2:

    LDA TABSTODRAW
    BEQ TEXTATNSKIPTAB
    JMP TEXTATSKIPTAB

TEXTATNSKIPTAB:
    LDA (TEXTPTR),Y

    CMP #31
    BCS TEXTATXCC
    JMP TEXTATCC

TEXTATXCC:
    JSR TEXTATDECODE
    JMP TEXTATSP0

TEXTATTAB:
    LDA XCURSYS
TEXTATTAB2:
    CMP TABCOUNT
    BCC TEXTATTAB3
    SEC
    SBC TABCOUNT
    JMP TEXTATTAB2
TEXTATTAB3:
    STA TMPPTR
    LDA TABCOUNT
    SEC
    SBC TMPPTR
    STA TABSTODRAW
    JMP TEXTATNEXT

TEXTATCC:
    CMP #09
    BEQ TEXTATTAB
    CMP #01
    BEQ TEXTATPEN
    CMP #02
    BEQ TEXTATPAPER
    CMP #03
    BEQ TEXTATCMOVEPREPARE
    CMP #04
    BEQ TEXTATXAT
    JMP TEXTATNEXT

TEXTATXAT:
    JMP TEXTATAT

TEXTATPEN:
    INC TEXTPTR
    DEX
    LDA TEXTWW
    AND #$2
    BEQ TEXTATPENDISABLED
    LDA (TEXTPTR), Y
    STA TEXTPEN
TEXTATPENDISABLED:
    INC TEXTPTR
    DEY
    JMP TEXTATNEXT

TEXTATPAPER:
    INC TEXTPTR
    DEX
    LDA TEXTWW
    AND #$1
    BEQ TEXTATPAPERDISABLED
    LDA (TEXTPTR), Y
    ; STA $d021
    ; STA $d020
TEXTATPAPERDISABLED:
    INC TEXTPTR
    DEY
    JMP TEXTATNEXT

TEXTATCMOVEPREPARE:
    INC TEXTPTR
    DEX
    LDA (TEXTPTR), Y
    STA CLINEX
    INC TEXTPTR
    DEX
    LDA (TEXTPTR), Y
    STA CLINEY

TEXTATCMOVE:
    CLC
    LDA CLINEX
    ADC XCURSYS
    CMP #$80
    BCS TEXTATCMOVESKIPX
    CMP CURRENTTILESWIDTH
    BCS TEXTATCMOVESKIPX
    STA XCURSYS
    LDA CLINEX

    CMP #$80
    BCC TEXTATCMOVEADDPX

TEXTATCMOVESUBPX:
    EOR #$FF
    CLC
    ADC #$1
    STA CLINEX
    SEC
    LDA COPYOFTEXTADDRESS
    SBC CLINEX
    STA COPYOFTEXTADDRESS
    LDA COPYOFTEXTADDRESS+1
    SBC #0
    STA COPYOFTEXTADDRESS+1

    SEC
    LDA COPYOFCOLORMAPADDRESS
    SBC CLINEX
    STA COPYOFCOLORMAPADDRESS
    LDA COPYOFCOLORMAPADDRESS+1
    SBC #0
    STA COPYOFCOLORMAPADDRESS+1

    JMP TEXTATCMOVESKIPX

TEXTATCMOVEADDPX:

    CLC
    ADC COPYOFTEXTADDRESS
    STA COPYOFTEXTADDRESS
    LDA #0
    ADC COPYOFTEXTADDRESS+1
    STA COPYOFTEXTADDRESS+1
    JMP TEXTATCMOVESKIPX

TEXTATCMOVESKIPX:

    CLC
    LDA CLINEY
    ADC YCURSYS
    CMP #$80
    BCS TEXTATCMOVESKIPY
    CMP CURRENTTILESHEIGHT
    BCS TEXTATCMOVESKIPY
    STA YCURSYS

TEXTATCMOVEADDPY:
    TXA
    PHA
    LDA CLINEY
    CMP #$80
    BCC TEXTATCMOVELOOPYP
    JMP TEXTATCMOVELOOPYM

TEXTATCMOVELOOPYP:
    TAX
TEXTATCMOVELOOPY:

    CLC
    LDA CURRENTTILESWIDTH
    ADC COPYOFTEXTADDRESS
    STA COPYOFTEXTADDRESS
    LDA #0
    ADC COPYOFTEXTADDRESS+1
    STA COPYOFTEXTADDRESS+1

    CLC
    LDA CURRENTTILESWIDTH
    ADC COPYOFCOLORMAPADDRESS
    STA COPYOFCOLORMAPADDRESS
    LDA #0
    ADC COPYOFCOLORMAPADDRESS+1
    STA COPYOFCOLORMAPADDRESS+1

    DEX
    BNE TEXTATCMOVELOOPY
    PLA
    TAX
    JMP TEXTATCMOVESKIPY

TEXTATCMOVELOOPYM:
    EOR #$FF
    CLC
    ADC #$1
    STA CLINEY
    TAX
TEXTATCMOVELOOPY2:

    SEC
    LDA COPYOFTEXTADDRESS
    SBC CURRENTTILESWIDTH
    STA COPYOFTEXTADDRESS
    LDA COPYOFTEXTADDRESS+1
    SBC #0
    STA COPYOFTEXTADDRESS+1

    SEC
    LDA COPYOFCOLORMAPADDRESS
    SBC CURRENTTILESWIDTH
    STA COPYOFCOLORMAPADDRESS
    LDA COPYOFCOLORMAPADDRESS+1
    SBC #0
    STA COPYOFCOLORMAPADDRESS+1

    DEX
    BNE TEXTATCMOVELOOPY2
    PLA
    TAX
    JMP TEXTATCMOVESKIPY

TEXTATCMOVESKIPY:
    INC TEXTPTR
    DEY
    JMP TEXTATNEXT

TEXTATAT:
    INC TEXTPTR
    DEX
    LDA (TEXTPTR), Y
    SEC
    SBC XCURSYS
    STA CLINEX
    INC TEXTPTR
    DEX
    LDA (TEXTPTR), Y
    SEC
    SBC YCURSYS
    STA CLINEY
    JMP TEXTATCMOVE

TEXTATSP0:
    STA (COPYOFTEXTADDRESS),Y
    LDA TEXTWW
    AND #$2
    BEQ TEXTATCNOPEN
    LDA TEXTPEN
    STA (COPYOFCOLORMAPADDRESS),Y
TEXTATCNOPEN:
    JMP TEXTATINCX

TEXTATSKIPTAB:
    DEC TABSTODRAW
    JMP TEXTATINCX

TEXTATINCX:
    INC XCURSYS
    LDA XCURSYS
    CMP CURRENTTILESWIDTH
    BEQ TEXTATNEXT2
    JMP TEXTATNEXT
TEXTATNEXT2:
    LDA #0
    STA XCURSYS
    INC YCURSYS
    LDA YCURSYS
    CMP CURRENTTILESHEIGHT

    BEQ TEXTATNEXT3
    JMP TEXTATNEXT
TEXTATNEXT3:

    LDA #$FE
    STA DIRECTION
    JSR VSCROLLT

    DEC YCURSYS
    SEC
    LDA COPYOFTEXTADDRESS
    SBC CURRENTTILESWIDTH
    STA COPYOFTEXTADDRESS
    LDA COPYOFTEXTADDRESS+1
    SBC #0
    STA COPYOFTEXTADDRESS+1

    SEC
    LDA COPYOFCOLORMAPADDRESS
    SBC CURRENTTILESWIDTH
    STA COPYOFCOLORMAPADDRESS
    LDA COPYOFCOLORMAPADDRESS+1
    SBC #0
    STA COPYOFCOLORMAPADDRESS+1

TEXTATNEXT:
    LDA TABSTODRAW
    BEQ TEXTATXLOOP2
    JMP TEXTATLOOP2
TEXTATXLOOP2:
    INY
    DEX
    BEQ TEXTATEND
    JMP TEXTATLOOP2
TEXTATEND:
    CLI
    RTS
