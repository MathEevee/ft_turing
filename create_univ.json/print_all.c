#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>


void go_back_memory (void)
{
    printf("\t\t\"go_back_memory\" : [\n");
    int i = 32;
    while (i < 127)
    {
        if (i == '_')
        {
            i++;
            continue;
        }
        if ((i >= 'a' && i <= 'z') || i == 'H' || i == 'R' || i == 'L' || i == '_' || i == '|' )
            printf("\t\t\t{ \"read\": \"%c\", \"to_state\": \"go_back_memory\", \"write\": \"%c\", \"action\": \"LEFT\" },\n", i,i);
        i++;
    }
    printf("\t\t\t{ \"read\": \"#\", \"to_state\": \"go_back_transition\", \"write\": \"#\", \"action\": \"LEFT\" }\n");
    printf("\t\t],\n");
}

void go_back_transition (void)
{
    printf("\t\t\"go_back_transition\" : [\n");
    int i = 32;
    while (i < 127)
    {
        if ((i >= 'a' && i <= 'z') || i == 'H' || i == 'R' || i == 'L' || i == '|')
            printf("\t\t\t{ \"read\": \"%c\", \"to_state\": \"go_back_transition\", \"write\": \"%c\", \"action\": \"LEFT\" },\n", i,i);
        i++;
    }
    printf("\t\t\t{ \"read\": \"_\", \"to_state\": \"search_next_trans\", \"write\": \"|\", \"action\": \"RIGHT\" },\n");
    printf("\t\t\t{ \"read\": \"#\", \"to_state\": \"go_back_curr_state\", \"write\": \"#\", \"action\": \"LEFT\" }\n");
    printf("\t\t],\n");
}

void go_back_curr_state (void)
{
    printf("\t\t\"go_back_curr_state\" : [\n");
    int i = 32;
    while (i < 127)
    {
        if ((i >= 'a' && i <= 'z') || i == 'H')
            printf("\t\t\t{ \"read\": \"%c\", \"to_state\": \"go_back_curr_state\", \"write\": \"%c\", \"action\": \"LEFT\" },\n", i,i);
        i++;
    }
    printf("\t\t\t{ \"read\": \"_\", \"to_state\": \"search_next_trans\", \"write\": \"_\", \"action\": \"RIGHT\" },\n");
    printf("\t\t\t{ \"read\": \"#\", \"to_state\": \"go_back_input\", \"write\": \"#\", \"action\": \"LEFT\" }\n");
    printf("\t\t],\n");
}

void go_back_input (void)
{
    printf("\t\t\"go_back_input\" : [\n");
    int i = 32;
    while (i < 127)
    {
        if ((i >= '0' && i <= '9') || i == '+' || i == '-' || i == '=' || i == '.')
            printf("\t\t\t{ \"read\": \"%c\", \"to_state\": \"go_back_input\", \"write\": \"%c\", \"action\": \"LEFT\" },\n", i,i);
        i++;
    }
    printf("\t\t\t{ \"read\": \"_\", \"to_state\": \"get_curr_state\", \"write\": \"_\", \"action\": \"RIGHT\" }\n");
    printf("\t\t],\n");
}

void get_head(void)
{
    printf("\t\t\"get_head\" : [\n");
    int i = 32;
    while (i < 127)
    {
        if ((i >= '0' && i <= '9') || i ==  '.' || i == '+' || i == '-' || i == '.' || i == '=')
            printf("\t\t\t{ \"read\": \"%c\", \"to_state\": \"save_%c\", \"write\": \"%c\", \"action\": \"RIGHT\" },\n", i, i,i);
        i++;
    }
    printf("\t\t\t{ \"read\": \"_\", \"to_state\": \"save_.\", \"write\": \".\", \"action\": \"RIGHT\" },\n");
    printf("\t\t\t{ \"read\": \"#\", \"to_state\": \"copy_.\", \"write\": \"#\", \"action\": \"LEFT\" }\n");
    printf("\t\t],\n");
}

