#include <unistd.h>
#include <stdio.h>


void print_line_erase(char c)
{
    int i = 32;

    printf("\"erase_%c\": [\n", c);

        // if (i != '.' && (( i >= 'A' &&  i <= 'Z') || ( i >= '0' &&  i <= '9') || ( i >= '0' &&  i <= '9')) )

    while (i < 127)
    {
        if (( i >= 'A' &&  i <= 'Z') || ( i >= '0' &&  i <= '9') || ( i >= 'a' &&  i <= 'z'))
        {
            if (c == i)
                printf("{ \"read\": \"%c\",  \"to_state\": \"go_left\", \"write\": \".\", \"action\": \"LEFT\" },\n", i);
            else
                printf("{ \"read\": \"%c\",  \"to_state\": \"write_n\", \"write\": \"%c\", \"action\": \"RIGHT\" },\n", i, i);
        }
        i++;
    }
    if (c == 'z')
        printf("{ \"read\": \".\",  \"to_state\": \"write_y\", \"write\": \".\", \"action\": \"RIGHT\" }\n]\n");
    else
        printf("{ \"read\": \".\",  \"to_state\": \"write_y\", \"write\": \".\", \"action\": \"RIGHT\" }\n],\n");
}


void print_line_go_right(char c)
{
    int i = 32;

    printf("\"go_right_%c\": [\n", c);
    while (i < 127)
    {
        if (i != '.' && (( i >= 'A' &&  i <= 'Z') || ( i >= '0' &&  i <= '9') || ( i >= 'a' &&  i <= 'z')))
        {
            printf("{ \"read\": \"%c\",  \"to_state\": \"go_right_%c\", \"write\": \"%c\", \"action\": \"RIGHT\" },\n", i, c, i);
        }

        i++;
    }
    printf("{ \"read\": \".\",  \"to_state\": \"erase_%c\", \"write\": \".\", \"action\": \"LEFT\" }\n],\n", c);
}

void write_n (void)
{
    int c = 32;
    printf("\"write_n\" : [\n");
    while (c < 127)
    {
        if (( c >= 'A' &&  c <= 'Z') || ( c >= '0' &&  c <= '9') || ( c >= 'a' &&  c <= 'z'))
        {
            printf("{ \"read\": \"%c\", \"to_state\": \"write_n\", \"write\": \"%c\", \"action\": \"RIGHT\" },\n", c,c);
        }
        c++;
    }
    printf("{ \"read\": \".\", \"to_state\": \"HALT\", \"write\": \"n\", \"action\": \"RIGHT\" }\n");
    printf("],\n");
}

void write_y (void)
{
    int c = 32;
    printf("\"write_y\" : [\n");
    while (c < 127)
    {
        if (( c >= 'A' &&  c <= 'Z') || ( c >= '0' &&  c <= '9') || ( c >= 'a' &&  c <= 'z'))
        {
            printf("{ \"read\": \"%c\", \"to_state\": \"write_n\", \"write\": \"%c\", \"action\": \"RIGHT\" },\n", c,c);
        }
        c++;
    }
    printf("{ \"read\": \".\", \"to_state\": \"HALT\", \"write\": \"y\", \"action\": \"RIGHT\" }\n");
    printf("],\n");
}

void find_letter (void)
{
    int c = 32;
    printf("\"find_letter\" : [\n");
    while (c < 127)
    {
        if (( c >= 'A' &&  c <= 'Z') || ( c >= '0' &&  c <= '9') || ( c >= 'a' &&  c <= 'z'))
        {
            printf("{ \"read\": \"%c\", \"to_state\": \"go_right_%c\", \"write\": \".\", \"action\": \"RIGHT\" },\n", c,c);
        }
        c++;
    }
    printf("{ \"read\": \".\", \"to_state\": \"write_y\", \"write\": \".\", \"action\": \"RIGHT\" }\n");
    printf("],\n");
}

void go_left (void)
{
    int c = 32;
    printf("\"go_left\" : [\n");
    while (c < 127)
    {
        if (( c >= 'A' &&  c <= 'Z') || ( c >= '0' &&  c <= '9') || ( c >= 'a' &&  c <= 'z'))
        {
            printf("{ \"read\": \"%c\", \"to_state\": \"go_left\", \"write\": \"%c\", \"action\": \"LEFT\" },\n", c,c);
        }
        c++;
    }
    printf("{ \"read\": \".\", \"to_state\": \"find_letter\", \"write\": \".\", \"action\": \"RIGHT\" }\n");
    printf("],\n");
}
void go_und_input (char c)
{

    printf ("{ \"read\": \"%c\", \"to_state\": \"trans\", \"write\": \"%c\", \"action\": \"RIGHT\" },\n", c, c);
    // { "read": "1", "to_state": "trans", "write": "1", "action": "RIGHT" },

}

