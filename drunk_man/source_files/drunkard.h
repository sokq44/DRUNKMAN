#include <iostream>

#ifndef drunkard_h
#define drunkard_h

struct Point
{
    int x;   /* Horizontal coordinate of a point. */
    int y;   /* Vertical coordinate of a point. */
};

struct Board
{
    Point top_left;         /* Top left point of a right-angled quadrilateral. */
    Point bottom_left;      /* Bottom left point of a right-angled quadrilateral. */
    Point top_right;        /* Top right point of a right-angled quadrilateral. */
    Point bottom_right;     /* Bottom right point of a right-angled quadrilateral. */
};

class Step
{
    private:
        Point beg;  /* Coordinates of the beggining of a step. */
        Point end;  /* Coordinates of the end of a step. */

    public:
        Step(Point);                /* Step classes Constructor */
        double step_length();       /* A method returning the length of the step. */
        std::string info_output();  /* A method for the coding proces showing information about a step. */
        Point last_point_coords();  /* A method returning a point which has a copied coordinates of the 'end' attribute coordinates. */
        Point beg_point_coords();   /* A method returning a point which has a copied coordinates of the 'beg' attribute coordinates. */
};

struct Stack
{
    Step *ins;
    Stack *last;
};

class Path
{
    private:
        /* ------------- Methods for the Stack structure -------------*/
        Stack *last_element(Stack*);
        void add(Stack*&, Step*);
        void delete_last(Stack*&);
        void terminate_all(Stack*&);
        /* -----------------------------------------------------------*/

    private:
        Stack *steps;                   /* A stack of Steps in a Path. */
        double max_step_length;         /* The maximum value of a step's length. */ 
        unsigned short max_step_num;    /* The maximum number of steps taken within a path. */
        double en_length;               /* An attribute that stores the entire length of all steps ('en_legth' - abbreviation for 'entire length'). */
        unsigned short steps_num;       /* The number of steps in a Path. */
        unsigned short height;          /* The coordinates which the end of the Path should reach. */
        Board board;                    /* The board with which the path is being created. */


    public:
        Path();                                                 /* Path classes Constructor. */
        Path(unsigned short, double, unsigned short, Board);    /* Path classes Constructor. */
        ~Path();                                                /* Path classes Destructor. */
        void create_path(Point);                                /* A method creating a Path. */
        double average_step_len();                              /* A method calculating the average length of a step in a path. */
        std::string info_output();                              /* A method that prints information about all the steps taken. */
        bool is_within_board(Step*);                            /* A method respondible for deciding whether the step is placed within board or not. */
        void path_to_json();
};

#endif