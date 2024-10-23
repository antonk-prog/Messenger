#include "CApplication.h"
#include "CMenu.h"
#include "CConverter.h"
#include "CInform.h"
#include "CInputWindow.h"
CApplication::CApplication() {
    // m_Storage.load();
}

CApplication::~CApplication() {
    CDisplay::end();
}

void CApplication::run() {
    CDisplay::init();
    mainMenu();
}

void CApplication::mainMenu() {
    CMenu mainMenu({"Log in", "Register", "Exit"},
                   {"", "", ""});

    while (true) {
        int userChoice = mainMenu.runOneChoice();
        switch (userChoice) {
            case 0: 
            {
                // login
                CInputWindow inputWindow_username("Enter username:", true);
                std::wstring login = inputWindow_username.run();
                CInputWindow inputWindow_password("Enter password:", true);
                std::wstring password = inputWindow_password.run();
                break;
            }
                
            case 1: // register
            {
                CInputWindow inputWindow_username("Enter username:", true);
                std::wstring login = inputWindow_username.run();
                CInputWindow inputWindow_password("Enter password:", true);
                std::wstring password = inputWindow_password.run();
                break;
            }
                
                
            case 2: // exit
                {
                    return;
                }
                
        }
    }
}

// void CApplication::search(char type) {
//     CMenu typeMenu({"Text", "Category", "Tag", "Show all", "Back"},
//                    {"Search notes containing given text", "Search notes with category", "Search notes with tag", "Choose from all notes"});
//     int userChoice;
//     while (true) {
//         userChoice = typeMenu.runOneChoice();
//         switch (userChoice) {
//             case 0: // Text
//                 searchByText(type);
//                 break;
//             case 1: // Category
//                 searchCategory(type);
//                 break;
//             case 2: // Tag
//                 searchTag(type);
//                 break;
//             case 3: // Show all
//                 searchAll(type);
//                 break;
//             case 4: // back
//                 return;
//         }
//     }
// }
