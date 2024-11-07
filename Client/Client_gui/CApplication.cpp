#include "CApplication.h"
#include "CMenu.h"
#include "CConverter.h"
#include "CInform.h"
#include "CInputWindow.h"

#include <HTTPRequest.hpp>
#include <iostream>
#include <vector>
#include <string>
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

                http::Response response;
                try
                    {
                        http::Request request{"http://localhost:8484/api/v1/login"};

                        const std::string body = "username=" + std::string(login.begin(), login.end()) + "&password=" + std::string(password.begin(), password.end());
                        response = request.send("POST", body, {
                            {"Content-Type", "application/x-www-form-urlencoded"}
                        });
                        std::string response_status = "";
                        std::string response_problem = "";
                                                        exit(0);

                        for (int i = 0; i < response.headerFields.size(); i++){
                            if (response.headerFields[i].first == "Success"){
                                response_status = response.headerFields[i].second; 
                            }
                            if (response.headerFields[i].first == "Problem"){
                                response_problem = response.headerFields[i].second;
                            }
                        }

                        if (response_status == "yes"){
                            exit(0);
                        }
                        // std::cout << "response.status: " << std::endl;
                        // std::cout << response.status.code << " " << response.status.reason << std::endl;
                        // std::cout << "response.headerFields: " << std::endl;
                        // for (int i = 0; i < response.headerFields.size(); i++){
                        //     std::cout << response.headerFields[i].first << " " << response.headerFields[i].second << std::endl;
                        // }
                    }

                    catch (const std::exception& e)
                    {
                        std::cerr << "Request failed, error: " << e.what() << '\n';
                    }
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