void save_(char input, bool states)
{
    if (input == '#' || input == '|' || input == '_')
        return;
    if (states == true)
    {
        printf("\"save_%c\",\n", input);
        return;
    } 
    printf("\t\t\"save_%c\" : [\n", input);
    int i = 32;
    while (i < 127)
    {
        if ((i >= 'a' && i <= 'z') || (i >= '0' && i <= '9') || i == '-' || i ==  '.' || i == '+' || i == '=')
            printf("\t\t\t{ \"read\": \"%c\", \"to_state\": \"save_%c\", \"write\": \"%c\", \"action\": \"RIGHT\" },\n", i, input,i);
        i++;
    }
    printf("\t\t\t{ \"read\": \"_\", \"to_state\": \"go_back_memory\", \"write\": \"%c\", \"action\": \"LEFT\" }\n", input);
    printf("\t\t],\n");

}

void copy_(char input, bool states)
{
    if (input == '#' || input == '|' || (input >= 'a' && input <= 'z') || input == '_')
        return;
    if (states == true)
    {
        printf("\"copy_%c\",\n", input);
        return;
    } 
    printf("\t\t\"copy_%c\" : [\n", input);
    int i = 32;
    while (i < 127)
    {
        if ((i >= '0' && i <= '9') || i == '-' || i ==  '.' || i == '+' || i == '=')
            printf("\t\t\t{ \"read\": \"%c\", \"to_state\": \"copy_%c\", \"write\": \"%c\", \"action\": \"LEFT\" },\n", i, i,input);
        i++;
    }
    printf("\t\t\t{ \"read\": \"_\", \"to_state\": \"go_end_input\", \"write\": \"%c\", \"action\": \"RIGHT\" }\n", input);
    printf("\t\t],\n");
}

void go_end_input(void)
{
    printf("\t\t\"go_end_input\" : [\n");
    int i = 32;
    while (i < 127)
    {
        if ((i >= '0' && i <= '9') || i == '-' || i ==  '.' || i == '+' || i == '=')
            printf("\t\t\t{ \"read\": \"%c\", \"to_state\": \"go_end_input\", \"write\": \"%c\", \"action\": \"RIGHT\" },\n", i, i);
        i++;
    }
    printf("\t\t\t{ \"read\": \"#\", \"to_state\": \"get_head\", \"write\": \"#\", \"action\": \"LEFT\" }\n");
    printf("\t\t],\n");
}

void get_curr_state (void)
{
    printf("\t\t\"get_curr_state\" : [\n");
    int i = 'a';
    while (i <= 'z')
    {
        printf("\t\t\t{ \"read\": \"%c\", \"to_state\": \"save_%c\", \"write\": \"_\", \"action\": \"RIGHT\" },\n", i, i);
        i++;
    }
    printf("\t\t\t{ \"read\": \"H\", \"to_state\": \"put_back_from_memory\", \"write\": \"H\", \"action\": \"RIGHT\" }\n");
    printf("\t\t],\n");
}

void search_next_trans(void)
{
    int i = 32;
    printf("\t\t\"search_next_trans\" : [\n");
    while (i < 127)
    {
        if ((i >= 'a' && i <= 'z') || (i >= '0' && i <= '9') 
        || i == '+' || i ==  '=' || i == '-' || i ==  '.' || i == 'R' || i ==  'L' || i ==  'H')
            printf("\t\t\t{ \"read\": \"%c\", \"to_state\": \"search_next_trans\", \"write\": \"%c\", \"action\": \"RIGHT\" },\n", i, i);
        i++;
    }
    printf("\t\t\t{ \"read\": \"|\", \"to_state\": \"compare_state\", \"write\": \"_\", \"action\": \"RIGHT\" }\n");
    printf("\t\t],\n");
}

void compare_state(void)
{
    int i = 32;
    printf("\t\t\"compare_state\" : [\n");
    while (i < 127)
    {
        if ((i >= 'a' && i < 'z') || (i >= '0' && i <= '9') 
        || i == '+' || i ==  '=' || i == '-' || i ==  '.')
            printf("\t\t\t{ \"read\": \"%c\", \"to_state\": \"get_%c_in_memory\", \"write\": \"%c\", \"action\": \"RIGHT\" },\n", i, i, i);
            i++;
    }
    printf("\t\t\t{ \"read\": \"z\", \"to_state\": \"get_z_in_memory\", \"write\": \"z\", \"action\": \"RIGHT\" }\n");
    printf("\t\t],\n");
}

