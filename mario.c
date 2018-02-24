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

struct Pyramid;

int calc_pyramid_height(int left_height, int right_height);
int calc_pyramid_width(struct Pyramid pyramid);
struct Pyramid construct_pyramid_specs(int left_height, int right_height);
int get_int(char * prompt);
bool is_invalid_height(int pyramid_height);
void print_character(char c);
int calc_level_above(int current_level);
int get_pyramid_height();
int calc_air_blocks(int pyramid_height, int pyramid_side_size);
void repeat_print(char c, int amount);
void print_air_blocks(int pyramid_height, int pyramid_side_size);
void print_left_air(struct Pyramid *pyramid, int pyramid_side_size);
void print_right_air(struct Pyramid *pyramid, int pyramid_side_size);
void print_pyramid_side(int pyramid_side_size);
void print_left_pyramid_side(int pyramid_side_size);
void print_right_pyramid_side(int pyramid_side_size);
void print_gap(int gap_size);
int calc_pyramid_side_size(int pyramid_height, int current_level, int offset);
void print_new_line();
void print_level_above(struct Pyramid *pyramid, int current_level);
void print_level(struct Pyramid *pyramid, int current_level);
void print_pyramid(struct Pyramid pyramid);
int calc_pyramid_left_size(struct Pyramid *pyramid, int current_level);
int calc_pyramid_right_size(struct Pyramid *pyramid, int current_level);
int get_left_height();
int get_right_height();
int get_height(char * prompt);
int max(int a, int b);

struct Pyramid {
    int height;
    int width;
    int gap;
    int left_height;
    int right_height;
};

int calc_pyramid_height(int left_height, int right_height)
{
    return max(left_height, right_height);
}

int calc_pyramid_width(struct Pyramid pyramid)
{
    return pyramid.left_height + pyramid.gap + pyramid.right_height;
}

struct Pyramid construct_pyramid_specs(int left_height, int right_height)
{
    struct Pyramid pyramid;
    pyramid.left_height = left_height;
    pyramid.right_height = right_height;
    pyramid.height = calc_pyramid_height(left_height, right_height);
    pyramid.gap = PYRAMID_GAP_SIZE;
    pyramid.width = calc_pyramid_width(pyramid);
    return pyramid;
}

int main(void)
{
    
    int left_height = get_left_height();
    int right_height = get_right_height();
    struct Pyramid pyramid = construct_pyramid_specs(left_height, right_height);
    print_pyramid(pyramid);
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

void print_air_blocks(int pyramid_height, int side_size)
{
    int number_of_air_blocks = calc_air_blocks(pyramid_height, side_size);
    
    repeat_print(AIR_BLOCK, number_of_air_blocks);

}

void print_left_air(struct Pyramid *pyramid, int pyramid_side_size)
{
    print_air_blocks(pyramid->left_height, pyramid_side_size);
}

void print_right_air(struct Pyramid *pyramid, int pyramid_side_size)
{
    print_air_blocks(pyramid->right_height, pyramid_side_size);
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
    int side_size = PYRAMID_STARTING_LEVEL; // Need clearer logic
    side_size += pyramid_height - current_level + offset;
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

void print_level_above(struct Pyramid *pyramid, int current_level)
{
    
    if(current_level < pyramid->height)
    {
        int level_above = calc_level_above(current_level);
        print_level(pyramid, level_above);
    }
}

void print_level(struct Pyramid *pyramid, int current_level)
{
    print_level_above(pyramid, current_level);
    int left_side_size = calc_pyramid_left_size(pyramid, current_level);
    int right_side_size = calc_pyramid_right_size(pyramid, current_level);
    
    print_left_air(pyramid, left_side_size);
    print_left_pyramid_side(left_side_size);
    
    print_gap(PYRAMID_GAP_SIZE);
    
    print_right_pyramid_side(right_side_size);
    print_right_air(pyramid, right_side_size);
    
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

void print_pyramid(struct Pyramid pyramid)
{
    int current_level = PYRAMID_STARTING_LEVEL;
    print_level(&pyramid, current_level);
}


int calc_pyramid_left_size(struct Pyramid *pyramid, int current_level)
{
    int offset = pyramid->left_height - pyramid->height;
    return calc_pyramid_side_size(pyramid->height, current_level, offset);
}

int calc_pyramid_right_size(struct Pyramid *pyramid, int current_level)
{
    int offset = pyramid->right_height - pyramid->height;
    return calc_pyramid_side_size(pyramid->height, current_level, offset);
}
