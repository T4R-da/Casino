#include "logo.hpp"
#include "miniaudio.h"

// ANSI Colors
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define CYAN    "\033[36m"
#define YELLOW  "\033[33m"
#define BOLD    "\033[1m"
#define GREEN   "\033[32m"
#define MAGENTA "\033[35m"

void printMenu(const std::array<std::string, 4>& options, const std::array<std::string, 4>& names, int selected) {
    std::cout << "\033[" << options.size() << "A";

    for (int i = 0; i < (int)options.size(); i++) {
        if (i == selected)
            std::cout << GREEN << BOLD << "  > " << names[i] << RESET << "   \n";
        else
            std::cout << "    " << names[i] << "   \n";
    }
}

int main() {
    std::string FILES_DIR = "Z:\\! coding\\C++\\! builds\\"; // modify this based on where you put the files 
    std::array<std::string, 4> options = {"Black-Jack-sim\\blackjack.exe","Poker-sim\\Poker-sim.exe","Roulette-simulator\\roulette.exe", "Texas_holdem-sim\\poker-sim.exe"};
    std::array<std::string, 4> names = {"Black Jack", "Poker 5 Card", "Roulette", "Texas Hold'em"};
    std::string Black_Jack = options[0]; std::string Poker_5card = options[1]; std::string Roulette = options[2]; std::string Texas_holdem = options[3];

    bootingSequence();
    clearScreen();
    // Audio Initialization with looping background music
    ma_engine engine;
    ma_sound bgSound;
    bool audioEnabled = false;
    
    if (ma_engine_init(NULL, &engine) == MA_SUCCESS) {
        if (ma_sound_init_from_file(&engine, "sound.wav", MA_SOUND_FLAG_STREAM, NULL, NULL, &bgSound) == MA_SUCCESS) {
            ma_sound_set_looping(&bgSound, true);
            ma_sound_start(&bgSound);
            audioEnabled = true;
        }
    }

    logo();
    std::cout << CYAN << "\nUse UP/DOWN arrows and ENTER to select:\n\n" << RESET;

    int selected = 0;
    for (int i = 0; i < (int)options.size(); i++) {
        if (i == selected)
            std::cout << GREEN << BOLD << "  > " << names[i] << RESET << "   \n";
        else
            std::cout << "    " << names[i] << "   \n";
    }

    while (true) {
        int key = _getch();

        if (key == 224) {
            int arrow = _getch();
            if (arrow == 72) selected = (selected - 1 + options.size()) % options.size();
            if (arrow == 80) selected = (selected + 1) % options.size();
            printMenu(options, names, selected);
        }

        if (key == 13) {
            if (audioEnabled) {
                ma_sound_stop(&bgSound);
                ma_sound_uninit(&bgSound);
                audioEnabled = false;
            }
            break;
        }
    }

    // Cleanup engine (sound already handled above if audio was enabled)
    ma_engine_uninit(&engine);

    std::cout << "\n" << YELLOW << "Launching: " << options[selected] << RESET << "\n";
    std::string fullPath = "\"" + FILES_DIR + options[selected] + "\"";

    // Change working directory to the target exe's folder
    std::string exeDir = FILES_DIR + options[selected];
    exeDir = exeDir.substr(0, exeDir.find_last_of("\\/"));
    SetCurrentDirectoryA(exeDir.c_str()); // Windows API, include <windows.h>

    std::system(fullPath.c_str());

    return 0;
}