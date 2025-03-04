#/*****************************************************************************
# * ugBASIC - an isomorphic BASIC language compiler for retrocomputers        *
# *****************************************************************************
# * Copyright 2020-2023 Marco Spedaletti (asimov@mclink.it)
# *
# * Licensed under the Apache License, Version 2.0 (the "License");
# * you may not use this file except in compliance with the License.
# * You may obtain a copy of the License at
# *
# * http://www.apache.org/licenses/LICENSE-2.0
# *
# * Unless required by applicable law or agreed to in writing, software
# * distributed under the License is distributed on an "AS IS" BASIS,
# * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# * See the License for the specific language governing permissions and
# * limitations under the License.
# *----------------------------------------------------------------------------
# * Concesso in licenza secondo i termini della Licenza Apache, versione 2.0
# * (la "Licenza"); è proibito usare questo file se non in conformità alla
# * Licenza. Una copia della Licenza è disponibile all'indirizzo:
# *
# * http://www.apache.org/licenses/LICENSE-2.0
# *
# * Se non richiesto dalla legislazione vigente o concordato per iscritto,
# * il software distribuito nei termini della Licenza è distribuito
# * "COSÌ COM'È", SENZA GARANZIE O CONDIZIONI DI ALCUN TIPO, esplicite o
# * implicite. Consultare la Licenza per il testo specifico che regola le
# * autorizzazioni e le limitazioni previste dalla medesima.
# ****************************************************************************/

FLEX_OPTIONS=--8bit 
BISON_OPTIONS=--locations -d -Wcounterexamples
CFLAGS=-O3 -fomit-frame-pointer
LFLAGS=
LIBS=-lm

.PHONY: paths clean all

all: paths compiler

test: paths-test tester

#-----------------------------------------------------------------------------
#--- MAKEFILE's ENVIRONMENT
#-----------------------------------------------------------------------------

ifeq ($(OS),Windows_NT)
  EXESUFFIX = .exe
  CFLAGS += -D_WIN32 -static
  LFLAGS += -static
else
  EXESUFFIX = 
endif

# ----------------------------------------------------------------------------
# ----------------------------------------------------------------------------
# MODULES SECTION - embed ASM for each specific target
# ----------------------------------------------------------------------------
# ----------------------------------------------------------------------------

ifeq ($(debug),1)
CFLAGS += -D_DEBUG -g
endif

# ----------------------------------------------------------------------------
# DEFAULT FONT
# ----------------------------------------------------------------------------

src-generated/fontvic1.c:
	@xxd -i $(subst src-generated/,data/,$(@:.c=.bin)) >$@

src-generated/fontvic2.c:
	@xxd -i $(subst src-generated/,data/,$(@:.c=.bin)) >$@

src-generated/fonttms9918.c:
	@xxd -i $(subst src-generated/,data/,$(@:.c=.bin)) >$@

src-generated/fontcpc.c:
	@xxd -i $(subst src-generated/,data/,$(@:.c=.bin)) >$@

src-generated/fontef9345.c:
	@xxd -i $(subst src-generated/,data/,$(@:.c=.bin)) >$@

# ----------------------------------------------------------------------------
# Components and chipsets
# ----------------------------------------------------------------------------

# Motorola 6809

