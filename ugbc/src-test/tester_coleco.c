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
 * "COSì COM'è", SENZA GARANZIE O CONDIZIONI DI ALCUN TIPO, esplicite o
 * implicite. Consultare la Licenza per il testo specifico che regola le
 * autorizzazioni e le limitazioni previste dalla medesima.
 ****************************************************************************/

/****************************************************************************
 * INCLUDE SECTION 
 ****************************************************************************/

#include "tester.h"

/****************************************************************************
 * CODE SECTION
 ****************************************************************************/

#ifdef __coleco__

void create_test( char *_name, void (*_payload)(TestEnvironment *), int (*_tester)(TestEnvironment *) ) {

    TestEnvironment t;
    memset( &t, 0, sizeof( TestEnvironment ) ) ;

    Environment * _environment = &t.environment;

    t.environment.sourceFileName = strdup("/tmp/out.bas");
    t.environment.asmFileName = strdup("/tmp/out.asm");
    t.environment.debuggerLabelsFileName = strdup("/tmp/out.lb2");
    begin_compilation( &t.environment );    
    _payload( &t );
    outline0("HALT");
    end_compilation( &t.environment );

    FILE *handleIns = fopen( "/tmp/out.ins", "wt" );
    int i=0,j=0;
    for(i=0; i<t.debug.inspections_count; ++i ) {
        fprintf( handleIns, "%4.4x %4.4x %s\n", t.debug.inspections[i].address, t.debug.inspections[i].size, t.debug.inspections[i].name );
    }
    fclose(handleIns);

    (void)!system("z88dk-z80asm -l -s -b /tmp/out.asm");
    (void)!system("runz80 -R 8000 -L /tmp/out.lb2 -L /tmp/out.sym -Li /tmp/out.ins -l 8000 /tmp/out.bin -O /tmp/out.out -u /tmp/out.lis");
    FILE * handle = fopen( "/tmp/out.out", "rt" );
    (void)!fscanf(handle, "%x %x %x %x %x %x %x %x", &t.state.a, &t.state.b, &t.state.c, &t.state.d, &t.state.e, &t.state.f, &t.state.h, &t.state.l );
    while( !feof(handle) ) {
        char realname[MAX_TEMPORARY_STORAGE];
        int address;
        unsigned int memory[4];
        (void)!fscanf(handle, "%s", realname);

        if ( feof(handle) ) {
            break;
        }
        
        for( i=0; i<t.debug.inspections_count; ++i ) {
            if ( strcmp( realname, t.debug.inspections[i].name) == 0 ) {
                t.debug.inspections[i].memory = malloc(t.debug.inspections[i].size);
                for(j=0; j<t.debug.inspections[i].size; ++j ) {
                    int v;
                    (void)!fscanf(handle, "%x", &v );
                    t.debug.inspections[i].memory[j] = ( v & 0xff );
                }
                break;
            }
        }
        if ( i<t.debug.inspections_count ) continue;

        if ( 
               strcmp( realname, "WORKING") == 0 
            || strcmp( realname, "TEMPORARY") == 0 
            || strcmp( realname, "DESCRIPTORS") == 0 
            || strcmp( realname, "USING") == 0 
        ) {
          if ( strcmp( realname, "WORKING") == 0 ) {
              int i=0;
              (void)!fscanf(handle, "%x", &t.state.working_base_address );
              for( i=0; i<1024; ++i ) {
                  (void)!fscanf(handle, "%x", &t.state.working[i] );
              }
          }
          if ( strcmp( realname, "TEMPORARY") == 0 ) {
              int i=0;
              (void)!fscanf(handle, "%x", &t.state.temporary_base_address );
              for( i=0; i<1024; ++i ) {
                  (void)!fscanf(handle, "%x", &t.state.temporary[i] );
              }
          }
          if ( strcmp( realname, "DESCRIPTORS") == 0 ) {
              int i=0;
              for( i=0; i<255; ++i ) {
                  (void)!fscanf(handle, "%x", &t.state.descriptors[i].size );
                  (void)!fscanf(handle, "%x", &t.state.descriptors[i].low );
                  (void)!fscanf(handle, "%x", &t.state.descriptors[i].high );
                  (void)!fscanf(handle, "%x", &t.state.descriptors[i].status );
              }
          }
          if ( strcmp( realname, "USING") == 0 ) {
            (void)!fscanf(handle, "%x", &t.state.xusing );
            Variable * v = variable_retrieve_by_realname( &t.environment, "USING" );
            if ( v ) {
                v->value = t.state.xusing;
            }
          }
        } else {
            int i=0;
            (void)!fscanf(handle, "%x %x %x %x %x", &address, &memory[0], &memory[1], &memory[2], &memory[3]);
            Variable * v = variable_retrieve_by_realname( &t.environment, &realname[0] );
            if ( v ) {
                switch( VT_BITWIDTH( v->type ) ) {
                    case 8:
                        v->value = VT_UNSIGN_8BIT( v->type, memory[0] );
                        break;
                    case 16:
                        v->value = VT_UNSIGN_16BIT( v->type, memory[0]+(memory[1]<<8) );
                        break;
                    case 32:
                        v->value = VT_UNSIGN_32BIT( v->type, memory[0]+(memory[1]<<8)+(memory[2]<<16)+(memory[3]<<24) ) ;
                        break;
                    case 0:
                        switch( v->type ) {
                            case VT_DSTRING: {
                                v->value = memory[0];
                                v->valueString = malloc(t.state.descriptors[v->value].size+1);
                                v->size = t.state.descriptors[v->value].size;
                                memset(v->valueString,0,t.state.descriptors[v->value].size+1);
                                if ( ( t.state.descriptors[v->value].status & 0x80 ) == 0 && ( t.state.descriptors[v->value].status & 0x40 ) == 0x40 ) {
                                    unsigned int baseAddress = ( ( t.state.descriptors[v->value].low & 0xff ) | ( t.state.descriptors[v->value].high & 0xff ) << 8 );
                                    for( i=0; i<v->size; ++i ) {
                                        if ( ! t.state.xusing ) {
                                            v->valueString[i] = t.state.working[baseAddress-t.state.working_base_address+i];
                                        } else {
                                            v->valueString[i] = t.state.temporary[baseAddress-t.state.temporary_base_address+i];
                                        }
                                    }
                                }
                                break;
                            }
                            case VT_STRING:
                                v->size = memory[0];
                                break;
                        }
                }
            }

        }

    }
    if ( ! _tester( &t ) ) {
        printf("%s : ", _name);
        printf("\e[31mFAILED\e[0m");
        printf("\n");
    } else {
        printf("\e[0m.\e[0m");
    };

}

void stop_test( Environment * _environment ) {
    outline0("HALT");
}


#endif