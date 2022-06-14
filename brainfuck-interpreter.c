#include <stdio.h>
#include <malloc.h>
#include "int_stack.h"

void interpret_brainfuck_code(char *brainfuck_source_code){
    int_stack loop_stack;
    loop_stack.size = 0;
    int data_pointer = 0;
    char *data_buffer = (char*)(malloc(sizeof(char)*30000));
    int src_iterator = 0;
    char current_command = *(brainfuck_source_code+src_iterator);
    while (current_command != '\0'){
        switch (current_command)
        {
            case '>':
            {
                data_pointer++;
                src_iterator++;
                break;
            }
            case '<':
            {
                data_pointer--;
                src_iterator++;
                break;
            }
            case '+':
            {
                data_buffer[data_pointer]++;
                src_iterator++;
                break;
            }
            case '-':
            {
                data_buffer[data_pointer]--;
                src_iterator++;
                break;
            }
            case '.':
            {
                printf("%c",data_buffer[data_pointer]);
                src_iterator++;
                break;
            }
            case ',':
            {
                data_buffer[data_pointer] = getchar();
                src_iterator++;
                break;
            }
            case '[':
            {       
                if(data_buffer[data_pointer]==0){
                    int iterator_to_jump = src_iterator + 1;
                    while(*(brainfuck_source_code+iterator_to_jump)!=']'){
                        iterator_to_jump++;
                    }
                    src_iterator = iterator_to_jump+1;
                }
                else{
                    push_stack(&loop_stack,src_iterator);
                    src_iterator++;
                }
                break;
            }
            case ']':
            {   
                if(data_buffer[data_pointer]==0){
                    src_iterator++;
                }
                else{
                src_iterator = pop_stack(&loop_stack);
                }
                break;
            }
            default:
            {
                src_iterator++;
                break;
            }
        }
        current_command = *(brainfuck_source_code+src_iterator);
    }
    puts("\n");
}


char* read_file_to_string(char* file_path ){
    char* buffer = 0;
    long file_length;
    FILE* file_ptr = fopen(file_path,"r");
    if(file_ptr){
        fseek(file_ptr,0,SEEK_END);
        file_length = ftell(file_ptr);
        fseek(file_ptr,0,SEEK_SET);
        buffer = malloc(file_length*sizeof(char));
        if(buffer){
            fread(buffer,sizeof(char),file_length,file_ptr);
        }
   
    }
    fclose(file_ptr);
    return buffer;
}

int main(int argc,char *argv[]){
    
    char* file_to_interpret_path = "./main.bf";
    if(argc == 2){
        file_to_interpret_path = argv[1];
    }
    char* text = read_file_to_string(file_to_interpret_path);
    interpret_brainfuck_code(text);
    return 0;
}

