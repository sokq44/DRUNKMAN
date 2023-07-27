#include <iostream>
#include <thread>
#include <chrono>

int read_number(const char*);

int main(int argc, char **argv)
{
    if(argc == 1)
    {
        std::cout << "\n\t\t\t\tWelcome to the DRUNK MAN'S PATH SIMULATION!\n\n";
        std::cout << "This program was designed to show a simulation of as many drunkard's paths as possible. Let me explain:\n";
        std::cout << "Your job is to provide 5 parameters that whill be used to create random paths: the maximum number of steps\n"; 
        std::cout << "to be made, the maximum length of a single step, height to which the drunkard is heading, horizontal coordinate\n";
        std::cout << "of the beginning point a number representing the length of a single wallof a square which is the\n";
        std::cout << "movement board and the number of paths provided by a simulation. An example of an appropriate input would\n";
        std::cout << "look like this: 'drunk_man 10 10 50 25 15', all the numbers must be from 1 to 99 and make sense (for example\n"; 
        std::cout << "you can't give any height value which is more than the longest combination possible to achieve with other\n"; 
        std::cout << "given parameters). Please note that this is a program designed for CLI and enjoy using.\n\n\n";
        
        for (int i = 99; i != 0; i--) 
        {
            std::cout << "Time left: " << i << " s.\r";
            std::cout.flush();
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
    else if(argc != 6 || ( (read_number(argv[2]) * read_number(argv[1])) ) < read_number(argv[3]))
    {
        std::cout << "Wrong input (arithmetically or logically).";
    }
    else
    {
        system("g++ source_files/main.cpp -o temp.exe");

        std::string execution;

        for(int i = 0; i < read_number(argv[5]); i++)
        {
            execution = "temp.exe " + std::to_string( read_number(argv[1]) ) + " " + std::to_string( read_number(argv[2]) ) + " " + std::to_string( read_number(argv[3]) ) + " " + std::to_string( read_number(argv[4]) );
            system(execution.c_str());
        }

        system("del temp.exe");
    }
}

int read_number(const char *txt)
{
    std::string num = txt;
    std::string cli_num = "cli_num.exe " + num;
    
    return system(cli_num.c_str());
}