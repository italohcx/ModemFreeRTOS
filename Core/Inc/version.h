/*
 * version.h
 *
 *  Created on: Sep 3, 2024
 *      Author: italo
 */

#ifndef INC_VERSION_H_
#define INC_VERSION_H_

#define FW_MAJOR_VERSION  1
#define FW_MINOR_VERSION  0
#define FW_BUILD_VERSION  0


#ifdef __MCUXPRESSO
#define LOGO_NEWLINE       "\r\n"
#else
#define LOGO_NEWLINE       "\r\n"
#endif
#define LOGO \
" " LOGO_NEWLINE\
"                                  =@@@@@@@@@  " LOGO_NEWLINE\
"                                :@         *%+ " LOGO_NEWLINE\
"                              @.           +#- " LOGO_NEWLINE\
"                            +             .%@  " LOGO_NEWLINE\
"                          .+              @@   " LOGO_NEWLINE\
"                         .              -@@    " LOGO_NEWLINE\
"                        -:             @@%     " LOGO_NEWLINE\
"                        @            @@@       " LOGO_NEWLINE\
"                        @         *@@@  -@%.   " LOGO_NEWLINE\
"                        @@@: -@@@@@            " LOGO_NEWLINE\
"                          +@@@-                " LOGO_NEWLINE\
"" LOGO_NEWLINE\
" @@@         #@@@#        *@@@-@@@@@@@@@@@@@@@@ :@@@@@@@@@@@@@@@@* " LOGO_NEWLINE\
" @@@-        -@@@+        .@@@              .@@              @@@@ " LOGO_NEWLINE\
" @@@:        -@@@*         @@@     @@@@@@@@@@    @@@@@@@@@@@ @@@@ " LOGO_NEWLINE\
" @@@         +@@@*         @@@.   @@@            @@@         @@@@ " LOGO_NEWLINE\
" @@@@@@@@@@@@*@@@@@@@@@@@@@@@@.@@@@@            .@@@@@@@@@@@@@@@@% " LOGO_NEWLINE\
"" LOGO_NEWLINE

#endif /* INC_VERSION_H_ */
