#pragma once

#include "CDisplay.h"

/**
 * This class is a controller for the entire application, it starts all processes depending on users needs.
 */
class CApplication {
public:
    CApplication();
    ~CApplication();
    CApplication(const CApplication &) = delete;
    CApplication & operator = (const CApplication &) = delete;

    /**
     * Main menu of the application, can be used to start the application.
     * @return 0 if application encountered no errors (different number if not).
     */
     void run();

private:

    //functions
    void mainMenu();
    // void search(char type);
};