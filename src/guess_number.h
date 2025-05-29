#ifndef GUESS_NUMBER_H
#define GUESS_NUMBER_H

#include <string>
#include <vector>
#include <array>
#include <memory>
#include "code_generator.h"

class GuessNumberGame {
public:
    // Default constructor uses RandomCodeGenerator
    GuessNumberGame();
    
    // Constructor with code generator dependency injection
    explicit GuessNumberGame(std::unique_ptr<CodeGenerator> generator);
    
    // Start a new game with code from the generator
    void startNewGame();
    
    // Process a guess and return the result as "xAyB"
    std::string processGuess(const std::array<int, 4>& guess);
    
    // Check if the input is valid (4 distinct digits from 0-9)
    bool isValidInput(const std::array<int, 4>& guess) const;
    
    // Return true if the player has won
    bool hasWon() const;
    
    // Return true if the player has used all attempts
    bool hasLost() const;
    
    // Get the remaining attempts
    int getRemainingAttempts() const;
    
    // Get history of guesses and results
    const std::vector<std::pair<std::array<int, 4>, std::string>>& getHistory() const;
    
    // Get the secret code (for testing or when game is over)
    const std::array<int, 4>& getSecretCode() const;

private:
    std::unique_ptr<CodeGenerator> codeGenerator;
    std::array<int, 4> secretCode;
    int remainingAttempts;
    bool gameWon;
    std::vector<std::pair<std::array<int, 4>, std::string>> history;
    
    static const int MAX_ATTEMPTS = 6;
};

// Function to run the interactive game
void playGuessNumberGame();

// Main function for the game executable
int runGame();

#endif // GUESS_NUMBER_H