void get_c_in_memory (char c, bool states)
{
    if (c == '#' || c == '|' || c == '_')
        return;
    if (states == true)
    {
        printf("\"get_%c_in_memory\",\n", c);
        return;
    } 
    int i = 32;
    printf("\t\t\"get_%c_in_memory\" : [\n", c);
    while (i < 127)
    {
        if ((i >= 'a' && i <= 'z') || (i >= '0' && i <= '9') 
            || i == '+' || i ==  '=' || i == '-' || i ==  '.' || i == 'R' || i ==  'L' || i ==  'H')
            printf("\t\t\t{ \"read\": \"%c\", \"to_state\": \"get_%c_in_memory\", \"write\": \"%c\", \"action\": \"RIGHT\" },\n", i, c, i);
        i++;
    }
    printf("\t\t\t{ \"read\": \"#\", \"to_state\": \"get_%c\", \"write\": \"#\", \"action\": \"RIGHT\" }\n", c);
    printf("\t\t],\n");
}

void get_c_state(char c, char i, bool states)
{
    if (c == i)
        printf("\t\t\t{ \"read\": \"%c\", \"to_state\": \"erase_memory\", \"write\": \"_\", \"action\": \"LEFT\" },\n", c);
    else
        printf("\t\t\t{ \"read\": \"%c\", \"to_state\": \"get_%c\", \"write\": \"%c\", \"action\": \"RIGHT\" },\n", i, c, i);
}

void get_c_input(char c, char i, bool states)
{
    if (c == i)
        printf("\t\t\t{ \"read\": \"%c\", \"to_state\": \"go_back_curr_transition\", \"write\": \"%c\", \"action\": \"LEFT\" },\n", i, c);
    else
        printf("\t\t\t{ \"read\": \"%c\", \"to_state\": \"get_%c\", \"write\": \"%c\", \"action\": \"RIGHT\" },\n", i, c, i);

}

void get_c(char c, bool states)
{
    if (c == '#' || c == '|' || c == '_' || c == 'R' || c == 'L' || c == 'H')
        return;
    if (states == true)
    {
        printf("\"get_%c\",\n", c);
        return;
    }
    int i = 32;
    printf("\t\t\"get_%c\" : [\n", c);
    while (i < 127)
    {
        if ((i >= 'a' && i <= 'z'))
            get_c_state(c, i, states);
        else if ((i >= '0' && i <= '9') 
            || i == '+' || i ==  '=' || i == '-' || i ==  '.')
            get_c_input(c, i, states);
        i++;
    }
    printf("\t\t\t{ \"read\": \"_\", \"to_state\": \"go_back_memory\", \"write\": \"_\", \"action\": \"LEFT\" }\n");
    printf("\t\t],\n");
}

//last = '|'

void go_back_curr_transition(void)
{
    int i = 32;
    printf("\t\t\"go_back_curr_transition\" : [\n");
    while (i < 127)
    {
        if ((i >= 'a' && i <= 'z') || (i >= '0' && i <= '9') 
            || i == '+' || i ==  '=' || i == '-' || i ==  '.' || i == 'R' || i ==  'L' || i ==  'H' || i ==  '#' || i ==  '|')
            printf("\t\t\t{ \"read\": \"%c\", \"to_state\": \"go_back_curr_transition\", \"write\": \"%c\", \"action\": \"LEFT\" },\n", i ,i);
        i++;
    }
    printf("\t\t\t{ \"read\": \"_\", \"to_state\": \"skip_read\", \"write\": \"_\", \"action\": \"RIGHT\" }\n");
    printf("\t\t],\n");
}

void skip_read(void)
{
    int i = 32;
    printf("\t\t\"skip_read\" : [\n");
    while (i < 127)
    {
        if ((i >= '0' && i <= '9') || i == '+' || i == '-' || i ==  '.')
            printf("\t\t\t{ \"read\": \"%c\", \"to_state\": \"compare_state\", \"write\": \"%c\", \"action\": \"RIGHT\" },\n", i ,i);
        i++;
    }
    printf("\t\t\t{ \"read\": \"=\", \"to_state\": \"compare_state\", \"write\": \"=\", \"action\": \"RIGHT\" }\n");
    printf("\t\t],\n");
}

