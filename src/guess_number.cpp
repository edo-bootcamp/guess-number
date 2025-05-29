
#include "guess_number.h"
#include "random_code_generator.h"
#include <iostream>
#include <sstream>
#include <set>

GuessNumberGame::GuessNumberGame() 
    : codeGenerator(std::make_unique<RandomCodeGenerator>()) {
    startNewGame();
}

GuessNumberGame::GuessNumberGame(std::unique_ptr<CodeGenerator> generator)
    : codeGenerator(std::move(generator)) {
    startNewGame();
}

void GuessNumberGame::startNewGame() {
    remainingAttempts = MAX_ATTEMPTS;
    gameWon = false;
    history.clear();
    secretCode = codeGenerator->generateCode();
}

std::string GuessNumberGame::processGuess(const std::array<int, 4>& guess) {
    int exactMatches = 0;  // A count (right number in right position)
    int valueMatches = 0;  // B count (right number in wrong position)
    
    // Arrays to track which positions were used
    std::array<bool, 4> secretUsed = {false, false, false, false};
    std::array<bool, 4> guessUsed = {false, false, false, false};
    
    // First pass: find exact matches (A count)
    for (int i = 0; i < 4; ++i) {
        if (guess[i] == secretCode[i]) {
            exactMatches++;
            secretUsed[i] = true;
            guessUsed[i] = true;
        }
    }
    
    // Second pass: find number matches in wrong positions (B count)
    for (int i = 0; i < 4; ++i) {
        if (guessUsed[i]) continue; // Skip already matched positions
        
        for (int j = 0; j < 4; ++j) {
            if (secretUsed[j]) continue; // Skip already matched positions
            if (guess[i] == secretCode[j]) {
                valueMatches++;
                secretUsed[j] = true;
                break;
            }
        }
    }
    
    // Format and return result
    std::ostringstream result;
    result << exactMatches << "A" << valueMatches << "B";
    
    // Update game state
    remainingAttempts--;
    if (exactMatches == 4) {
        gameWon = true;
    }
    
    // Add to history
    history.push_back({guess, result.str()});
    
    return result.str();
}

bool GuessNumberGame::isValidInput(const std::array<int, 4>& guess) const {
    std::set<int> uniqueDigits;
    
    for (int digit : guess) {
        // Check if digit is between 0-9
        if (digit < 0 || digit > 9) {
            return false;
        }
        
        // Check for duplicates
        if (uniqueDigits.count(digit) > 0) {
            return false;
        }
        
        uniqueDigits.insert(digit);
    }
    
    return uniqueDigits.size() == 4;
}

bool GuessNumberGame::hasWon() const {
    return gameWon;
}

bool GuessNumberGame::hasLost() const {
    return remainingAttempts <= 0 && !gameWon;
}

int GuessNumberGame::getRemainingAttempts() const {
    return remainingAttempts;
}

const std::vector<std::pair<std::array<int, 4>, std::string>>& GuessNumberGame::getHistory() const {
    return history;
}

const std::array<int, 4>& GuessNumberGame::getSecretCode() const {
    return secretCode;
}

void playGuessNumberGame() {
    GuessNumberGame game;
    
    std::cout << "Welcome to Guess Number Game!" << std::endl;
    std::cout << "Try to guess the 4-digit secret code. Each digit is between 0-9 and no duplicates." << std::endl;
    std::cout << "After each guess, you'll get feedback in the format xAyB:" << std::endl;
    std::cout << "- x is the number of correct digits in the correct position (A)" << std::endl;
    std::cout << "- y is the number of correct digits in the wrong position (B)" << std::endl;
    std::cout << "You have " << game.getRemainingAttempts() << " attempts. Good luck!" << std::endl << std::endl;

    while (!game.hasWon() && !game.hasLost()) {
        // Display attempt information
        std::cout << "Attempt " << (6 - game.getRemainingAttempts() + 1) << " of 6" << std::endl;
        
        // Display history
        const auto& history = game.getHistory();
        if (!history.empty()) {
            std::cout << "Previous guesses:" << std::endl;
            for (size_t i = 0; i < history.size(); ++i) {
                const auto& entry = history[i];
                std::cout << "  " << (i+1) << ": ";
                for (int digit : entry.first) {
                    std::cout << digit << " ";
                }
                std::cout << "-> " << entry.second << std::endl;
            }
            std::cout << std::endl;
        }
        
        // Get user input
        std::array<int, 4> guess;
        bool validInput = false;
        
        while (!validInput) {
            std::cout << "Enter your guess (4 distinct digits from 0-9, separated by spaces): ";
            
            // Read user input
            std::string input;
            std::getline(std::cin, input);
            std::istringstream iss(input);
            
            // Try to parse 4 integers
            int count = 0;
            int num;
            
            while (iss >> num && count < 4) {
                guess[count++] = num;
            }
            
            // Check if exactly 4 numbers were provided
            if (count != 4) {
                std::cout << "Wrong Input, Input again" << std::endl;
                continue;
            }
            
            // Validate the input numbers
            if (game.isValidInput(guess)) {
                validInput = true;
            } else {
                std::cout << "Wrong Input, Input again" << std::endl;
            }
        }
        
        // Process the guess
        std::string result = game.processGuess(guess);
        std::cout << "Result: " << result << std::endl << std::endl;
        
        // Check if the player won
        if (game.hasWon()) {
            std::cout << "Congratulations! You've guessed the secret code!" << std::endl;
        } 
        // Check if the player lost
        else if (game.hasLost()) {
            std::cout << "Game over! You've used all your attempts." << std::endl;
            std::cout << "The secret code was: ";
            for (int digit : game.getSecretCode()) {
                std::cout << digit << " ";
            }
            std::cout << std::endl;
        }
    }
    
    // Ask if the player wants to play again
    std::cout << "Would you like to play again? (y/n): ";
    char response;
    std::cin >> response;
    std::cin.ignore(); // Clear the newline character
    
    if (response == 'y' || response == 'Y') {
        playGuessNumberGame();
    } else {
        std::cout << "Thank you for playing!" << std::endl;
    }
}

int runGame() {
    playGuessNumberGame();
    return 0;
}