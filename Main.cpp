/* Maths challenge quiz
   Copyright Ethan Marshall - 2019

   Licensed under the GPL V.3.0
*/

#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
#include <vector>

#include "include/Constants.h"
#include "include/Startup.h"
#include "include/Util.h"
#include "include/Scoring.h"
#include "include/GameOver.h"

#include "include/round/Round.h"
#include "include/round/BaseRound.h"
#include "include/round/RoundUtils.h"

using namespace gameround;
using namespace game_over;
using namespace std;

static PreviousRound prevRound = {
    RoundType::arithmetic,
    false,
};

static scoring::GameStatus game_state;

int main(int argc, char *argv[])
{
    // Setup random behaviour seed based on system time
    util::setupRandomSeed();

    vector<string> *parsedArgs = startup::parseCmdLine(argv, argc);
    startup::handleCmdLine(parsedArgs);

    startup::printWelcome();

    startup::startup_information info;
    startup::handleStartQuestions(&info);

    startup::haltPreGame();

    // Main game loop
    while (true)
    {

        // Construct round
        int roundType = std::rand() % MAX_ROUND_TYPES;
        BaseRound *currentRound = gameround::constructRound(roundType, &prevRound);

        // ==================== [START OF ROUND] ====================

        while (!currentRound->isRoundOver())
        {

            float ans = currentRound->askQuestion();
            currentRound->handleAnswer(ans);
        }

        // ==================== [END OF ROUND] ====================

        // Fill in the previous round's information
        currentRound->getRoundInfo(&prevRound);
        currentRound->updateGameState(&game_state);

        if (!currentRound->shouldPassRound())
        {
            scoring::run_roundFailureCutscene();
            scoring::displayResults(game_state, info.difficulty);
            scoring::resultAcceptance(info.difficulty);
            break;
        }

        currentRound->runInterlude();

        // Free the current round
        delete currentRound;
        std::memset(currentRound, 0, sizeof(currentRound->getSize()));
    }

    // When we reach this point, the game is over
    gameExiting();

    return 0;
}