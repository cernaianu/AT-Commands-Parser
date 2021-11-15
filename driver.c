#include <stdio.h>
#include <stdint.h>
#include "parser.h"

void print_data(){
    printf("Captured data:\n");
    for(int i=0;i<=date.line_count;i++)
            printf("%s\n",date.data[i]);
}

int main(int argc, char* args[])
{

    FILE *input_file;

    input_file = fopen(args[1], "rb");

    uint8_t buffer[50000];

    uint8_t state;
    int nr = fread(buffer, 1, 50000, input_file );
    uint8_t crt_chr ;
    int index = 0;

    do
    {
       
       crt_chr = buffer[index++];
       state = at_command_parse(crt_chr);
       
    } while (!state);


    if(date.line_count == 0)
    {
        printf("No data to display.\n");
    }
    else print_data();
   
    if(state == 1)
        printf("Parser ended with success.\n");
    if(state == 2)
        {
            printf("Parser ended with error.\n");
            if(date.line_count == AT_COMMAND_MAX_LINES - 1)
                printf("Max number of lines reached!\n");
            else printf("Incorrect format of input file.\n");
        }
    fclose(input_file);

}