void erase_memory()
{
    int i = 32;
    printf("\t\t\"erase_memory\" : [\n");
    while (i < 127)
    {
        if ((i >= '0' && i <= '9') || i == '+' || i == '-' || i ==  '.' || i == '=')
            printf("\t\t\t{ \"read\": \"%c\", \"to_state\": \"erase_memory\", \"write\": \"_\", \"action\": \"LEFT\" },\n", i);
        i++;
    }
    printf("\t\t\t{ \"read\": \"#\", \"to_state\": \"get_next_state\", \"write\": \"#\", \"action\": \"LEFT\" }\n");
    printf("\t\t],\n");
}

void get_next_state()
{
    int i = 32;
    printf("\t\t\"get_next_state\" : [\n");
    while (i < 127)
    {
        if ((i >= 'a' && i <= 'z') || (i >= '0' && i <= '9') 
            || i == '+' || i ==  '=' || i == '-' || i ==  '.' || i == 'R' || i ==  'L' || i ==  'H' || i ==  '#' || i ==  '|')
            printf("\t\t\t{ \"read\": \"%c\", \"to_state\": \"get_next_state\", \"write\": \"%c\", \"action\": \"LEFT\" },\n", i, i);
        i++;
    }
    printf("\t\t\t{ \"read\": \"_\", \"to_state\": \"skip_curr_state\", \"write\": \"_\", \"action\": \"RIGHT\" }\n");
    printf("\t\t],\n");
}

void skip_curr_state(void)
{
    int i = 32;
    printf("\t\t\"skip_curr_state\" : [\n");
    while (i < 127)
    {
        if ((i >= '0' && i <= '9') 
            || i == '+' || i == '-' || i ==  '.')
            printf("\t\t\t{ \"read\": \"%c\", \"to_state\": \"skip_bis\", \"write\": \"%c\", \"action\": \"RIGHT\" },\n", i, i);
            i++;
    }
    printf("\t\t\t{ \"read\": \"=\", \"to_state\": \"skip_bis\", \"write\": \"=\", \"action\": \"RIGHT\" }\n");
    printf("\t\t],\n");
}

void skip_bis(void)
{
    int i = 'a';
    printf("\t\t\"skip_bis\" : [\n");
    while (i < 'z')
    {
        printf("\t\t\t{ \"read\": \"%c\", \"to_state\": \"next_state\", \"write\": \"%c\", \"action\": \"RIGHT\" },\n", i, i);
        i++;
    }
    printf("\t\t\t{ \"read\": \"z\", \"to_state\": \"next_state\", \"write\": \"z\", \"action\": \"RIGHT\" }\n");
    printf("\t\t],\n");
}

void next_state(void)
{
    int i = 32;
    printf("\t\t\"next_state\" : [\n");
    while (i < 127)
    {
        if ((i >= 'a' && i < 'z') || i ==  'H')
            printf("\t\t\t{ \"read\": \"%c\", \"to_state\": \"write_curr_state_%c\", \"write\": \"_\", \"action\": \"LEFT\" },\n", i,i);
        i++;
    }
    printf("\t\t\t{ \"read\": \"z\", \"to_state\": \"write_curr_state_z\", \"write\": \"_\", \"action\": \"LEFT\" }\n");
    printf("\t\t],\n");
}

void write_curr_state_c(char c, bool states)
{
    if ((c >= '0' && c <= '9') || c == '-' || c == '+' || c == '='
        || c == '_' || c == '-' || c == '|' || c == '#')
        return;
    if (states == true)
    {
        printf("\"write_curr_state_%c\",\n", c);
        return;
    }
    int i = 32;
    printf("\t\t\"write_curr_state_%c\" : [\n", c);
    while (i < 127)
    {
        if ((i >= 'a' && i <= 'z') || (i >= '0' && i <= '9') 
        || i == '+' || i ==  '=' || i == '-' || i ==  '.' || i == 'R' || i ==  'L' || i ==  'H' || i ==  '#' || i ==  '|')
            printf("\t\t\t{ \"read\": \"%c\", \"to_state\": \"write_curr_state_%c\", \"write\": \"%c\", \"action\": \"LEFT\" },\n", i,c, i);
        i++;
    }
    printf("\t\t\t{ \"read\": \"_\", \"to_state\": \"put_back_%c\", \"write\": \"%c\", \"action\": \"RIGHT\" }\n", c, c);
    printf("\t\t],\n");
}