// int main (void)
// {
//     int i = 32;
//     // write_n();
//     // write_y();
//     // find_letter();
//     // go_left();
//     while (i < 127)
//     {
//         // if (( i >= 'A' &&  i <= 'Z') || ( i >= 'a' &&  i <= 'z') || ( i >= '0' &&  i <= '9') || i == '#' || i == '.' || i == '=' || i == '+')
//         // if (( i >= 'a' &&  i <= 'z') || i == '1' || i == '#' || i == '.' || i == '=' || i == '+' || i == '|' || i == '_' || i == 'H' || i == 'S' || i == 'L' || i == 'R')
//         if (( i >= 'a' &&  i <= 'z'))
//         {
//             // printf("\"go_right_%c\", \"erase_%c\",\n", i, i);
//             // print_line_go_right(i);
//             go_und_input(i);
//             // print_line_erase(i);
//             // printf("\"%c\", ", i);
//         }
//     //     // printf("\"go_right_\\%c\", \"erase_\\%c\",\n", i, i);
//         i++;
//     }
// }

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

void save_(char input)
{
    if (input == '#' || input == '|' || input == '_')
        return;
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

void copy_(char input)
{
    if (input == '#' || input == '|' || (input >= 'a' && input <= 'z') || input == '_')
        return;
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

void search_next_state(void)
{
    int i = 32;
    printf("\t\t\"search_next_state\" : [\n");
    while (i < 127)
    {
        if ((i >= 'a' && i <= 'z') || (i >= '0' && i <= '9') 
        || i == '+' || i ==  '=' || i == '-' || i ==  '.' || i == 'R' || i ==  'L' || i ==  'H')
            printf("\t\t\t{ \"read\": \"%c\", \"to_state\": \"search_next_state\", \"write\": \"%c\", \"action\": \"RIGHT\" },\n", i, i);
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

void get_c_in_memory (char c)
{
    if (c == '#' || c == '|' || c == '_')
        return;
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

void get_c_state(char c, char i)
{
    if (c == i)
        printf("\t\t\t{ \"read\": \"%c\", \"to_state\": \"erase_memory\", \"write\": \"_\", \"action\": \"LEFT\" },\n", c);
    else
        printf("\t\t\t{ \"read\": \"%c\", \"to_state\": \"get_%c\", \"write\": \"%c\", \"action\": \"RIGHT\" },\n", i, c, i);
}

void get_c_input(char c, char i)
{
    if (c == i)
        printf("\t\t\t{ \"read\": \"%c\", \"to_state\": \"go_back_curr_transition\", \"write\": \"%c\", \"action\": \"LEFT\" },\n", i, c);
    else
        printf("\t\t\t{ \"read\": \"%c\", \"to_state\": \"get_%c\", \"write\": \"%c\", \"action\": \"RIGHT\" },\n", i, c, i);

}

void get_c(char c)
{
    if (c == '#' || c == '|' || c == '_' || c == 'R' || c == 'L' || c == 'H')
        return;
    int i = 32;
    printf("\t\t\"get_%c\" : [\n", c);
    while (i < 127)
    {
        if ((i >= 'a' && i <= 'z'))
            get_c_state(c, i);
        else if ((i >= '0' && i <= '9') 
            || i == '+' || i ==  '=' || i == '-' || i ==  '.')
            get_c_input(c, i);
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
            printf("\t\t\t{ \"read\": \"%c\", \"to_state\": \"go_back_curr_transition\", \"write\": \"%c\", \"action\": \"LEFT\" }\n", i ,i);
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

int main ()
{
    int i = 32;
    go_back_memory();
    go_back_transition();
    go_back_curr_state();
    go_back_input();
    get_head();
    go_end_input();
    get_curr_state();
    search_next_state();
    compare_state();
    go_back_curr_transition();
    skip_read();
    erase_memory();
    get_next_state();
    skip_curr_state();
    skip_bis();
    next_state();
    while (i < 127)
    {
        if ((i >= 'a' && i <= 'z') || (i >= '0' && i <= '9') 
            || i == '+' || i ==  '=' || i == '-' || i ==  '.' || i == 'R' || i ==  'L' || i ==  'H' || i ==  '#' || i ==  '|' || i ==  '_')
        {
            save_(i);
            copy_(i);
            get_c_in_memory(i);
            get_c(i);
        }
        i++;
    }
}