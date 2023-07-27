#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdio>
#include <fstream>
#include "drunkard.h"
#include <string>

/* ---------------------------------------- Method Declaration part for the 'Step' class. ---------------------------------------- */
Step::Step(Point p)
{
    this->beg.x = p.x;
    this->beg.y = p.y;
    
    this->end.x = rand() % 100;
    this->end.y = rand() % 100 + p.y;
}

double Step::step_length()
{
    return( sqrt( pow( (this->end.x - this->beg.x), 2 ) + pow( (this->end.y - this->beg.y), 2 ) ) );
}

std::string Step::info_output()
{
    std::string output;

    output = "\t{\n\t\t\"beg_x\": " + std::to_string(this->beg.x) + ",\n\t\t\"beg_y\": " + std::to_string(this->beg.y) + ",\n\t\t\"end_x\": " + std::to_string(this->end.x) + ",\n\t\t\"end_y\": " + std::to_string(this->end.y) + ",\n\t\t\"length\": " + std::to_string(this->step_length()) + "\n\t},\n";

    return output;
}

Point Step::last_point_coords()
{
    Point spot;
    spot.x = this->end.x;
    spot.y = this->end.y;

    return spot;
}
/* --------------------------------------------------------------------------------------------------------------------------------- */

/* ---------------------------------------- Method Declaration part for the 'Path' class. ---------------------------------------- */
Path::Path(unsigned short max_step_num, double max_step_length, unsigned short height, Board board)
{
    this->max_step_num = max_step_num;
    this->height = height;
    this->max_step_length = max_step_length;
    this->board = board;
}

Path::~Path()
{
    this->terminate_all(this->steps);
}

Stack *Path::last_element(Stack *stack)
{
    if(stack)
        while(stack->last)
            stack = stack->last;
    
    return stack;
}

void Path::add(Stack *& stack, Step *move)
{
    Stack *tmp = new Stack;
    tmp->ins = move;
    tmp->last = nullptr;

    if(stack)
        last_element(stack)->last = tmp;
    else
        stack = tmp;
}

void Path::delete_last(Stack *& stack)
{
    if(!stack)
        return;

    Stack *last = last_element(stack);

    if(last == stack)
    {
        delete(stack);
        stack = nullptr;
    } 
    else
    {
        Stack *penultimate = stack;
        while(penultimate->last != last)
            penultimate = penultimate->last;

        penultimate->last = nullptr;
        delete(last);
    }

    return;
}


void Path::terminate_all(Stack *&stack)
{
    while(stack)
    {
        Stack *tmp = stack;
        stack = stack->last;

        delete(tmp);
    }

    stack = nullptr;
}

double Path::average_step_len()
{
    return( this->en_length / (double)(this->steps_num) );
}

bool Path::is_within_board(Step *move)
{
    if(move->last_point_coords().x > this->board.bottom_right.x || move->last_point_coords().x < this->board.bottom_left.x)
        return false;
    
    return true;
}

void Path::create_path(Point beg_point)
{
    Step* move;
    int i = 0;

    this->steps = nullptr;
    Point end = beg_point;

    srand(time(nullptr));

    while(true)
    {
        for (i; i < this->max_step_num; i++)
        {
            move = new Step(end);

            if (move->step_length() > this->max_step_length || (move->last_point_coords().x == end.x && move->last_point_coords().y == end.y) || !this->is_within_board(move))
            {
                --i;

                delete move;
                continue;
            }
            else if (move->last_point_coords().y >= this->height)
            {
                this->add(this->steps, move);
                this->en_length += move->step_length();
                break;
            }
            else
            {
                this->add(this->steps, move);
                end = move->last_point_coords();
                this->en_length += move->step_length();
            }
            ++this->steps_num;
        }

        if(move->last_point_coords().y < this->height)
        {
            this->steps_num = 0;
            i = 0;
            end = beg_point;

            this->terminate_all(this->steps);
        }else 
            break;
    }
}

std::string Path::info_output()
{
    Stack *tmp = this->steps;
    std::string path;
    
    while (tmp)
    {
        path += tmp->ins->info_output();
        tmp = tmp->last;
    }

    return path;
}

void Path::path_to_json()
{
    std::ofstream file("source_files/path.json");

    if(file.good())
    {
        file << "{\n\t\"steps\": [\n";
        file << this->info_output() << "\t{}\n";
        file << "\t],\n";
        file << "\t\"en_length\": " << this->en_length << ",\n\t\"average_step_len\": " << this->average_step_len() << ",\n";
        file << "\t\"board\": [\n";
        file << "\t\t{ \"bottom_left_x\": " << this->board.bottom_left.x << ", \"bottom_left_y\": " << this->board.bottom_left.y << "},\n";
        file << "\t\t{ \"bottom_right_x\": " << this->board.bottom_right.x << ", \"bottom_right_y\": " << this->board.bottom_right.y << "},\n";
        file << "\t\t{ \"top_right_x\": " << this->board.top_left.x << ", \"top_right_y\": " << this->board.top_left.y << "},\n";
        file << "\t\t{ \"top_left_x\": " << this->board.top_right.x << ", \"top_left_y\": " << this->board.top_right.y << "}\n";
        file <<"\t]\n}";
        
    }

    file.close();
}

/* --------------------------------------------------------------------------------------------------------------------------------- */

int read_number(const char*);

int main(int argc, char **argv)
{
    Board board;
    Point beg_point = {read_number(argv[4]), 0};

    board.bottom_left.x = 0;
    board.bottom_left.y = 0;
    board.bottom_right.x = read_number(argv[3]);
    board.bottom_right.y = 0;
    board.top_left.x = 0;
    board.top_left.y = read_number(argv[3]);
    board.top_right.x = read_number(argv[3]);
    board.top_right.y = read_number(argv[3]);

    int max_step_num = read_number(argv[1]);
    int max_step_length = read_number(argv[2]);
    int height = board.top_left.y;

    Path *test = new Path(max_step_num, max_step_length, height, board);
    test->create_path(beg_point);
    test->path_to_json();

    system("python source_files/draw_path.py");

    delete(test); 
    test = NULL;
}

int read_number(const char* txt)
{
    std::string num = txt;
    std::string cli_num = "cli_num.exe " + num;
    
    return system(cli_num.c_str());
}