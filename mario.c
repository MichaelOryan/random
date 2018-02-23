// Make a mario pyramid from CS50
// Expanded to now include setting individual heights for each side of the pyramid

#include <stdio.h>
#include <stdbool.h>

#define MINIMUM_PYRAMID_HEIGHT 0
#define MAXIMUM_PYRAMID_HEIGHT 23
#define PYRAMID_GAP_SIZE 2
#define BRICK_BLOCK '#'
#define AIR_BLOCK ' '
#define PYRAMID_STARTING_LEVEL 1
#define NEWLINE_CHARACTER '\n'

int get_int(char * prompt);
bool is_invalid_height(int pyramid_height);
void print_character(char c);
int calc_level_above(int current_level);
int get_pyramid_height();
int calc_air_blocks(int pyramid_height, int pyramid_side_size);
void repeat_print(char c, int amount);
void print_air_blocks(int pyramid_height, int pyramid_side_size);
void print_left_air(int pyramid_height, int pyramid_side_size);
void print_right_air(int pyramid_height, int pyramid_side_size);
void print_pyramid_side(int pyramid_side_size);
void print_left_pyramid_side(int pyramid_side_size);
void print_right_pyramid_side(int pyramid_side_size);
void print_gap(int gap_size);
int calc_pyramid_side_size(int pyramid_height, int current_level, int offset);
void print_new_line();
void print_level_above(int pyramid_height, int current_level, int left_height, int right_height);
void print_level(int pyramid_height, int current_level, int left_height, int right_height);
void print_pyramid(int left_height, int right_height);
int calc_pyramid_left_size(int pyramid_height, int current_level, int left_height);
int calc_pyramid_right_size(int pyramid_height, int current_level, int right_height);
int get_left_height();
int get_right_height();
int get_height(char * prompt);


int main(void)
{
    int left_height = get_left_height();
    int right_height = get_right_height();
    print_pyramid(left_height, right_height);
}

int get_int(char * prompt)
{
    printf("%s", prompt);
    int n;
    scanf("%d", &n);
    return n;
}

bool is_invalid_height(int pyramid_height)
{
    return  pyramid_height >= MINIMUM_PYRAMID_HEIGHT &&
            pyramid_height <= MAXIMUM_PYRAMID_HEIGHT;
}

void print_character(char c)
{
    printf("%c", c);
}

int calc_level_above(int current_level)
{
    return current_level + 1;
}

int get_height(char * prompt)
{
    int height;
    
    do
    {
        height = get_int(prompt);
    }
    while ( !is_invalid_height(height) );
    
    return height;
    
}

int get_pyramid_height()
{
    return get_height("Pyramid Height?: ");
}

int get_left_height()
{
    return get_height("Pyramid Left Side Height?: ");
}

int get_right_height()
{
    return get_height("Pyramid Right Side Height?: ");
}


int calc_air_blocks(int pyramid_height, int pyramid_side_size)
{
    return pyramid_height - pyramid_side_size;
}

void repeat_print(char c, int amount)
{
    for(int count = 0; count < amount; count++)
    {
        print_character(c);
    }
}

void print_air_blocks(int pyramid_height, int pyramid_side_size)
{
    int number_of_air_blocks = calc_air_blocks(pyramid_height, pyramid_side_size);
    
    repeat_print(AIR_BLOCK, number_of_air_blocks);

}

void print_left_air(int pyramid_height, int pyramid_side_size)
{
    print_air_blocks(pyramid_height, pyramid_side_size);
}

void print_right_air(int pyramid_height, int pyramid_side_size)
{
    print_air_blocks(pyramid_height, pyramid_side_size);
}

void print_pyramid_side(int pyramid_side_size)
{
    repeat_print(BRICK_BLOCK, pyramid_side_size);
}

void print_left_pyramid_side(int pyramid_side_size)
{
    print_pyramid_side(pyramid_side_size);
}

void print_right_pyramid_side(int pyramid_side_size)
{
    print_pyramid_side(pyramid_side_size);
}

void print_gap(int gap_size)
{
    repeat_print(AIR_BLOCK, gap_size);
}

int calc_pyramid_side_size(int pyramid_height, int current_level, int offset)
{
    // height of one, current level of one, size of pyramid side one.
    // Need better logic to show why this is as it is or change it to something
    // that makes more sense
    int side_size = pyramid_height - current_level + 1 + offset;
    if(side_size < 0)
    {
        side_size = 0;
    }
    else if (side_size > pyramid_height)
    {
        side_size = pyramid_height;
    }
    return side_size;
}

void print_new_line()
{
    print_character(NEWLINE_CHARACTER);
}

void print_level_above(int pyramid_height, int current_level, int left_height, int right_height)
{
    
    if(current_level < pyramid_height)
    {
        int level_above = calc_level_above(current_level);
        print_level(pyramid_height, level_above, left_height, right_height);
    }
}

void print_level(int pyramid_height, int current_level, int left_height, int right_height)
{
    print_level_above(pyramid_height, current_level, left_height, right_height);
    int left_side_size = calc_pyramid_left_size(pyramid_height, current_level, left_height);
    int right_side_size = calc_pyramid_right_size(pyramid_height, current_level, right_height);
    
    print_left_air(pyramid_height, left_side_size);
    print_left_pyramid_side(left_side_size);
    
    print_gap(PYRAMID_GAP_SIZE);
    
    print_right_pyramid_side(right_side_size);
    print_right_air(pyramid_height, right_side_size);
    
    print_new_line();
}

int max(int a, int b)
{
    int maximum = a;
    
    if(b > a)
    {
        maximum = b;
    }
    
    return maximum;
}

void print_pyramid(int left_height, int right_height)
{
    int current_level = PYRAMID_STARTING_LEVEL;
    int pyramid_height = max(left_height, right_height);
    print_level(pyramid_height, current_level, left_height, right_height);
}


int calc_pyramid_left_size(int pyramid_height, int current_level, int left_height)
{
    int offset = left_height - pyramid_height;
    return calc_pyramid_side_size(pyramid_height, current_level, offset);
}

int calc_pyramid_right_size(int pyramid_height, int current_level, int right_height)
{
    int offset = right_height - pyramid_height;
    return calc_pyramid_side_size(pyramid_height, current_level, offset);
}

