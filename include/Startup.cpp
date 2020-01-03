/* Maths challenge quiz
   Copyright Ethan Marshall - 2019

   Licensed under the GPL V.3.0
*/

#include <vector>
#include <string>
#include <iostream>

#include "Startup.h"
#include "Util.h"
#include "Constants.h"

namespace startup
{

const int tut_max = 12;
const int tut_min = 1;

std::vector<std::string> *parseCmdLine(char *argv[], int count)
{

    std::vector<std::string> *vector = new std::vector<std::string>();

    for (int i = 1; i < count; i++)
    {
    }

    return vector;
}

void handleCmdLine(std::vector<std::string> *cmds)
{

    // Free the allocated startup options
    delete cmds;
}

bool warnImpossibleDifficulty()
{
    std::cout << "\nWARNING: Impossible difficulty selected\n";
    std::cout << "You have selected impossible difficulty, which removes the limit for how high question amounts can be\n";
    std::cout << "You may encounter impossible to calculate values, extremely long questions or numbers larger than the program can handle\n";
    std::cout << "You proceed at your own risk\n\n";

    std::string choice;
    std::cout << "Do you wish to continue? [Y/N]";
    std::getline(std::cin, choice);

    util::stringLower(&choice);

    if (choice == "y")
    {
        std::cout << "Good luck, padawan\n\n";
        return true;
    }
    else
    {
        std::cout << "\n\n";
        return false;
    }
}

bool warnTrainingDifficulty()
{
    std::cout << "\nWARNING: Training difficulty selected\n";
    std::cout << "You have selected training difficulty, meaning that all questions will only contain the number 1\n";
    std::cout << "This mode is designed to be a trial run of the game and will not give a true reflection of your mathamatical ability.\n";
    std::cout << "Your score in this mode is considered non-genuine and certain features of the game may be altered to reflect that.\n\n";

    std::string choice;
    std::cout << "Do you wish to continue? [Y/N]";
    std::getline(std::cin, choice);

    util::stringLower(&choice);

    if (choice == "y")
    {
        std::cout << "Training mode has been applied for this round, and your score is not genuine from this point forward\n\n";
        return true;
    }
    else
    {
        std::cout << "\n\n";
        return false;
    }
}

void handleDifficultyEnter(startup_information *info)
{
    bool success = false;

    while (!success)
    {
        std::string difficulty;
        std::cout << "Enter your difficulty, 1-4 (1=Easy, 4=Very hard)\n";
        std::cout << "Enter difficulty:";
        std::getline(std::cin, difficulty);

        if (difficulty.empty())
        {
            std::cout << "Please enter a valid difficulty\n\n";
            continue;
        }

        try
        {
            info->difficulty = std::stoi(difficulty);
        }
        catch (const std::invalid_argument &e)
        {
            std::cout << "Please enter a valid difficulty\n\n";
            continue;
        }

        if (info->difficulty <= TRAINING_DIFFICULTY_THRESHOLD)
        {
            success = warnTrainingDifficulty();
            continue;
        }
        else if (info->difficulty >= IMPOSSIBLE_DIFFICULTY_THRESHOLD)
        {
            success = warnImpossibleDifficulty();
            continue;
        }

        success = true;
        std::cout << "Your difficulty has been set to " << info->difficulty << "\n\n";
    }
}

void runTutorial()
{
    std::cout << std::endl;
    std::cout << "Welcome to the Maths Challenge Quiz!\n";
    std::cout << "In this game you stay ahead of the game by answering maths problems correctly\n";
    std::cout << "You can select any difficulty to cater to your mathematical ability\n";
    std::cout << "\n";
    std::cout << "Let's try out a simple tutorial\n";
    std::cout << "\n";

    int randint1 = std::rand() % (tut_max - tut_min) + tut_min;
    int randint2 = std::rand() % (tut_max - tut_min) + tut_min;

    std::string randstr1 = std::to_string(randint1);
    std::string randstr2 = std::to_string(randint2);

    std::string input;
    int answer;
    int correct_answer = randint1 * randint2;

    while (true)
    {
        std::cout << "Please enter the answer to " + randstr1 + "x" + randstr2 + ":";
        std::getline(std::cin, input);

        if (!util::isValidNumber(input))
        {
            std::cout << "Please enter a valid answer\n";
            continue;
        }

        answer = std::stoi(input);

        if (answer == correct_answer)
        {
            std::cout << "Correct, you've got the idea\n";
            std::cout << "You will now play the real game which will get you a score\n";
            std::cout << "Good luck\n";
            std::cout.flush();
            util::sleep(2);
            std::cout.clear();
            break;
        }
        else
        {
            std::cout << "Incorrect, please try again\n\n";
        }
    }
}

bool askFirstTime()
{
    std::string input;
    bool first = false;

    std::cout << "Is this your first time playing? [Y/N]";
    std::getline(std::cin, input);

    util::stringLower(&input);

    if (input == "y")
    {
        runTutorial();
        first = true;
    }

    return first;
}

void handleStartQuestions(startup_information *info)
{
    std::cout << "Please enter your name:";
    std::getline(std::cin, info->name);
    std::cout << "\n";

    handleDifficultyEnter(info);

    bool isFirst = askFirstTime();
    info->first = isFirst;
}

void haltPreGame()
{
    std::cout << "\nGame commencing in 5 seconds...\n";
    std::cout.flush();
    util::sleep(5);
    util::clearScreen();
}

void printWelcome()
{
    std::cout << "Welcome to the Maths Challenge Quiz\n";
    std::cout << "Copyright 2019 Ethan Marshall\n\n";
}

void printCopyright()
{
    std::cout << "Maths Challenge Quiz is a copyrighted work by Ethan Marshall\n";
    std::cout << "The program is licensed under the terms of the GPL V.3.0, meaning you have certain freedoms\n";
    std::cout << "For more information, visit https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html \n\n";
}

void printHelp()
{
    std::cout << "Maths Challenge Quiz - Help Menu\n\n";
    std::cout << "The Maths Challenge Quiz is a program designed to test a person's mathematical ability in a fun way\n";
    std::cout << "This game can be quite complicated, so help can be found in the 'readme.md' file included in the install\n\n";
}

} // namespace startup