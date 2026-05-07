#include "logo.hpp"
#include "miniaudio.h"
#include <iostream>
#include <string>
#include <array>
#include <windows.h>
#include <conio.h>
#include <filesystem> // Required for smart path handling

namespace fs = std::filesystem;

// ANSI Colors
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define CYAN    "\033[36m"
#define YELLOW  "\033[33m"
#define BOLD    "\033[1m"
#define GREEN   "\033[32m"

void printMenu(const std::array<std::string, 5>& names, int selected) {
    std::cout << "\033[" << names.size() << "A";
    for (int i = 0; i < (int)names.size(); i++) {
        if (i == selected)
            std::cout << GREEN << BOLD << "  > " << names[i] << RESET << "   \n";
        else
            std::cout << "    " << names[i] << "   \n";
    }
}

int main() {
    // 1. Get the current EXE path
    char pathBuffer[MAX_PATH];
    GetModuleFileNameA(NULL, pathBuffer, MAX_PATH);
    fs::path currentPath = fs::path(pathBuffer).parent_path();

    // 2. FIND THE CASINO ROOT
    // This loop climbs up from "! builds\Casino" to the main "C++" folder,
    // then looks for the "Casino" folder that actually contains the repos.
    fs::path rootPath;
    bool found = false;

    // Check current folder, then parent, then grandparent...
    for (auto p = currentPath; p.has_relative_path(); p = p.parent_path()) {
        // Look for the folder that contains repo1
        if (fs::exists(p / "repo1")) {
            rootPath = p;
            found = true;
            break;
        }
        // Also check if we are in a sibling structure (climb out of '! builds' into 'C++' then into 'Casino')
        if (fs::exists(p.parent_path() / "Casino" / "repo1")) {
            rootPath = p.parent_path() / "Casino";
            found = true;
            break;
        }
    }

    // Fallback to current directory if searching fails
    if (!found) rootPath = currentPath;

    std::array<std::string, 5> relativePaths = {
        "repo1\\src\\blackjack.exe", 
        "repo2\\src\\Poker-sim.exe", 
        "repo3\\src\\poker-sim.exe", 
        "repo4\\src\\roulette.exe"
        "repo5\\src\\slot_machine.exe"
    };
    std::array<std::string, 5> names = {"Black Jack", "Poker 5 Card", "Texas Hold'em", "Roulette", "Slot Machine"};

    bootingSequence();
    clearScreen();

    // Audio Initialization
    ma_engine engine;
    ma_sound bgSound;
    bool audioEnabled = false;
    if (ma_engine_init(NULL, &engine) == MA_SUCCESS) {
        // Try to find sound.wav in the EXE folder or the Root folder
        std::string soundPath = "sound.wav";
        if (!fs::exists(soundPath)) soundPath = (rootPath / "sound.wav").string();

        if (ma_sound_init_from_file(&engine, soundPath.c_str(), MA_SOUND_FLAG_STREAM, NULL, NULL, &bgSound) == MA_SUCCESS) {
            ma_sound_set_looping(&bgSound, true);
            ma_sound_start(&bgSound);
            audioEnabled = true;
        }
    }

    logo();
    std::cout << CYAN << "\nUse UP/DOWN arrows and ENTER to select:\n\n" << RESET;

    int selected = 0;
    for (int i = 0; i < (int)names.size(); i++) {
        if (i == selected) std::cout << GREEN << BOLD << "  > " << names[i] << RESET << "   \n";
        else std::cout << "    " << names[i] << "   \n";
    }

    while (true) {
        int key = _getch();
        if (key == 224) {
            int arrow = _getch();
            if (arrow == 72) selected = (selected - 1 + 4) % 4;
            if (arrow == 80) selected = (selected + 1) % 4;
            printMenu(names, selected);
        }
        if (key == 13) break;
    }

    if (audioEnabled) {
        ma_sound_stop(&bgSound);
        ma_sound_uninit(&bgSound);
        ma_engine_uninit(&engine);
    }

    // 3. LAUNCHING
    fs::path fullExePath = rootPath / relativePaths[selected];
    std::string targetDir = fullExePath.parent_path().string();
    std::string exeName = fullExePath.filename().string();

    if (SetCurrentDirectoryA(targetDir.c_str())) {
        // Triple quotes to handle the '!' and spaces in your path
        std::string command = "start \"\" \"" + exeName + "\"";
        std::system(command.c_str());
    } else {
        std::cerr << RED << "\nError: Could not find game folder!" << RESET << "\n";
        std::cerr << "Tried: " << targetDir << "\n";
        system("pause");
    }

    return 0;
}