MODULES_6809 := $(wildcard src/hw/6809/*.asm)
SOURCES_6809 := $(subst src/hw/6809/,src-generated/6809_,$(MODULES_6809:.asm=.c))

src-generated/6809_%.c: $(MODULES_6809)
	@xxd -i $(subst src-generated/6809_,src/hw/6809/,$(@:.c=.asm)) >$@

# Motorola 6847

MODULES_6847 := $(wildcard src/hw/6847/*.asm)
SOURCES_6847 := $(subst src/hw/6847/,src-generated/6847_,$(MODULES_6847:.asm=.c))

src-generated/6847_%.c: $(MODULES_6847)
	@xxd -i $(subst src-generated/6847_,src/hw/6847/,$(@:.c=.asm)) >$@

# Thomson EF9345

MODULES_EF9345 := $(wildcard src/hw/ef9345/*.asm)
SOURCES_EF9345 := $(subst src/hw/ef9345/,src-generated/ef9345_,$(MODULES_EF9345:.asm=.c)) src-generated/fontef9345.c

src-generated/ef9345_%.c: $(MODULES_EF9345)
	@xxd -i $(subst src-generated/ef9345_,src/hw/ef9345/,$(@:.c=.asm)) >$@

# Thomson EF936x

MODULES_EF936X := $(wildcard src/hw/ef936x/*.asm)
SOURCES_EF936X := $(subst src/hw/ef936x/,src-generated/ef936x_,$(MODULES_EF936X:.asm=.c))

src-generated/ef936x_%.c: $(MODULES_EF936X)
	@xxd -i $(subst src-generated/ef936x_,src/hw/ef936x/,$(@:.c=.asm)) >$@

# MOS Technology 6502/6510

MODULES_6502 := $(wildcard src/hw/6502/*.asm)
SOURCES_6502 := $(subst src/hw/6502/,src-generated/6502_,$(MODULES_6502:.asm=.c))

src-generated/6502_%.c: $(MODULES_6502)
	@xxd -i $(subst src-generated/6502_,src/hw/6502/,$(@:.c=.asm)) >$@

# ATARI POKEY

MODULES_POKEY := $(wildcard src/hw/pokey/*.asm)
SOURCES_POKEY := $(subst src/hw/pokey/,src-generated/pokey_,$(MODULES_POKEY:.asm=.c))

src-generated/pokey_%.c: $(MODULES_POKEY)
	@xxd -i $(subst src-generated/pokey_,src/hw/pokey/,$(@:.c=.asm)) >$@

# Alphanumeric Television Interface Controller (ANTIC)

MODULES_ANTIC := $(wildcard src/hw/antic/*.asm)
SOURCES_ANTIC := $(subst src/hw/antic/,src-generated/antic_,$(MODULES_ANTIC:.asm=.c))

src-generated/antic_%.c: $(MODULES_ANTIC)
	@xxd -i $(subst src-generated/antic_,src/hw/antic/,$(@:.c=.asm)) >$@

# Color Television Interface Adaptor (CTIA) 
# Graphic Television Interface Adaptor[1] (GTIA) 

MODULES_GTIA := $(wildcard src/hw/gtia/*.asm)
SOURCES_GTIA := $(subst src/hw/gtia/,src-generated/gtia_,$(MODULES_GTIA:.asm=.c))

src-generated/gtia_%.c: $(MODULES_GTIA)
	@xxd -i $(subst src-generated/gtia_,src/hw/gtia/,$(@:.c=.asm)) >$@

# General Instrument AY-3-8910

MODULES_AY8910 := $(wildcard src/hw/ay8910/*.asm)
SOURCES_AY8910 := $(subst src/hw/ay8910/,src-generated/ay8910_,$(MODULES_AY8910:.asm=.c))

src-generated/ay8910_%.c: $(MODULES_AY8910)
	@xxd -i $(subst src-generated/ay8910_,src/hw/ay8910/,$(@:.c=.asm)) >$@

# MOS Technology VIC-I

MODULES_VIC1 := $(wildcard src/hw/vic1/*.asm)
SOURCES_VIC1 := $(subst src/hw/vic1/,src-generated/vic1_,$(MODULES_VIC1:.asm=.c)) src-generated/fontvic1.c

src-generated/vic1_%.c: $(MODULES_VIC1)
	@xxd -i $(subst src-generated/vic1_,src/hw/vic1/,$(@:.c=.asm)) >$@

# MOS Technology VIC-II

MODULES_VIC2 := $(wildcard src/hw/vic2/*.asm)
SOURCES_VIC2 := $(subst src/hw/vic2/,src-generated/vic2_,$(MODULES_VIC2:.asm=.c)) src-generated/fontvic2.c

src-generated/vic2_%.c: $(MODULES_VIC2)
	@xxd -i $(subst src-generated/vic2_,src/hw/vic2/,$(@:.c=.asm)) >$@

# MOS Technology SID

MODULES_SID := $(wildcard src/hw/sid/*.asm)
SOURCES_SID := $(subst src/hw/sid/,src-generated/sid_,$(MODULES_SID:.asm=.c))

src-generated/sid_%.c: $(MODULES_SID)
	@xxd -i $(subst src-generated/sid_,src/hw/sid/,$(@:.c=.asm)) >$@

# MOS Technology TED

MODULES_TED := $(wildcard src/hw/ted/*.asm)
SOURCES_TED := $(subst src/hw/ted/,src-generated/ted_,$(MODULES_TED:.asm=.c))

src-generated/ted_%.c: $(MODULES_TED)
	@xxd -i $(subst src-generated/ted_,src/hw/ted/,$(@:.c=.asm)) >$@

# Texas Instruments SN76489

MODULES_SN76489 := $(wildcard src/hw/sn76489/*.asm)
SOURCES_SN76489 := $(subst src/hw/sn76489/,src-generated/sn76489_,$(MODULES_SN76489:.asm=.c))

src-generated/sn76489_%.c: $(MODULES_SN76489)
	@xxd -i $(subst src-generated/sn76489_,src/hw/sn76489/,$(@:.c=.asm)) >$@

# Texas Instruments TMS9918

MODULES_TMS9918 := $(wildcard src/hw/tms9918/*.asm)
SOURCES_TMS9918 := $(subst src/hw/tms9918/,src-generated/tms9918_,$(MODULES_TMS9918:.asm=.c))  src-generated/fonttms9918.c

src-generated/tms9918_%.c: $(MODULES_TMS9918)
	@xxd -i $(subst src-generated/tms9918_,src/hw/tms9918/,$(@:.c=.asm)) >$@

# Zilog Z80

MODULES_Z80 := $(wildcard src/hw/z80/*.asm)
SOURCES_Z80 := $(subst src/hw/z80/,src-generated/z80_,$(MODULES_Z80:.asm=.c))

src-generated/z80_%.c: $(MODULES_Z80)
	@xxd -i $(subst src-generated/z80_,src/hw/z80/,$(@:.c=.asm)) >$@

# ----------------------------------------------------------------------------
# Computers and targets
# ----------------------------------------------------------------------------

# ATARI computer family

MODULES_ATARI := $(wildcard src/hw/atari/*.asm)
SOURCES_ATARI := $(subst src/hw/atari/,src-generated/atari_,$(MODULES_ATARI:.asm=.c))

src-generated/atari_%.c: $(MODULES_ATARI)
	@xxd -i $(subst src-generated/atari_,src/hw/atari/,$(@:.c=.asm)) >$@

src-generated/modules_atari.c: $(SOURCES_6502) $(SOURCES_ANTIC) $(SOURCES_ATARI) $(SOURCES_GTIA) $(SOURCES_POKEY)
	@cat $(SOURCES_6502) $(SOURCES_ANTIC) $(SOURCES_ATARI) $(SOURCES_GTIA) $(SOURCES_POKEY) >src-generated/modules_atari.c
	@grep "src" src-generated/modules_atari.c | awk -f modules.awk >src-generated/modules_atari.h
	@grep "data" src-generated/modules_atari.c | awk -f modules.awk >>src-generated/modules_atari.h

src-generated/modules_atarixl.c: $(SOURCES_6502) $(SOURCES_ANTIC) $(SOURCES_ATARI) $(SOURCES_GTIA)  $(SOURCES_POKEY)
	@cat $(SOURCES_6502) $(SOURCES_ANTIC) $(SOURCES_ATARI) $(SOURCES_GTIA) $(SOURCES_POKEY) >src-generated/modules_atarixl.c
	@grep "src" src-generated/modules_atarixl.c | awk -f modules.awk >src-generated/modules_atarixl.h
	@grep "data" src-generated/modules_atarixl.c | awk -f modules.awk >>src-generated/modules_atarixl.h

# Amstrad CPC464

MODULES_CPC := $(wildcard src/hw/cpc/*.asm)
SOURCES_CPC := $(subst src/hw/cpc/,src-generated/cpc_,$(MODULES_CPC:.asm=.c))

src-generated/cpc_%.c: $(MODULES_CPC)
	@xxd -i $(subst src-generated/cpc_,src/hw/cpc/,$(@:.c=.asm)) >$@

src-generated/modules_cpc.c: $(SOURCES_Z80) $(SOURCES_CPC) $(SOURCES_AY8910) src-generated/fontcpc.c
	@cat $(SOURCES_Z80) $(SOURCES_CPC) $(SOURCES_AY8910) src-generated/fontcpc.c >src-generated/modules_cpc.c
	@grep "src" src-generated/modules_cpc.c | awk -f modules.awk >src-generated/modules_cpc.h
	@grep "data" src-generated/modules_cpc.c | awk -f modules.awk >>src-generated/modules_cpc.h

# ColecoVision

MODULES_COLECO := $(wildcard src/hw/coleco/*.asm)
SOURCES_COLECO := $(subst src/hw/coleco/,src-generated/coleco_,$(MODULES_COLECO:.asm=.c))

src-generated/coleco_%.c: $(MODULES_COLECO)
	@xxd -i $(subst src-generated/coleco_,src/hw/coleco/,$(@:.c=.asm)) >$@

src-generated/modules_coleco.c: $(SOURCES_Z80) $(SOURCES_TMS9918) $(SOURCES_SN76489) $(SOURCES_COLECO)
	@cat $(SOURCES_Z80) $(SOURCES_TMS9918) $(SOURCES_SN76489) $(SOURCES_COLECO) >src-generated/modules_coleco.c
	@grep "src" src-generated/modules_coleco.c | awk -f modules.awk >src-generated/modules_coleco.h
	@grep "data" src-generated/modules_coleco.c | awk -f modules.awk >>src-generated/modules_coleco.h

# Commodore 128

MODULES_C128 := $(wildcard src/hw/c128/*.asm)
SOURCES_C128 := $(subst src/hw/c128/,src-generated/c128_,$(MODULES_C128:.asm=.c))

src-generated/c128_%.c: $(MODULES_C128)
	@xxd -i $(subst src-generated/c128_,src/hw/c128/,$(@:.c=.asm)) >$@

src-generated/modules_c128.c: $(SOURCES_6502) $(SOURCES_C128) $(SOURCES_VIC2) $(SOURCES_SID)
	@cat $(SOURCES_6502) $(SOURCES_C128) $(SOURCES_VIC2) $(SOURCES_SID) >src-generated/modules_c128.c
	@grep "src" src-generated/modules_c128.c | awk -f modules.awk >src-generated/modules_c128.h
	@grep "data" src-generated/modules_c128.c | awk -f modules.awk >>src-generated/modules_c128.h

# Commodore 64

MODULES_C64 := $(wildcard src/hw/c64/*.asm)
SOURCES_C64 := $(subst src/hw/c64/,src-generated/c64_,$(MODULES_C64:.asm=.c))

src-generated/c64_%.c: $(MODULES_C64)
	@xxd -i $(subst src-generated/c64_,src/hw/c64/,$(@:.c=.asm)) >$@

src-generated/modules_c64.c: $(SOURCES_6502) $(SOURCES_C64) $(SOURCES_VIC2) $(SOURCES_SID)
	@cat $(SOURCES_6502) $(SOURCES_C64) $(SOURCES_VIC2) $(SOURCES_SID) >src-generated/modules_c64.c
	@grep "src" src-generated/modules_c64.c | awk -f modules.awk >src-generated/modules_c64.h
	@grep "data" src-generated/modules_c64.c | awk -f modules.awk >>src-generated/modules_c64.h

# Commodore VIC-20

MODULES_VIC20 := $(wildcard src/hw/vic20/*.asm)
SOURCES_VIC20 := $(subst src/hw/vic20/,src-generated/vic20_,$(MODULES_VIC20:.asm=.c))

src-generated/vic20_%.c: $(MODULES_VIC20)
	@xxd -i $(subst src-generated/vic20_,src/hw/vic20/,$(@:.c=.asm)) >$@

src-generated/modules_vic20.c: $(SOURCES_6502) $(SOURCES_VIC20) $(SOURCES_VIC1)
	@cat $(SOURCES_6502) $(SOURCES_VIC20) $(SOURCES_VIC1) >src-generated/modules_vic20.c
	@grep "src" src-generated/modules_vic20.c | awk -f modules.awk >src-generated/modules_vic20.h
	@grep "data" src-generated/modules_vic20.c | awk -f modules.awk >>src-generated/modules_vic20.h

# Commodore PLUS/4

MODULES_PLUS4 := $(wildcard src/hw/plus4/*.asm)
SOURCES_PLUS4 := $(subst src/hw/plus4/,src-generated/plus4_,$(MODULES_PLUS4:.asm=.c))

src-generated/plus4_%.c: $(MODULES_PLUS4)
	@xxd -i $(subst src-generated/plus4_,src/hw/plus4/,$(@:.c=.asm)) >$@

src-generated/modules_plus4.c: $(SOURCES_6502) $(SOURCES_PLUS4) $(SOURCES_TED)
	@cat $(SOURCES_6502) $(SOURCES_PLUS4) $(SOURCES_TED) >src-generated/modules_plus4.c
	@grep "src" src-generated/modules_plus4.c | awk -f modules.awk >src-generated/modules_plus4.h
	@grep "data" src-generated/modules_plus4.c | awk -f modules.awk >>src-generated/modules_plus4.h

# TRS-80 Color Computer

MODULES_COCO := $(wildcard src/hw/coco/*.asm)
SOURCES_COCO := $(subst src/hw/coco/,src-generated/coco_,$(MODULES_COCO:.asm=.c))

src-generated/coco_%.c: $(MODULES_COCO)
	@xxd -i $(subst src-generated/coco_,src/hw/coco/,$(@:.c=.asm)) >$@

src-generated/modules_coco.c: $(SOURCES_6809) $(SOURCES_6847) $(SOURCES_COCO)
	@cat $(SOURCES_6809) $(SOURCES_6847) $(SOURCES_COCO) >src-generated/modules_coco.c
	@grep "src" src-generated/modules_coco.c | awk -f modules.awk >src-generated/modules_coco.h
	@grep "data" src-generated/modules_coco.c | awk -f modules.awk >>src-generated/modules_coco.h

# Dragon 32

MODULES_D32 := $(wildcard src/hw/d32/*.asm)
SOURCES_D32 := $(subst src/hw/d32/,src-generated/d32_,$(MODULES_D32:.asm=.c))

src-generated/d32_%.c: $(MODULES_D32)
	@xxd -i $(subst src-generated/d32_,src/hw/d32/,$(@:.c=.asm)) >$@

src-generated/modules_d32.c: $(SOURCES_6809) $(SOURCES_6847) $(SOURCES_D32)
	@cat $(SOURCES_6809) $(SOURCES_6847) $(SOURCES_D32) >src-generated/modules_d32.c
	@grep "src" src-generated/modules_d32.c | awk -f modules.awk >src-generated/modules_d32.h
	@grep "data" src-generated/modules_d32.c | awk -f modules.awk >>src-generated/modules_d32.h

# Dragon 64

MODULES_D64 := $(wildcard src/hw/d64/*.asm)
SOURCES_D64 := $(subst src/hw/d64/,src-generated/d64_,$(MODULES_D64:.asm=.c))

src-generated/d64_%.c: $(MODULES_D64)
	@xxd -i $(subst src-generated/d64_,src/hw/d64/,$(@:.c=.asm)) >$@

src-generated/modules_d64.c: $(SOURCES_6809) $(SOURCES_6847) $(SOURCES_D64)
	@cat $(SOURCES_6809) $(SOURCES_6847) $(SOURCES_D64) >src-generated/modules_d64.c
	@grep "src" src-generated/modules_d64.c | awk -f modules.awk >src-generated/modules_d64.h
	@grep "data" src-generated/modules_d64.c | awk -f modules.awk >>src-generated/modules_d64.h

# SEGA SC-3000

MODULES_SC3000 := $(wildcard src/hw/sc3000/*.asm)
SOURCES_SC3000 := $(subst src/hw/sc3000/,src-generated/sc3000_,$(MODULES_SC3000:.asm=.c))

src-generated/sc3000_%.c: $(MODULES_SC3000)
	@xxd -i $(subst src-generated/sc3000_,src/hw/sc3000/,$(@:.c=.asm)) >$@

src-generated/modules_sc3000.c: $(SOURCES_Z80) $(SOURCES_TMS9918) $(SOURCES_SN76489) $(SOURCES_SC3000)
	@cat $(SOURCES_Z80) $(SOURCES_TMS9918) $(SOURCES_SN76489) $(SOURCES_SC3000) >src-generated/modules_sc3000.c
	@grep "src" src-generated/modules_sc3000.c | awk -f modules.awk >src-generated/modules_sc3000.h
	@grep "data" src-generated/modules_sc3000.c | awk -f modules.awk >>src-generated/modules_sc3000.h

# SEGA SG-1000

MODULES_SG1000 := $(wildcard src/hw/sg1000/*.asm)
SOURCES_SG1000 := $(subst src/hw/sg1000/,src-generated/sg1000_,$(MODULES_SG1000:.asm=.c))

src-generated/sg1000_%.c: $(MODULES_SG1000)
	@xxd -i $(subst src-generated/sg1000_,src/hw/sg1000/,$(@:.c=.asm)) >$@

src-generated/modules_sg1000.c: $(SOURCES_Z80) $(SOURCES_TMS9918) $(SOURCES_SN76489) $(SOURCES_SG1000)
	@cat $(SOURCES_Z80) $(SOURCES_TMS9918) $(SOURCES_SN76489) $(SOURCES_SG1000) >src-generated/modules_sg1000.c
	@grep "src" src-generated/modules_sg1000.c | awk -f modules.awk >src-generated/modules_sg1000.h
	@grep "data" src-generated/modules_sg1000.c | awk -f modules.awk >>src-generated/modules_sg1000.h

# Olivetti Prodest PC 128
# Thomson MO6 serie U
# Thomson MO6 serie V
# Thomson MO6 serie W

MODULES_PC128OP := $(wildcard src/hw/pc128op/*.asm)
SOURCES_PC128OP := $(subst src/hw/pc128op/,src-generated/pc128op_,$(MODULES_PC128OP:.asm=.c))

src-generated/pc128op_%.c: $(MODULES_PC128OP)
	@xxd -i $(subst src-generated/pc128op_,src/hw/pc128op/,$(@:.c=.asm)) >$@

src-generated/modules_pc128op.c: $(SOURCES_6809) $(SOURCES_EF936X) $(SOURCES_PC128OP)
	@cat $(SOURCES_6809) $(SOURCES_EF936X) $(SOURCES_PC128OP) >src-generated/modules_pc128op.c
	@grep "src" src-generated/modules_pc128op.c | awk -f modules.awk >src-generated/modules_pc128op.h
	@grep "data" src-generated/modules_pc128op.c | awk -f modules.awk >>src-generated/modules_pc128op.h

# Thomson MO5 v1.0
# Thomson MO5 v1.2
# Thomson MO5 QW
# Thomson MO5E
# Thomson MO5E DE
# Thomson MO5N
# Thomson MO5NR

MODULES_MO5 := $(wildcard src/hw/mo5/*.asm)
SOURCES_MO5 := $(subst src/hw/mo5/,src-generated/mo5_,$(MODULES_MO5:.asm=.c))

src-generated/mo5_%.c: $(MODULES_MO5)
	@xxd -i $(subst src-generated/mo5_,src/hw/mo5/,$(@:.c=.asm)) >$@

src-generated/modules_mo5.c: $(SOURCES_6809) $(SOURCES_EF936X) $(SOURCES_MO5)
	@cat $(SOURCES_6809) $(SOURCES_EF936X) $(SOURCES_MO5) >src-generated/modules_mo5.c
	@grep "src" src-generated/modules_mo5.c | awk -f modules.awk >src-generated/modules_mo5.h
	@grep "data" src-generated/modules_mo5.c | awk -f modules.awk >>src-generated/modules_mo5.h

# MSX1

MODULES_MSX1 := $(wildcard src/hw/msx1/*.asm)
SOURCES_MSX1 := $(subst src/hw/msx1/,src-generated/msx1_,$(MODULES_MSX1:.asm=.c))

src-generated/msx1_%.c: $(MODULES_MSX)
	@xxd -i $(subst src-generated/msx1_,src/hw/msx1/,$(@:.c=.asm)) >$@

src-generated/modules_msx1.c: $(SOURCES_Z80) $(SOURCES_TMS9918) $(SOURCES_AY8910) $(SOURCES_MSX1)
	@cat $(SOURCES_Z80) $(SOURCES_TMS9918) $(SOURCES_AY8910) $(SOURCES_MSX1) >src-generated/modules_msx1.c
	@grep "src" src-generated/modules_msx1.c | awk -f modules.awk >src-generated/modules_msx1.h
	@grep "data" src-generated/modules_msx1.c | awk -f modules.awk >>src-generated/modules_msx1.h

# VG5000

MODULES_VG5000 := $(wildcard src/hw/vg5000/*.asm)
SOURCES_VG5000 := $(subst src/hw/vg5000/,src-generated/vg5000_,$(MODULES_VG5000:.asm=.c))

src-generated/vg5000_%.c: $(MODULES_VG5000)
	@xxd -i $(subst src-generated/vg5000_,src/hw/vg5000/,$(@:.c=.asm)) >$@

src-generated/modules_vg5000.c: $(SOURCES_Z80) $(SOURCES_VG5000) $(SOURCES_EF9345)
	@cat $(SOURCES_Z80) $(SOURCES_EF9345) $(SOURCES_VG5000) >src-generated/modules_vg5000.c
	@grep "src" src-generated/modules_vg5000.c | awk -f modules.awk >src-generated/modules_vg5000.h
	@grep "data" src-generated/modules_vg5000.c | awk -f modules.awk >>src-generated/modules_vg5000.h

# ZX Spectrum

MODULES_ZX := $(wildcard src/hw/zx/*.asm)
SOURCES_ZX := $(subst src/hw/zx/,src-generated/zx_,$(MODULES_ZX:.asm=.c))

src-generated/zx_%.c: $(MODULES_ZX)
	@xxd -i $(subst src-generated/zx_,src/hw/zx/,$(@:.c=.asm)) >$@

src-generated/modules_zx.c: $(SOURCES_Z80) $(SOURCES_ZX)
	@cat $(SOURCES_Z80) $(SOURCES_ZX) >src-generated/modules_zx.c
	@grep "src" src-generated/modules_zx.c | awk -f modules.awk >src-generated/modules_zx.h
	@grep "data" src-generated/modules_zx.c | awk -f modules.awk >>src-generated/modules_zx.h

# ----------------------------------------------------------------------------
# ----------------------------------------------------------------------------
# LEXER/PARSER SECTION
# ----------------------------------------------------------------------------
# ----------------------------------------------------------------------------

src-generated/ugbc.yy.c: src/ugbc.lex src/ugbc.y
	@flex ${FLEX_OPTIONS} --outfile=src-generated/ugbc.yy.c src/ugbc.lex

src-generated/ugbc.tab.c: src/ugbc.lex src/ugbc.y
	@bison ${BISON_OPTIONS} --file-prefix=src-generated/ugbc src/ugbc.y

src-generated/ugbc.embed.yy.c: src/ugbc.embed.lex src/ugbc.embed.y
	@flex ${FLEX_OPTIONS} --prefix=embed --outfile=src-generated/ugbc.embed.yy.c src/ugbc.embed.lex

src-generated/ugbc.embed.tab.c: src/ugbc.embed.lex src/ugbc.embed.y
	@bison ${BISON_OPTIONS} --debug -p embed --file-prefix=src-generated/ugbc.embed src/ugbc.embed.y

# ----------------------------------------------------------------------------
# ----------------------------------------------------------------------------
# COMPILATION RULES
# ----------------------------------------------------------------------------
# ----------------------------------------------------------------------------

SOURCES := $(wildcard src/*.c)
SOURCES += $(wildcard src/libs/*.c)
SOURCES += $(wildcard src/targets/*.c)
SOURCES += $(wildcard src/hw/*.c)
SOURCES += $(wildcard src/outputs/*.c)
SOURCES += $(wildcard src/targets/common/*.c)
SOURCES += $(wildcard src/targets/$(target)/*.c)
SOURCES += src-generated/ugbc.yy.c src-generated/ugbc.tab.c src-generated/ugbc.embed.yy.c src-generated/ugbc.embed.tab.c src-generated/modules_$(target).c

OBJS = $(SOURCES:%.c=objs.$(target)/%.o)

SOURCESTEST := $(wildcard src/*.c)
SOURCESTEST += $(wildcard src/libs/*.c)
SOURCESTEST += $(wildcard src/targets/*.c)
SOURCESTEST += $(wildcard src/hw/*.c)
SOURCESTEST += $(wildcard src/targets/common/*.c)
SOURCESTEST += $(wildcard src/targets/$(target)/*.c)
SOURCESTEST += $(wildcard src-test/suites/*.c)
SOURCESTEST += src-generated/modules_$(target).c src-generated/ugbc.embed.yy.c src-generated/ugbc.embed.tab.c src-test/tester.c src-test/tester_c64.c src-test/tester_plus4.c src-test/tester_atari.c src-test/tester_atarixl.c src-test/tester_coleco.c src-test/tester_msx1.c src-test/tester_coco.c src-test/tester_zx.c src-test/tester_d32.c src-test/tester_d64.c src-test/tester_pc128op.c src-test/tester_mo5.c src-test/tester_vic20.c src-test/tester_sc3000.c src-test/tester_sg1000.c src-test/tester_c128.c

paths:
	@mkdir -p src-generated
	@mkdir -p exe

paths-test:
	@mkdir -p exe-test

compiler: $(OBJS)
	@$(CC) $(LFLAGS) $^ -o exe/ugbc.$(target)$(EXESUFFIX) $(LIBS)
	
objs.$(target)/%.o: %.c src-generated/ugbc.yy.c src-generated/ugbc.tab.c src-generated/ugbc.embed.yy.c src-generated/ugbc.embed.tab.c src-generated/modules_$(target).c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -D__$(target)__  -c $< -o $@

tester: $(SOURCESTEST)
	@$(CC) $(CFLAGS) -D__$(target)__ $(SOURCESTEST) -o exe-test/ugbc.$(target)$(EXESUFFIX) -lm

clean:
	@rm -rf objs.$(target)/*
	@rm -f exe/ugbc.*
	@rm -f src-generated/*.c
	@rm -f src-generated/*.h
	@rm -f exe-test/ugbc.*