void put_back_c(char c, bool states)
{
    if ((c >= '0' && c <= '9') || c == '+' || c == '=' || c == '.'
        || c == '_' || c == '-' || c == '|' || c == '#')
        return;
    if (states == true)
    {
        printf("\"put_back_%c\",\n", c);
        return;
    }
    int i = 32;
    printf("\t\t\"put_back_%c\" : [\n", c);
    while (i < 127)
    {
        if ((i >= 'a' && i <= 'z') || (i >= '0' && i <= '9') 
            || i == '+' || i ==  '=' || i == '-' || i ==  '.' || i == 'R' || i ==  'L' || i ==  'H' || i ==  '#' || i ==  '|')
            printf("\t\t\t{ \"read\": \"%c\", \"to_state\": \"put_back_%c\", \"write\": \"%c\", \"action\": \"RIGHT\" },\n", i,c, i);
        i++;
    }
    printf("\t\t\t{ \"read\": \"_\", \"to_state\": \"get_trans\", \"write\": \"%c\", \"action\": \"RIGHT\" }\n", c);
    printf("\t\t],\n");
}

void get_trans()
{
    int i = 32;
    printf("\t\t\"get_trans\" : [\n");
    while (i < 127)
    {
        if ((i >= '0' && i <= '9') 
            || i == '+' || i == '-' || i ==  '.')
            printf("\t\t\t{ \"read\": \"%c\", \"to_state\": \"get_dir_%c\", \"write\": \"%c\", \"action\": \"RIGHT\" },\n", i,i, i);
        i++;
    }
    printf("\t\t\t{ \"read\": \"=\", \"to_state\": \"get_dir_=\", \"write\": \"=\", \"action\": \"RIGHT\" }\n");
    printf("\t\t],\n");
}


void get_dir_c(char input, bool states)
{
    if ((input >= 'a' && input <= 'z')
    || input == 'R' || input ==  'L' || input ==  'H' || input ==  '#' || input ==  '|' || input == '_' || input == '#')
        return;
    if (states == true)
    {
        printf("\"get_dir_%c\",\n", input);
        return;
    }
    printf("\t\t\"get_dir_%c\" : [\n", input);
    //R
    printf("\t\t\t{ \"read\": \"R\", \"to_state\": \"apply_%c_R\", \"write\": \"R\", \"action\": \"LEFT\" },\n", input);
    //L
    printf("\t\t\t{ \"read\": \"L\", \"to_state\": \"apply_%c_L\", \"write\": \"L\", \"action\": \"LEFT\" }\n", input);

    printf("\t\t],\n");
}

void apply_c_move(char input, char move, bool states)
{
    int i = 32;
    if (states == true)
        return;

    printf("\t\t\"apply_%c_%c\" : [\n", input, move);
    while (i < 127)
    {
        if ((i >= 'a' && i <= 'z') || (i >= '0' && i <= '9') 
            || i == '+' || i ==  '=' || i == '-' || i ==  '.' || i == 'R' || i ==  'L' || i ==  'H' || i ==  '#' || i ==  '|')
            printf("\t\t\t{ \"read\": \"%c\", \"to_state\": \"apply_%c_%c\", \"write\": \"%c\", \"action\": \"LEFT\" },\n", i,input, move, i);
        i++;
    }
    if (move == 'R')
        printf("\t\t\t{ \"read\": \"_\", \"to_state\": \"get_head\", \"write\": \"%c\", \"action\": \"RIGHT\" }\n", input);
    else
        printf("\t\t\t{ \"read\": \"_\", \"to_state\": \"get_head\", \"write\": \"%c\", \"action\": \"LEFT\" }\n", input);
    printf("\t\t],\n");
}


void apply_c (char input, bool states)
{
    if ((input >= 'a' && input <= 'z')
    || input == 'R' || input ==  'L' || input ==  'H' || input ==  '#' || input ==  '|' || input == '_' || input == '#')
        return;
    if (states == true)
    {
        printf("\"apply_%c_R\",\n", input);
        printf("\"apply_%c_L\",\n", input);
        return;
    }
    apply_c_move(input, 'R', states);
    apply_c_move(input, 'L', states);
}

