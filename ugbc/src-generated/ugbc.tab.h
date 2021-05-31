/* A Bison parser, made by GNU Bison 3.7.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_SRC_GENERATED_UGBC_TAB_H_INCLUDED
# define YY_YY_SRC_GENERATED_UGBC_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    Remark = 258,                  /* Remark  */
    NewLine = 259,                 /* NewLine  */
    OP_SEMICOLON = 260,            /* OP_SEMICOLON  */
    OP_COLON = 261,                /* OP_COLON  */
    OP_COMMA = 262,                /* OP_COMMA  */
    OP_PLUS = 263,                 /* OP_PLUS  */
    OP_MINUS = 264,                /* OP_MINUS  */
    OP_INC = 265,                  /* OP_INC  */
    OP_DEC = 266,                  /* OP_DEC  */
    OP_EQUAL = 267,                /* OP_EQUAL  */
    OP_ASSIGN = 268,               /* OP_ASSIGN  */
    OP_LT = 269,                   /* OP_LT  */
    OP_LTE = 270,                  /* OP_LTE  */
    OP_GT = 271,                   /* OP_GT  */
    OP_GTE = 272,                  /* OP_GTE  */
    OP_DISEQUAL = 273,             /* OP_DISEQUAL  */
    OP_MULTIPLICATION = 274,       /* OP_MULTIPLICATION  */
    OP_DOLLAR = 275,               /* OP_DOLLAR  */
    OP_DIVISION = 276,             /* OP_DIVISION  */
    QM = 277,                      /* QM  */
    HAS = 278,                     /* HAS  */
    IS = 279,                      /* IS  */
    OF = 280,                      /* OF  */
    OP_HASH = 281,                 /* OP_HASH  */
    OP_POW = 282,                  /* OP_POW  */
    RASTER = 283,                  /* RASTER  */
    DONE = 284,                    /* DONE  */
    AT = 285,                      /* AT  */
    COLOR = 286,                   /* COLOR  */
    BORDER = 287,                  /* BORDER  */
    WAIT = 288,                    /* WAIT  */
    NEXT = 289,                    /* NEXT  */
    WITH = 290,                    /* WITH  */
    BANK = 291,                    /* BANK  */
    SPRITE = 292,                  /* SPRITE  */
    DATA = 293,                    /* DATA  */
    FROM = 294,                    /* FROM  */
    OP = 295,                      /* OP  */
    CP = 296,                      /* CP  */
    ENABLE = 297,                  /* ENABLE  */
    DISABLE = 298,                 /* DISABLE  */
    HALT = 299,                    /* HALT  */
    ECM = 300,                     /* ECM  */
    BITMAP = 301,                  /* BITMAP  */
    SCREEN = 302,                  /* SCREEN  */
    ON = 303,                      /* ON  */
    OFF = 304,                     /* OFF  */
    ROWS = 305,                    /* ROWS  */
    VERTICAL = 306,                /* VERTICAL  */
    SCROLL = 307,                  /* SCROLL  */
    VAR = 308,                     /* VAR  */
    AS = 309,                      /* AS  */
    TEMPORARY = 310,               /* TEMPORARY  */
    XPEN = 311,                    /* XPEN  */
    YPEN = 312,                    /* YPEN  */
    PEEK = 313,                    /* PEEK  */
    GOTO = 314,                    /* GOTO  */
    HORIZONTAL = 315,              /* HORIZONTAL  */
    MCM = 316,                     /* MCM  */
    COMPRESS = 317,                /* COMPRESS  */
    EXPAND = 318,                  /* EXPAND  */
    LOOP = 319,                    /* LOOP  */
    REPEAT = 320,                  /* REPEAT  */
    WHILE = 321,                   /* WHILE  */
    TEXT = 322,                    /* TEXT  */
    TILES = 323,                   /* TILES  */
    COLORMAP = 324,                /* COLORMAP  */
    SELECT = 325,                  /* SELECT  */
    MONOCOLOR = 326,               /* MONOCOLOR  */
    MULTICOLOR = 327,              /* MULTICOLOR  */
    COLLISION = 328,               /* COLLISION  */
    IF = 329,                      /* IF  */
    THEN = 330,                    /* THEN  */
    HIT = 331,                     /* HIT  */
    BACKGROUND = 332,              /* BACKGROUND  */
    TO = 333,                      /* TO  */
    RANDOM = 334,                  /* RANDOM  */
    BYTE = 335,                    /* BYTE  */
    WORD = 336,                    /* WORD  */
    POSITION = 337,                /* POSITION  */
    CODE = 338,                    /* CODE  */
    VARIABLES = 339,               /* VARIABLES  */
    MS = 340,                      /* MS  */
    CYCLES = 341,                  /* CYCLES  */
    WIDTH = 342,                   /* WIDTH  */
    HEIGHT = 343,                  /* HEIGHT  */
    DWORD = 344,                   /* DWORD  */
    PEN = 345,                     /* PEN  */
    CLEAR = 346,                   /* CLEAR  */
    BEG = 347,                     /* BEG  */
    END = 348,                     /* END  */
    GAMELOOP = 349,                /* GAMELOOP  */
    ENDIF = 350,                   /* ENDIF  */
    UP = 351,                      /* UP  */
    DOWN = 352,                    /* DOWN  */
    LEFT = 353,                    /* LEFT  */
    RIGHT = 354,                   /* RIGHT  */
    DEBUG = 355,                   /* DEBUG  */
    AND = 356,                     /* AND  */
    RANDOMIZE = 357,               /* RANDOMIZE  */
    GRAPHIC = 358,                 /* GRAPHIC  */
    TEXTMAP = 359,                 /* TEXTMAP  */
    POINT = 360,                   /* POINT  */
    GOSUB = 361,                   /* GOSUB  */
    RETURN = 362,                  /* RETURN  */
    POP = 363,                     /* POP  */
    OR = 364,                      /* OR  */
    ELSE = 365,                    /* ELSE  */
    NOT = 366,                     /* NOT  */
    TRUE = 367,                    /* TRUE  */
    FALSE = 368,                   /* FALSE  */
    DO = 369,                      /* DO  */
    EXIT = 370,                    /* EXIT  */
    WEND = 371,                    /* WEND  */
    UNTIL = 372,                   /* UNTIL  */
    FOR = 373,                     /* FOR  */
    STEP = 374,                    /* STEP  */
    EVERY = 375,                   /* EVERY  */
    MID = 376,                     /* MID  */
    INSTR = 377,                   /* INSTR  */
    UPPER = 378,                   /* UPPER  */
    LOWER = 379,                   /* LOWER  */
    STR = 380,                     /* STR  */
    VAL = 381,                     /* VAL  */
    STRING = 382,                  /* STRING  */
    SPACE = 383,                   /* SPACE  */
    FLIP = 384,                    /* FLIP  */
    CHR = 385,                     /* CHR  */
    ASC = 386,                     /* ASC  */
    LEN = 387,                     /* LEN  */
    MOD = 388,                     /* MOD  */
    ADD = 389,                     /* ADD  */
    MIN = 390,                     /* MIN  */
    MAX = 391,                     /* MAX  */
    SGN = 392,                     /* SGN  */
    SIGNED = 393,                  /* SIGNED  */
    ABS = 394,                     /* ABS  */
    RND = 395,                     /* RND  */
    COLORS = 396,                  /* COLORS  */
    INK = 397,                     /* INK  */
    TIMER = 398,                   /* TIMER  */
    POWERING = 399,                /* POWERING  */
    DIM = 400,                     /* DIM  */
    ADDRESS = 401,                 /* ADDRESS  */
    PROC = 402,                    /* PROC  */
    PROCEDURE = 403,               /* PROCEDURE  */
    CALL = 404,                    /* CALL  */
    OSP = 405,                     /* OSP  */
    CSP = 406,                     /* CSP  */
    SHARED = 407,                  /* SHARED  */
    MILLISECOND = 408,             /* MILLISECOND  */
    MILLISECONDS = 409,            /* MILLISECONDS  */
    TICKS = 410,                   /* TICKS  */
    GLOBAL = 411,                  /* GLOBAL  */
    PARAM = 412,                   /* PARAM  */
    PRINT = 413,                   /* PRINT  */
    DEFAULT = 414,                 /* DEFAULT  */
    USE = 415,                     /* USE  */
    PAPER = 416,                   /* PAPER  */
    INVERSE = 417,                 /* INVERSE  */
    REPLACE = 418,                 /* REPLACE  */
    XOR = 419,                     /* XOR  */
    IGNORE = 420,                  /* IGNORE  */
    NORMAL = 421,                  /* NORMAL  */
    WRITING = 422,                 /* WRITING  */
    ONLY = 423,                    /* ONLY  */
    LOCATE = 424,                  /* LOCATE  */
    CLS = 425,                     /* CLS  */
    HOME = 426,                    /* HOME  */
    CMOVE = 427,                   /* CMOVE  */
    CENTER = 428,                  /* CENTER  */
    CENTRE = 429,                  /* CENTRE  */
    TAB = 430,                     /* TAB  */
    SET = 431,                     /* SET  */
    CUP = 432,                     /* CUP  */
    CDOWN = 433,                   /* CDOWN  */
    CLEFT = 434,                   /* CLEFT  */
    CRIGHT = 435,                  /* CRIGHT  */
    CLINE = 436,                   /* CLINE  */
    XCURS = 437,                   /* XCURS  */
    YCURS = 438,                   /* YCURS  */
    MEMORIZE = 439,                /* MEMORIZE  */
    REMEMBER = 440,                /* REMEMBER  */
    HSCROLL = 441,                 /* HSCROLL  */
    VSCROLL = 442,                 /* VSCROLL  */
    TEXTADDRESS = 443,             /* TEXTADDRESS  */
    JOY = 444,                     /* JOY  */
    BIN = 445,                     /* BIN  */
    BIT = 446,                     /* BIT  */
    COUNT = 447,                   /* COUNT  */
    JOYCOUNT = 448,                /* JOYCOUNT  */
    FIRE = 449,                    /* FIRE  */
    JUP = 450,                     /* JUP  */
    JDOWN = 451,                   /* JDOWN  */
    JLEFT = 452,                   /* JLEFT  */
    JRIGHT = 453,                  /* JRIGHT  */
    JFIRE = 454,                   /* JFIRE  */
    INKEY = 455,                   /* INKEY  */
    SCANCODE = 456,                /* SCANCODE  */
    SCAN = 457,                    /* SCAN  */
    SHIFT = 458,                   /* SHIFT  */
    SCANSHIFT = 459,               /* SCANSHIFT  */
    BOTH = 460,                    /* BOTH  */
    SHIFTS = 461,                  /* SHIFTS  */
    NONE = 462,                    /* NONE  */
    LETTER = 463,                  /* LETTER  */
    ASTERISK = 464,                /* ASTERISK  */
    COLON = 465,                   /* COLON  */
    COMMA = 466,                   /* COMMA  */
    COMMODORE = 467,               /* COMMODORE  */
    CONTROL = 468,                 /* CONTROL  */
    CRSR = 469,                    /* CRSR  */
    CURSOR = 470,                  /* CURSOR  */
    DELETE = 471,                  /* DELETE  */
    EQUAL = 472,                   /* EQUAL  */
    FUNCTION = 473,                /* FUNCTION  */
    INSERT = 474,                  /* INSERT  */
    ARROW = 475,                   /* ARROW  */
    MINUS = 476,                   /* MINUS  */
    PERIOD = 477,                  /* PERIOD  */
    PLUS = 478,                    /* PLUS  */
    POUND = 479,                   /* POUND  */
    RUNSTOP = 480,                 /* RUNSTOP  */
    RUN = 481,                     /* RUN  */
    STOP = 482,                    /* STOP  */
    SEMICOLON = 483,               /* SEMICOLON  */
    SLASH = 484,                   /* SLASH  */
    KEY = 485,                     /* KEY  */
    STATE = 486,                   /* STATE  */
    KEYSTATE = 487,                /* KEYSTATE  */
    KEYSHIFT = 488,                /* KEYSHIFT  */
    CAPSLOCK = 489,                /* CAPSLOCK  */
    CAPS = 490,                    /* CAPS  */
    LOCK = 491,                    /* LOCK  */
    ALT = 492,                     /* ALT  */
    INPUT = 493,                   /* INPUT  */
    FREE = 494,                    /* FREE  */
    TILEMAP = 495,                 /* TILEMAP  */
    A = 496,                       /* A  */
    B = 497,                       /* B  */
    C = 498,                       /* C  */
    D = 499,                       /* D  */
    E = 500,                       /* E  */
    F = 501,                       /* F  */
    G = 502,                       /* G  */
    H = 503,                       /* H  */
    I = 504,                       /* I  */
    J = 505,                       /* J  */
    K = 506,                       /* K  */
    L = 507,                       /* L  */
    M = 508,                       /* M  */
    N = 509,                       /* N  */
    O = 510,                       /* O  */
    P = 511,                       /* P  */
    Q = 512,                       /* Q  */
    R = 513,                       /* R  */
    S = 514,                       /* S  */
    T = 515,                       /* T  */
    U = 516,                       /* U  */
    V = 517,                       /* V  */
    X = 518,                       /* X  */
    Y = 519,                       /* Y  */
    W = 520,                       /* W  */
    Z = 521,                       /* Z  */
    F1 = 522,                      /* F1  */
    F2 = 523,                      /* F2  */
    F3 = 524,                      /* F3  */
    F4 = 525,                      /* F4  */
    F5 = 526,                      /* F5  */
    F6 = 527,                      /* F6  */
    F7 = 528,                      /* F7  */
    F8 = 529,                      /* F8  */
    BLACK = 530,                   /* BLACK  */
    WHITE = 531,                   /* WHITE  */
    RED = 532,                     /* RED  */
    CYAN = 533,                    /* CYAN  */
    VIOLET = 534,                  /* VIOLET  */
    GREEN = 535,                   /* GREEN  */
    BLUE = 536,                    /* BLUE  */
    YELLOW = 537,                  /* YELLOW  */
    ORANGE = 538,                  /* ORANGE  */
    BROWN = 539,                   /* BROWN  */
    LIGHT = 540,                   /* LIGHT  */
    DARK = 541,                    /* DARK  */
    GREY = 542,                    /* GREY  */
    GRAY = 543,                    /* GRAY  */
    MAGENTA = 544,                 /* MAGENTA  */
    PURPLE = 545,                  /* PURPLE  */
    LAVENDER = 546,                /* LAVENDER  */
    GOLD = 547,                    /* GOLD  */
    TURQUOISE = 548,               /* TURQUOISE  */
    TAN = 549,                     /* TAN  */
    PINK = 550,                    /* PINK  */
    PEACH = 551,                   /* PEACH  */
    OLIVE = 552,                   /* OLIVE  */
    Identifier = 553,              /* Identifier  */
    String = 554,                  /* String  */
    Integer = 555                  /* Integer  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 25 "src/ugbc.y"

    int integer;
    char * string;

#line 369 "src-generated/ugbc.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void * _environment);

#endif /* !YY_YY_SRC_GENERATED_UGBC_TAB_H_INCLUDED  */
