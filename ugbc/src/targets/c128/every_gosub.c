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

/**
 * @brief Emit ASM code for <b>EVERY ... TICKS GOSUB ...</b>
 * 
 * Emit assembly code to initialize the EVERY subsystem.
 * 
 * @param _environment 
 * @param _timing 
 * @param _label 
 */
/* <usermanual>
@keyword EVERY...GOSUB

@english
Define the call of a sub-routine at regular intervals, without 
interfering with the main program. You must specifying the length of time 
between every call, measured in TICKS. 

Note that the subroutine execution 
time should be less than the interval time, or the main program timings 
will be affected. After a subroutine has been entered, the 
''EVERY'' system is automatically disabled. This means that, 
in order to call this feature continuously, an ''EVERY ON'' command 
must be inserted into a subroutine before the final RETURN statement.

@italian
Definisce una chiamata a una sottoprogramma a intervalli regolari, senza
interferire con il programma principale. È necessario specificare il
periodo di tempo tra ogni chiamata, misurata in TICKS.

Si fa notare che la durata dell'esecuzione della subroutine dovrebbe essere 
inferiore al tempo dell'intervallo indicato, altrimenti le temporizzazioni 
del programma principale ne risentiranno. 

Dopo essere entrati nella subroutine, il sistema disabilita la chiamata
periodica. Ciò significa che, per richiamare questa funzione in modo continuo,
è necessario invocare il comando ''EVERY ON'' prima dell'istruzione ''RETURN'' finale.

@syntax EVERY [timing] TICKS GOSUB [identifier]

@example EVERY 50 TICKS GOSUB changeBorderColor
@usedInExample control_periodic_01.bas

@target c128
</usermanual> */
void every_ticks_gosub( Environment * _environment, char * _timing, char * _label ) {

    Variable * timing = variable_retrieve( _environment, _timing );

    Variable * zero = variable_temporary( _environment, timing->type, "(zero)" );
    variable_store( _environment, zero->name, 0 );

    _environment->everyStatus = variable_retrieve( _environment, "EVERYSTATUS");
    _environment->everyStatus->locked = 1;

    _environment->everyCounter = variable_temporary( _environment, timing->type, "(every counter)");
    _environment->everyCounter->locked = 1;
    _environment->everyTiming = timing;
    _environment->everyTiming->locked = 1;

    variable_move_naked( _environment, _environment->everyTiming->name, _environment->everyCounter->name );

    char skipEveryRoutineLabel[MAX_TEMPORARY_STORAGE]; sprintf(skipEveryRoutineLabel, "setg%d", UNIQUE_ID );
    char everyRoutineLabel[MAX_TEMPORARY_STORAGE]; sprintf(everyRoutineLabel, "etg%d", UNIQUE_ID );
    char endOfEveryRoutineLabel[MAX_TEMPORARY_STORAGE]; sprintf(endOfEveryRoutineLabel, "eetg%d", UNIQUE_ID );
    
    cpu_jump( _environment, skipEveryRoutineLabel );
    
    cpu_label( _environment, everyRoutineLabel );
    
    cpu_di( _environment );

    cpu_bveq( _environment, _environment->everyStatus->realName, endOfEveryRoutineLabel );

    variable_decrement( _environment, _environment->everyCounter->name );

    cpu_bvneq( _environment, variable_compare_not( _environment, _environment->everyCounter->name, zero->name )->realName, endOfEveryRoutineLabel );

    cpu_call( _environment, _label );

    variable_move_naked( _environment, _environment->everyTiming->name, _environment->everyCounter->name );

    cpu_label( _environment, endOfEveryRoutineLabel );

    cpu_ei( _environment );

    vic2_next_raster( _environment );

    cpu_label( _environment, skipEveryRoutineLabel );

    vic2_raster_at( _environment, everyRoutineLabel, "0", "42" );

}
