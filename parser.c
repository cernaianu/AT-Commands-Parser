#include <stdint.h>
#include "parser.h"
#include <stdio.h>




STATE_MACHINE_RETURN_VALUE at_command_parse(uint8_t character_crt)
{
    static uint8_t stare = 0;
    static uint8_t index_col = 0;

    //DEBUGGING
    //FILE * f_write;
    // f_write = fopen("state_output", "a+");
    // fprintf(f_write, "Current state:%d current line: %s (line-count:%d; colon:%d)\n", stare, date.data[date.line_count], date.line_count, index_col);
    // fclose(f_write);
    //DEBUGGIN

    switch(stare)
    {
        case 0:
        {
            if(character_crt == 13) //CR
            {
                stare = 1;
                return STATE_MACHINE_NOT_READY;
            }
                
            else return STATE_MACHINE_READY_WITH_ERROR;
        }
        case 1:
        {
            if(character_crt == 10) //LF
            {
                stare = 2;
                return STATE_MACHINE_NOT_READY;
            }
            else return STATE_MACHINE_READY_WITH_ERROR;
        }
        case 2:
        {
            if(character_crt == 79) //O
            {
                stare = 3;
                return STATE_MACHINE_NOT_READY;
            }
            else if(character_crt == 69) // E
            {
                stare = 7;
                return STATE_MACHINE_NOT_READY;
            }
            else if(character_crt == 43) //+
            {
                stare = 11;
                return STATE_MACHINE_NOT_READY;
            }
            else return STATE_MACHINE_READY_WITH_ERROR;
        }
        case 3:
        {
            if(character_crt == 75) //K
            {
                stare = 4;
                return STATE_MACHINE_NOT_READY;
            }
            else return STATE_MACHINE_READY_WITH_ERROR;
        }
        case 4:
        {
            if(character_crt == 13) //CR
            {
                stare = 5;
                return STATE_MACHINE_NOT_READY;
            }
            else return STATE_MACHINE_READY_WITH_ERROR;
        }
        case 5:
        {
            if(character_crt == 10) //LF
            {
                stare = 6;
                return STATE_MACHINE_NOT_READY;
            }
            else return STATE_MACHINE_READY_WITH_ERROR;
        }
        case 6:
        {
            return STATE_MACHINE_READY_OK;
        }
        case 7:
        {
            if(character_crt == 82) //R
            {
                stare = 8;
                return STATE_MACHINE_NOT_READY;
            }
            else return STATE_MACHINE_READY_WITH_ERROR;
        }
        case 8:
        {
            if(character_crt == 82) //R
            {
                stare = 9;
                return STATE_MACHINE_NOT_READY;
            }
            else return STATE_MACHINE_READY_WITH_ERROR;
        }
        case 9:
        {
            if(character_crt == 79) //O
            {
                stare = 10;
                return STATE_MACHINE_NOT_READY;
            }
            else return STATE_MACHINE_READY_WITH_ERROR;
        }
        case 10:
        {
            if(character_crt == 82) //R
            {
                stare = 4;
                return STATE_MACHINE_NOT_READY;
            }
            else return STATE_MACHINE_READY_WITH_ERROR;
        }
        case 11:
        {
            if(character_crt >= 32 && character_crt <= 126) //anychar
            {
                
                if(index_col < AT_COMMAND_MAX_LINE_SIZE - 1)
                {
                    date.data[date.line_count][index_col] = character_crt;
                    index_col++;
                    return STATE_MACHINE_NOT_READY;
                }
                else return STATE_MACHINE_READY_WITH_ERROR;
            }
            else if(character_crt == 13)//CR
            {
                stare = 12;
                
                if(index_col < AT_COMMAND_MAX_LINE_SIZE - 1)
                {
                    date.data[date.line_count][index_col] = '\0';
                    
                    return STATE_MACHINE_NOT_READY;
                }
                else return STATE_MACHINE_READY_WITH_ERROR;
            }
            else
            {
                return STATE_MACHINE_READY_WITH_ERROR;
            }
        }
        case 12:
        {
            if(character_crt == 10)//LF
            {
                stare = 13;
                
                if(date.line_count < AT_COMMAND_MAX_LINES - 1)
                {
                    
                    date.line_count++;
                    index_col = 0;
                    return STATE_MACHINE_NOT_READY;
                }
               
               else return STATE_MACHINE_READY_WITH_ERROR;
            }
            else return STATE_MACHINE_READY_WITH_ERROR;
        }
        case 13:
        {
            if(character_crt == 43)//+
            {
                stare = 11;
                return STATE_MACHINE_NOT_READY;
            }
            else if(character_crt == 13)//CR
            {
                stare = 14;
                return STATE_MACHINE_NOT_READY;
            }
            else return STATE_MACHINE_READY_WITH_ERROR;
        }
        case 14:
        {
            if(character_crt == 10)//LF
            {
                stare = 15;
                return STATE_MACHINE_NOT_READY;
            }
            else return STATE_MACHINE_READY_WITH_ERROR;
        }
        case 15:
        {
            if(character_crt == 79)//O
            {
                stare = 16;
                return STATE_MACHINE_NOT_READY;
            }
            else if(character_crt == 69)//E
            {
                stare = 7;
                return STATE_MACHINE_NOT_READY;
            }
            else return STATE_MACHINE_READY_WITH_ERROR;
        }
        case 16:
        {
            if(character_crt == 75)//K
            {
                stare = 4;
                return STATE_MACHINE_NOT_READY;
            }
            else return STATE_MACHINE_READY_WITH_ERROR;

        }
        
    }
}