void put_back_from_memory(void)
{
    int i = 32;
    printf("\t\t\"put_back_from_memory\" : [\n");
    while (i < 127)
    {
        if ((i >= '0' && i <= '9') 
            || i == '+' || i ==  '=' || i == '-' || i ==  '.')
            printf("\t\t\t{ \"read\": \"%c\", \"to_state\": \"put_back_from_memory\", \"write\": \"%c\", \"action\": \"RIGHT\" },\n", i, i);
        i++;
    }
    printf("\t\t\t{ \"read\": \"_\", \"to_state\": \"what_to_wrote\", \"write\": \"_\", \"action\": \"LEFT\" }\n");
    printf("\t\t],\n");
}

void what_to_wrote(void)
{
    int i = 32;
    printf("\t\t\"what_to_wrote\" : [\n");
    while (i < 127)
    {
        if ((i >= '0' && i <= '9') 
            || i == '+' || i == '-' || i ==  '.')
            printf("\t\t\t{ \"read\": \"%c\", \"to_state\": \"write_%c\", \"write\": \"_\", \"action\": \"LEFT\" },\n", i,i);
        i++;
    }
    printf("\t\t\t{ \"read\": \"=\", \"to_state\": \"write_=\", \"write\": \"_\", \"action\": \"LEFT\" }\n");
    printf("\t\t],\n");
}

void write_c(char c, bool states)
{
    if ((c >= 'a' && c <= 'z') || c == 'R' || c ==  'L' || c ==  'H' || c ==  '#' || c ==  '|' || c == '_')
        return;
    if (states == true)
    {
        printf("\"write_%c\",\n", c);
        return;
    } 
    int i = 32;
    printf("\t\t\"write_%c\" : [\n", c);
    while (i < 127)
    {
        if ((i >= 'a' && i <= 'z') || (i >= '0' && i <= '9')
            || i == '+' || i ==  '=' || i == '-' || i ==  '.' || i == 'R' || i ==  'L' || i ==  'H' || i ==  '#' || i ==  '|')
            printf("\t\t\t{ \"read\": \"%c\", \"to_state\": \"write_%c\", \"write\": \"%c\", \"action\": \"LEFT\" },\n", i, c,i);
        i++;
    }
    printf("\t\t\t{ \"read\": \"_\", \"to_state\": \"HALT\", \"write\": \"%c\", \"action\": \"RIGHT\" }\n", c);
    printf("\t\t],\n");
}

/* ---------------------------------------- PARSING ----------------------------------------*/

void start()
{
    int i = 32;
    printf("\t\t\"start\" : [\n");
    while (i < 127)
    {
        if ((i >= '0' && i <= '9') 
            || i == '+' || i == '-' || i ==  '.')
            printf("\t\t\t{ \"read\": \"%c\", \"to_state\": \"check_input\", \"write\": \"%c\", \"action\": \"RIGHT\" },\n", i,i);
        i++;
    }
    printf("\t\t\t{ \"read\": \"=\", \"to_state\": \"check_input\", \"write\": \"=\", \"action\": \"RIGHT\" }\n");
    printf("\t\t],\n");
}

void check_input(void)
{
    int i = 32;
    printf("\t\t\"check_input\" : [\n");
    while (i < 127)
    {
        if ((i >= '0' && i <= '9') 
            || i == '+' || i ==  '=' || i == '-' || i ==  '.')
            printf("\t\t\t{ \"read\": \"%c\", \"to_state\": \"check_input\", \"write\": \"%c\", \"action\": \"RIGHT\" },\n", i,i);
        i++;
    }
    printf("\t\t\t{ \"read\": \"#\", \"to_state\": \"check_curr_state\", \"write\": \"#\", \"action\": \"RIGHT\" }\n");
    printf("\t\t],\n");
}

void check_curr_state()
{
    int i = 'a';
    printf("\t\t\"check_curr_state\" : [\n");
    while (i < 'z')
    {
        printf("\t\t\t{ \"read\": \"%c\", \"to_state\": \"transition_#\", \"write\": \"%c\", \"action\": \"RIGHT\" },\n", i,i);
        i++;
     }
    printf("\t\t\t{ \"read\": \"z\", \"to_state\": \"transition_#\", \"write\": \"z\", \"action\": \"RIGHT\" }\n");
    printf("\t\t],\n");
}

