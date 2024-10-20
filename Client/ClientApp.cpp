#include <ncurses.h>
#include <vector>
#include <string>
#include <string>
#include <iostream>
#include <HTTPRequest.hpp>
#define PEOPLE_HEIGHT 20
#define PEOPLE_WIDTH 12
#define CHAT_HEIGHT 20
#define CHAT_WIDTH 60
#define FULL_HEIGHT 20
#define FULL_WIDTH 70

int main() {

    // try
    // {
    //     http::Request request{"http://localhost:8484/api/v1/login"};
    //     const std::string body = "username=anton&password=123";
    //     const auto response = request.send("POST", body, {
    //         {"Content-Type", "application/x-www-form-urlencoded"}
    //     });
    //     std::cout << "response.status: " << std::endl;
    //     std::cout << response.status.code << " " << response.status.reason << std::endl;
    //     std::cout << "response.headerFields: " << std::endl;
    //     for (int i = 0; i < response.headerFields.size(); i++){
    //         std::cout << response.headerFields[i].first << " " << response.headerFields[i].second << std::endl;
    //     }
    //     // std::cout << std::string{response.headerFields.begin(), response.headerFields.end()} << '\n';
    //     std::cout << std::string{response.body.begin(), response.body.end()} << '\n'; // print the result
    // }
    // catch (const std::exception& e)
    // {
    //     std::cerr << "Request failed, error: " << e.what() << '\n';
    // }   
    
    WINDOW *people_menu,  *chat_window, *auth_window, *log_window, *reg_window;
    int auth_window_ind = 0;
    bool is_logged = false;
    std::vector<std::string> menu_elements {"antoska", "glebok", "uliana"};
    menu_elements.push_back("SEARCH");
    menu_elements.push_back("SETTINGS");
    int ch, cur_peop_ind = 0;
    initscr();
    curs_set(0);
    auth_window = newwin(FULL_HEIGHT, FULL_WIDTH, 0, 0);
    box(auth_window, 0, 0);
    wattron(auth_window, A_STANDOUT);
    mvwprintw(auth_window, FULL_HEIGHT/2-1, FULL_WIDTH/2-5, "%s", "Log in");
    wattroff(auth_window, A_STANDOUT);
    mvwprintw(auth_window, FULL_HEIGHT/2, FULL_WIDTH/2-5, "%s", "Registrate");
    wrefresh(auth_window);
    noecho();
    keypad(auth_window, TRUE);
    while(!is_logged){ 
        
        ch = wgetch(auth_window);
        if (auth_window_ind==0)  mvwprintw(auth_window, FULL_HEIGHT/2-1, FULL_WIDTH/2-5, "%s", "Log in");
        else mvwprintw(auth_window, FULL_HEIGHT/2, FULL_WIDTH/2-5, "%s", "Registrate");
        switch( ch ) {
            case KEY_UP:
                auth_window_ind--;
                auth_window_ind = ( auth_window_ind<0 ) ? 1 : 0;
                break;
            case KEY_DOWN:
                auth_window_ind++;
                auth_window_ind = ( auth_window_ind > 1 ) ? 0 : 1;
                break;
            case '\n': // KEY_ENTER
                curs_set(2);
                std::string username;
                std::string password;
                if (auth_window_ind == 0){ // Log in
                    log_window = newwin(FULL_HEIGHT, FULL_WIDTH, 0, 0);
                    bool entered_username = false;
                    bool entered_password = false;
                    box(log_window, 0, 0);
                    // move(FULL_HEIGHT / 4, FULL_WIDTH/2-1)
                    mvwprintw(log_window, FULL_HEIGHT / 4, FULL_WIDTH/2-15, "%s", "Enter username:");
                    mvwprintw(log_window, (FULL_HEIGHT / 4) * 2, FULL_WIDTH/2-15, "%s", "Enter password:");
                    wrefresh(log_window);
                    keypad(log_window, TRUE);
                    wmove(log_window, FULL_HEIGHT / 4, FULL_WIDTH/2+2);

                    int start_cursor_x = getcurx(log_window);

                    while (!entered_username){
                        ch = wgetch(log_window);
                        if (ch == '\n'){
                            entered_username = true;
                        }
                        
                        if (ch == KEY_BACKSPACE){
                            if (start_cursor_x < getcurx(log_window)){
                                wmove(log_window, getcury(log_window), getcurx(log_window)-1);
                                waddch(log_window, ' ');
                                wmove(log_window, getcury(log_window), getcurx(log_window)-1);
                            }
                            
                        }else{
                            if (getcurx(log_window) < FULL_WIDTH-5){
                                waddch(log_window,  ch | A_BOLD | A_UNDERLINE);
                                username += ch;
                            }   
                        }
                        
                    }
                    wmove(log_window, (FULL_HEIGHT / 4)*2, FULL_WIDTH/2+2);
                    start_cursor_x = getcurx(log_window);
                    while (!entered_password){
                        ch = wgetch(log_window);
                        if (ch == '\n'){
                            entered_password = true;
                        }
                        
                        if (ch == KEY_BACKSPACE){
                            if (start_cursor_x < getcurx(log_window)){
                                wmove(log_window, getcury(log_window), getcurx(log_window)-1);
                                waddch(log_window, ' ');
                                wmove(log_window, getcury(log_window), getcurx(log_window)-1);
                            }
                            
                        }else{
                            if (getcurx(log_window) < FULL_WIDTH-5){
                                waddch(log_window,  ch | A_BOLD | A_UNDERLINE);
                                password += ch;
                            }   
                        }
                    }
                    http::Response response;
                    try
                    {
                        http::Request request{"http://localhost:8484/api/v1/login"};
                        const std::string body = "username=" + username + "&password=" + password;
                        response = request.send("POST", body, {
                            {"Content-Type", "application/x-www-form-urlencoded"}
                        });
                        // std::cout << "response.status: " << std::endl;
                        // std::cout << response.status.code << " " << response.status.reason << std::endl;
                        // std::cout << "response.headerFields: " << std::endl;
                        // for (int i = 0; i < response.headerFields.size(); i++){
                            // std::cout << response.headerFields[i].first << " " << response.headerFields[i].second << std::endl;
                        // }
                    }

                    catch (const std::exception& e)
                    {
                        std::cerr << "Request failed, error: " << e.what() << '\n';
                    }
                    if (std::string{response.body.begin(), response.body.end()} == "OK") // send hhtp post request and check if succeded to create user account :
                    {

                        curs_set(0);
                        clear();
                        refresh();
                        box(auth_window, 0, 0);

                        wattroff(auth_window, A_STANDOUT);
                        mvwprintw(auth_window, FULL_HEIGHT/2-1, FULL_WIDTH/2-5, "%s", "Log in");
                        wattron(auth_window, A_STANDOUT);
                        mvwprintw(auth_window, FULL_HEIGHT/2, FULL_WIDTH/2-5, "%s", "Registrate");
                        keypad(auth_window, TRUE);
                        break;
                    }
                    if (true) // send hhtp post request and check if user exists. if true:
                    {
                        is_logged = true;
                        break;
                    }
                } else {  // Register
                    log_window = newwin(FULL_HEIGHT, FULL_WIDTH, 0, 0);
                    bool entered_username = false;
                    bool entered_password = false;
                    box(log_window, 0, 0);
                    // move(FULL_HEIGHT / 4, FULL_WIDTH/2-1)
                    mvwprintw(log_window, FULL_HEIGHT / 4, FULL_WIDTH/2-15, "%s", "Enter username:");
                    mvwprintw(log_window, (FULL_HEIGHT / 4) * 2, FULL_WIDTH/2-15, "%s", "Enter password:");
                    wrefresh(log_window);
                    keypad(log_window, TRUE);
                    wmove(log_window, FULL_HEIGHT / 4, FULL_WIDTH/2+2);

                    int start_cursor_x = getcurx(log_window);

                    while (!entered_username){
                        ch = wgetch(log_window);
                        if (ch == '\n'){
                            entered_username = true;
                        }
                        
                        if (ch == KEY_BACKSPACE){
                            if (start_cursor_x < getcurx(log_window)){
                                wmove(log_window, getcury(log_window), getcurx(log_window)-1);
                                waddch(log_window, ' ');
                                wmove(log_window, getcury(log_window), getcurx(log_window)-1);
                            }
                            
                        }else{
                            if (getcurx(log_window) < FULL_WIDTH-5){
                                waddch(log_window,  ch | A_BOLD | A_UNDERLINE);
                                username += ch;
                            }   
                        }
                        
                    }
                    wmove(log_window, (FULL_HEIGHT / 4)*2, FULL_WIDTH/2+2);
                    start_cursor_x = getcurx(log_window);
                    while (!entered_password){
                        ch = wgetch(log_window);
                        if (ch == '\n'){
                            entered_password = true;
                        }
                        
                        if (ch == KEY_BACKSPACE){
                            if (start_cursor_x < getcurx(log_window)){
                                wmove(log_window, getcury(log_window), getcurx(log_window)-1);
                                waddch(log_window, ' ');
                                wmove(log_window, getcury(log_window), getcurx(log_window)-1);
                            }
                            
                        }else{
                            if (getcurx(log_window) < FULL_WIDTH-5){
                                waddch(log_window,  ch | A_BOLD | A_UNDERLINE);
                                password += ch;
                            }   
                        }
                    }
                    http::Response response;
                    try
                    {
                        http::Request request{"http://localhost:8484/api/v1/registrate"};
                        const std::string body = "username=" + username + "&password=" + password;
                        response = request.send("POST", body, {
                            {"Content-Type", "application/x-www-form-urlencoded"}
                        });
                        // std::cout << "response.status: " << std::endl;
                        // std::cout << response.status.code << " " << response.status.reason << std::endl;
                        // std::cout << "response.headerFields: " << std::endl;
                        // for (int i = 0; i < response.headerFields.size(); i++){
                            // std::cout << response.headerFields[i].first << " " << response.headerFields[i].second << std::endl;
                        // }
                    }

                    catch (const std::exception& e)
                    {
                        std::cerr << "Request failed, error: " << e.what() << '\n';
                    }
                    if (std::string{response.body.begin(), response.body.end()} == "OK") // send hhtp post request and check if succeded to create user account :
                    {
                        // show window that registration succeded

                        // delwin(log_window);
                        curs_set(0);
                        clear();
                        refresh();
                        box(auth_window, 0, 0);

                        wattroff(auth_window, A_STANDOUT);
                        mvwprintw(auth_window, FULL_HEIGHT/2-1, FULL_WIDTH/2-5, "%s", "Log in");
                        wattron(auth_window, A_STANDOUT);
                        mvwprintw(auth_window, FULL_HEIGHT/2, FULL_WIDTH/2-5, "%s", "Registrate");
                        keypad(auth_window, TRUE);
                        break;
                    }
                }
                break;
        }
        wattron( auth_window, A_STANDOUT );
        if (auth_window_ind==0)  mvwprintw(auth_window, FULL_HEIGHT/2-1, FULL_WIDTH/2-5, "%s", "Log in");
        else mvwprintw(auth_window, FULL_HEIGHT/2, FULL_WIDTH/2-5, "%s", "Registrate");
        wattroff( auth_window, A_STANDOUT );
    }
    clear();



    people_menu = newwin( PEOPLE_HEIGHT, PEOPLE_WIDTH, 0, 0 );
    chat_window = newwin(CHAT_HEIGHT, CHAT_WIDTH, 0, 12);
    curs_set(0);
    box(people_menu, 0, 0); // borders
    box(chat_window, 0, 0);
    mvwprintw(people_menu, 0, 2, "%s", "Contacts");
    mvwprintw(chat_window, 0, 16, "%s", "Chat");
    for( cur_peop_ind=0; cur_peop_ind<menu_elements.size()-2; cur_peop_ind++ ) {
        if( cur_peop_ind == 0 ) 
            wattron( people_menu, A_STANDOUT ); 
        else
            wattroff( people_menu, A_STANDOUT );
        mvwprintw( people_menu, cur_peop_ind+1, 2, "%-7s", menu_elements[cur_peop_ind].c_str() );
    }
    mvwprintw( people_menu, PEOPLE_HEIGHT-3, 2, "%-7s", menu_elements[cur_peop_ind].c_str() );
    cur_peop_ind++;
    mvwprintw( people_menu, PEOPLE_HEIGHT-2, 2, "%-7s", menu_elements[cur_peop_ind].c_str() );


    wrefresh( people_menu );
    wrefresh( chat_window );
    cur_peop_ind = 0;
    
    keypad( people_menu, TRUE );
    while(( ch = wgetch(people_menu)) != 'q'){ 

        if (menu_elements[cur_peop_ind] == "SEARCH") mvwprintw( people_menu, PEOPLE_HEIGHT-3, 2, "%-7s", menu_elements[cur_peop_ind].c_str() ); 
        else if (menu_elements[cur_peop_ind] == "SETTINGS") mvwprintw( people_menu, PEOPLE_HEIGHT-2, 2, "%-7s", menu_elements[cur_peop_ind].c_str() ); 
        else mvwprintw( people_menu, cur_peop_ind+1, 2, "%-7s", menu_elements[cur_peop_ind].c_str() ); 
        switch( ch ) {
            case KEY_UP:
                cur_peop_ind--;
                cur_peop_ind = ( cur_peop_ind<0 ) ? (menu_elements.size()-1) : cur_peop_ind;
                break;
            case KEY_DOWN:
                cur_peop_ind++;
                cur_peop_ind = ( cur_peop_ind>menu_elements.size()-1 ) ? 0 : cur_peop_ind;
                break;
        }
        wattron( people_menu, A_STANDOUT );
        if (menu_elements[cur_peop_ind] == "SEARCH") mvwprintw( people_menu, PEOPLE_HEIGHT-3, 2, "%-7s", menu_elements[cur_peop_ind].c_str() ); 
        else if (menu_elements[cur_peop_ind] == "SETTINGS") mvwprintw( people_menu, PEOPLE_HEIGHT-2, 2, "%-7s", menu_elements[cur_peop_ind].c_str() ); 
        else mvwprintw( people_menu, cur_peop_ind+1, 2, "%-7s", menu_elements[cur_peop_ind].c_str() ); 
        wattroff( people_menu, A_STANDOUT );
    }
    delwin( people_menu );
    delwin( chat_window );
    delwin(auth_window);
    endwin();
    return 0;
}