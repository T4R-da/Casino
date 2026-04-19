#include <iostream>
#include <string>
#include <cstdlib>
#include <array>
#include <conio.h>
#include <vector>
#include <chrono>
#include <thread>
#include <windows.h>

// ANSI Colors
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define CYAN    "\033[36m"
#define YELLOW  "\033[33m"
#define BOLD    "\033[1m"
#define GREEN   "\033[32m"
#define MAGENTA "\033[35m"


inline void clearScreen() { system("cls"); }

inline void bootingSequence() {
    clearScreen();
    std::cout << CYAN << BOLD << "[SYSTEM]: INITIALIZING ASSETS..." << RESET << "\n";
    std::cout << "[";
    for(int i=0; i<30; i++) {
        std::cout << "#";
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }
    std::cout << "] 100%\n";
    std::cout << GREEN << "ASSETS LOADED." << RESET << "\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

void logo() {
    std::vector<std::string> casinoLogo = {
        " $$$$$$\\   $$$$$$\\   $$$$$$\\  $$$$$$\\ $$\\   $$\\  $$$$$$\\  ",
        "$$  __$$\\ $$  __$$\\ $$  __$$\\ \\_$$  _|$$$\\  $$ |$$  __$$\\ ",
        "$$ /  \\__|$$ /  $$ |$$ /  \\__|  $$ |  $$$$\\ $$ |$$ /  $$ |",
        "$$ |      $$$$$$$$ |\\$$$$$$\\    $$ |  $$ $$\\$$ |$$ |  $$ |",
        "$$ |      $$  __$$ | \\____$$\\   $$ |  $$ \\$$$$ |$$ |  $$ |",
        "$$ |  $$\\ $$ |  $$ |$$\\   $$ |  $$ |  $$ |\\$$$ |$$ |  $$ |",
        "\\$$$$$$  |$$ |  $$ |\\$$$$$$  |$$$$$$\\ $$ | \\$$ | $$$$$$  |",
        " \\______/ \\__|  \\__| \\______/ \\______||\\__|  \\__| \\______/ "};

    for (size_t i = 0; i < casinoLogo.size(); i++) {
        std::cout << RED << BOLD << "  " << casinoLogo[i] << RESET << "\n";
    }
}