void transition_hash()
{
    printf("\t\t\"transition_#\" : [\n");
    printf("\t\t\t{ \"read\": \"#\", \"to_state\": \"check_transition\", \"write\": \"#\", \"action\": \"RIGHT\" }\n");
    printf("\t\t],\n");
}

void check_transition()
{
    printf("\t\t\"check_transition\" : [\n");
    printf("\t\t\t{ \"read\": \"|\", \"to_state\": \"is_read\", \"write\": \"|\", \"action\": \"RIGHT\" }\n");
    printf("\t\t],\n");
}

void is_read()
{
    int i = 32;
    printf("\t\t\"check_input\" : [\n");
    while (i < 127)
    {
        if ((i >= '0' && i <= '9') 
            || i == '+' || i == '-' || i ==  '.')
            printf("\t\t\t{ \"read\": \"%c\", \"to_state\": \"is_curr_state\", \"write\": \"%c\", \"action\": \"RIGHT\" },\n", i,i);
        i++;
    }
    printf("\t\t\t{ \"read\": \"=\", \"to_state\": \"is_curr_state\", \"write\": \"=\", \"action\": \"RIGHT\" }\n");
    printf("\t\t],\n");
}

void is_curr_state(void)
{
    int i = 'a';
    printf("\t\t\"is_curr_state\" : [\n");
    while (i < 'z')
    {
        printf("\t\t\t{ \"read\": \"%c\", \"to_state\": \"is_to_state\", \"write\": \"%c\", \"action\": \"RIGHT\" },\n", i,i);
        i++;
    }
    printf("\t\t\t{ \"read\": \"z\", \"to_state\": \"is_to_state\", \"write\": \"z\", \"action\": \"RIGHT\" }\n");
    printf("\t\t],\n");
}

void is_to_state()
{
    int i = 'a';
    printf("\t\t\"is_curr_state\" : [\n");
    while (i <= 'z')
    {
        printf("\t\t\t{ \"read\": \"%c\", \"to_state\": \"is_write\", \"write\": \"%c\", \"action\": \"RIGHT\" },\n", i,i);
        i++;
    }
    printf("\t\t\t{ \"read\": \"H\", \"to_state\": \"is_write\", \"write\": \"H\", \"action\": \"RIGHT\" }\n");
    printf("\t\t],\n");
}

void is_write()
{
    int i = 32;
    printf("\t\t\"is_write\" : [\n");
    while (i < 127)
    {
        if ((i >= '0' && i <= '9') 
            || i == '+' || i == '-' || i ==  '.')
            printf("\t\t\t{ \"read\": \"%c\", \"to_state\": \"is_move\", \"write\": \"%c\", \"action\": \"RIGHT\" },\n", i,i);
        i++;
    }
    printf("\t\t\t{ \"read\": \"=\", \"to_state\": \"is_move\", \"write\": \"=\", \"action\": \"RIGHT\" }\n");
    printf("\t\t],\n");
}

void is_move()
{
    printf("\t\t\"is_move\" : [\n");
    printf("\t\t\t{ \"read\": \"R\", \"to_state\": \"memory_hash\", \"write\": \"R\", \"action\": \"RIGHT\" },\n");
    printf("\t\t\t{ \"read\": \"L\", \"to_state\": \"memory_hash\", \"write\": \"L\", \"action\": \"RIGHT\" }\n");
    printf("\t\t],\n");
}

void memory_hash()
{
    printf("\t\t\"memory_hash\" : [\n");
    printf("\t\t\t{ \"read\": \"|\", \"to_state\": \"is_read\", \"write\": \"|\", \"action\": \"RIGHT\" },\n");
    printf("\t\t\t{ \"read\": \"#\", \"to_state\": \"is_end\", \"write\": \"#\", \"action\": \"RIGHT\" }\n");
    printf("\t\t],\n");
}

void is_end()
{
    printf("\t\t\"is_end\" : [\n");
    printf("\t\t\t{ \"read\": \"_\", \"to_state\": \"go_start_tape\", \"write\": \"_\", \"action\": \"LEFT\" }\n");
    printf("\t\t],\n");
}

