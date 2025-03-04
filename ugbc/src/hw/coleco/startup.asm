; /*****************************************************************************
;  * ugBASIC - an isomorphic BASIC language compiler for retrocomputers        *
;  *****************************************************************************
;  * Copyright 2021-2023 Marco Spedaletti (asimov@mclink.it)
;  *
;  * Licensed under the Apache License, Version 2.0 (the "License
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
;  * (la "Licenza è proibito usare questo file se non in conformità alla
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
;*                      STARTUP ROUTINE FOR COLECO                             *
;*                                                                             *
;*                             by Marco Spedaletti                             *
;*                                                                             *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

rst_8:
    RETI
    NOP

rst_10:
    RETI
    NOP

rst_18:
    JP $1ffd

rst_20:
    RETI
    NOP

rst_28:
    RETI
    NOP

rst_30:
    RETI
    NOP

rst_38:
    RETI
    NOP

jp NMI

NMI:
	PUSH	AF
	PUSH	BC
	PUSH	DE
	PUSH	HL
	PUSH	IX
	PUSH	IY
	EX	AF,AF'
	PUSH	AF
	EXX
	PUSH	BC
	PUSH	DE
	PUSH	HL
    LD HL,(COLECOTIMER)
    INC HL
    LD (COLECOTIMER),HL
	LD A, (IRQVECTORREADY)
	CMP 0
	JR Z, IRQVECTORSKIP
    CALL IRQVECTOR
IRQVECTORSKIP:
    CALL MUSICPLAYER
	POP	HL
	POP	DE
	POP	BC
	EXX
	POP	AF
	EX	AF,AF'
	POP	IY
	POP	IX
	POP	HL
	POP	DE
	POP	BC
    IN A, ($bf)
	POP	AF
	RETN

; SET_GAMELOOP_HOOK:
;         LD (GAMELOOP_HOOK+1),HL
;         LD A,$c9
;         LD (GAMELOOP_HOOK+3),A
;         LD A,$cd
;         LD (GAMELOOP_HOOK),A
;         RET

IRQVOID:
    RET

COLECOSTARTUP:
    LD	HL, $9b9b
    LD	(CONTROLLER_BUFFER),HL

    LD DE, IRQVOID
    LD HL, IRQVECTOR
    LD A, $c3
    LD (HL), A
    INC HL
    LD A, E
    LD (HL), A
    INC HL
    LD A, D
    LD (HL), A
	LD A, 1
	LD (IRQVECTORREADY), A

    RET