/*****************************************************************************
 * ugBASIC - an isomorphic BASIC language compiler for retrocomputers        *
 *****************************************************************************
 * Copyright 2021-2023 Marco Spedaletti (asimov@mclink.it)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *----------------------------------------------------------------------------
 * Concesso in licenza secondo i termini della Licenza Apache, versione 2.0
 * (la "Licenza"); è proibito usare questo file se non in conformità alla
 * Licenza. Una copia della Licenza è disponibile all'indirizzo:
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Se non richiesto dalla legislazione vigente o concordato per iscritto,
 * il software distribuito nei termini della Licenza è distribuito
 * "COSÌ COM'È", SENZA GARANZIE O CONDIZIONI DI ALCUN TIPO, esplicite o
 * implicite. Consultare la Licenza per il testo specifico che regola le
 * autorizzazioni e le limitazioni previste dalla medesima.
 ****************************************************************************/

/****************************************************************************
 * INCLUDE SECTION 
 ****************************************************************************/

#include "../../ugbc.h"

/****************************************************************************
 * CODE SECTION 
 ****************************************************************************/

Variable * joy_vars( Environment * _environment, char * _port ) {

    MAKE_LABEL

    Variable * port = variable_retrieve_or_define( _environment, _port, VT_BYTE, 0 );
    Variable * result = variable_temporary( _environment, VT_BYTE, "(result of JOY)" );

    outline1("LDA %s", port->realName );
    outline0("CMP #0" );
    outline1("BEQ %sjoy0", label );
    outline0("CMP #1" );
    outline1("BEQ %sjoy1", label );
    outline0("CMP #2" );
    outline1("BEQ %sjoy2", label );
    outline0("CMP #3" );
    outline1("BEQ %sjoy3", label );
    outline1("JMP %send2", label );

    outhead1("%sjoy0:", label );
    outline0("LDA $D300");
    outline0("AND #$0F");
    outline0("ASL A");
    outline1("STA %s", result->realName);
    outline0("LDA $D010");
    outline0("AND #$01");
    outline1("ORA %s", result->realName);
    outline1("STA %s", result->realName);
    outline1("JMP %send", label );

    outhead1("%sjoy1:", label );
    outline0("LDA $D300");
    outline0("AND #$F0");
    outline0("LSR A");
    outline0("LSR A");
    outline0("LSR A");
    outline1("STA %s", result->realName);
    outline0("LDA $D011");
    outline0("AND #$01");
    outline1("ORA %s", result->realName);
    outline1("STA %s", result->realName);
    outline1("JMP %send", label );

    outhead1("%sjoy2:", label );
    outline0("LDA $D301");
    outline0("AND #$0F");
    outline0("ASL A");
    outline1("STA %s", result->realName);
    outline0("LDA $D012");
    outline0("AND #$01");
    outline1("ORA %s", result->realName);
    outline1("STA %s", result->realName);
    outline1("JMP %send", label );

    outhead1("%sjoy3:", label );
    outline0("LDA $D301");
    outline0("AND #$F0");
    outline0("LSR A");
    outline0("LSR A");
    outline0("LSR A");
    outline1("STA %s", result->realName);
    outline0("LDA $D013");
    outline0("AND #$01");
    outline1("ORA %s", result->realName);
    outline1("STA %s", result->realName);
    outline1("JMP %send", label );

    outhead1("%send:", label );
    outline1("LDA %s", result->realName);
    outline0("EOR #$ff");
    outline0("AND #$1f");
    outline1("STA %s", result->realName);
    outhead1("%send2:", label );

    return result;
    
}

Variable * joy( Environment * _environment, int _port ) {

    MAKE_LABEL

    Variable * result = variable_temporary( _environment, VT_BYTE, "(result of JOY)" );

    switch( _port ) {
        case 0:
            outline0("LDA $D300");
            outline0("AND #$0F");
            outline0("ASL A");
            outline1("STA %s", result->realName);
            outline0("LDA $D010");
            outline0("AND #$01");
            outline1("ORA %s", result->realName);
            outline1("STA %s", result->realName);
            break;

        case 1:
            outline0("LDA $D300");
            outline0("AND #$F0");
            outline0("LSR A");
            outline0("LSR A");
            outline0("LSR A");
            outline1("STA %s", result->realName);
            outline0("LDA $D011");
            outline0("AND #$01");
            outline1("ORA %s", result->realName);
            outline1("STA %s", result->realName);
            break;

        case 2:
            outline0("LDA $D301");
            outline0("AND #$0F");
            outline0("ASL A");
            outline1("STA %s", result->realName);
            outline0("LDA $D012");
            outline0("AND #$01");
            outline1("ORA %s", result->realName);
            outline1("STA %s", result->realName);
            break;

        case 3:
            outline0("LDA $D301");
            outline0("AND #$F0");
            outline0("LSR A");
            outline0("LSR A");
            outline0("LSR A");
            outline1("STA %s", result->realName);
            outline0("LDA $D013");
            outline0("AND #$01");
            outline1("ORA %s", result->realName);
            outline1("STA %s", result->realName);
            break;

    }

    outline1("LDA %s", result->realName);
    outline0("EOR #$ff");
    outline0("AND #$1f");
    outline1("STA %s", result->realName);

    return result;
    
}