void go_start_tape()
{
    int i = 32;
    printf("\t\t\"go_start_tape\" : [\n");
    while (i < 127)
    {
        if ((i >= 'a' && i <= 'z') || (i >= '0' && i <= '9') 
        || i == '+' || i ==  '=' || i == '-' || i ==  '.' || i == 'R' || i ==  'L' || i ==  'H' || i ==  '#' || i ==  '|')
            printf("\t\t\t{ \"read\": \"%c\", \"to_state\": \"go_start_tape\", \"write\": \"%c\", \"action\": \"LEFT\" },\n", i, i);
        i++;
    }
    printf("\t\t\t{ \"read\": \"_\", \"to_state\": \"get_head\", \"write\": \"_\", \"action\": \"RIGHT\" }\n");
    printf("\t\t],\n");
}



void print_name_function(void)
{
    printf("\"go_back_memory\",\n");
    printf("\"go_back_transition\",\n");
    printf("\"go_back_curr_state\",\n");
    printf("\"go_back_input\",\n");
    printf("\"get_head\",\n");
    printf("\"go_end_input\",\n");
    printf("\"get_curr_state\",\n");
    printf("\"search_next_trans\",\n");
    printf("\"compare_state\",\n");
    printf("\"go_back_curr_transition\",\n");
    printf("\"skip_read\",\n");
    printf("\"erase_memory\",\n");
    printf("\"get_next_state\",\n");
    printf("\"skip_curr_state\",\n");
    printf("\"skip_bis\",\n");
    printf("\"next_state\",\n");
    printf("\"get_trans\",\n");
    printf("\"put_back_from_memory\",\n");
    printf("\"what_to_wrote\",\n");
    printf("\"start\",\n");
    printf("\"check_input\",\n");
    printf("\"check_curr_state\",\n");
    printf("\"transition_#\",\n");
    printf("\"check_transition\",\n");
    printf("\"is_read\",\n");
    printf("\"is_curr_state\",\n");
    printf("\"is_to_state\",\n");
    printf("\"is_write\",\n");
    printf("\"is_move\",\n");
    printf("\"memory_hash\",\n");
    printf("\"is_end\",\n");
    printf("\"go_start_tape\",\n");
}

int main ()
{
    int i = 32;
    print_name_function();
    while (i < 127)
    {
        if ((i >= 'a' && i <= 'z') || (i >= '0' && i <= '9') 
            || i == '+' || i ==  '=' || i == '-' || i ==  '.' || i == 'R' || i ==  'L' || i ==  'H' || i ==  '#' || i ==  '|' || i ==  '_')
        {
            save_(i, true);
            copy_(i, true);
            get_c_in_memory(i, true);
            get_c(i, true);
            write_curr_state_c(i, true);
            put_back_c(i, true);
            get_dir_c(i, true);
            apply_c(i, true);
            write_c(i, true);
        }
        i++;
    }

    printf("\n\n\n\n");

    go_back_memory();
    go_back_transition();
    go_back_curr_state();
    go_back_input();
    get_head();
    go_end_input();
    get_curr_state();
    search_next_trans();
    compare_state();
    go_back_curr_transition();
    skip_read();
    erase_memory();
    get_next_state();
    skip_curr_state();
    skip_bis();
    next_state();
    get_trans();
    put_back_from_memory();
    what_to_wrote();
    start();
    check_input();
    check_curr_state();
    transition_hash();
    check_transition();
    is_read();
    is_curr_state();
    is_to_state();
    is_write();
    is_move();
    memory_hash();
    is_end();
    go_start_tape();
    i = 32;

    while (i < 127)
    {
        if ((i >= 'a' && i <= 'z') || (i >= '0' && i <= '9') 
            || i == '+' || i ==  '=' || i == '-' || i ==  '.' || i == 'R' || i ==  'L' || i ==  'H' || i ==  '#' || i ==  '|' || i ==  '_')
        {
            save_(i, false);
            copy_(i, false);
            get_c_in_memory(i, false);
            get_c(i, false);
            write_curr_state_c(i, false);
            put_back_c(i, false);
            get_dir_c(i, false);
            apply_c(i, false);
            write_c(i, false);
        }
        i++;
    }
}