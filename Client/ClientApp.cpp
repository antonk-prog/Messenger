#include <ncurses.h>
#include <vector>
#include <string>

#define PEOPLE_HEIGHT 20
#define PEOPLE_WIDTH 12
#define CHAT_HEIGHT 20
#define CHAT_WIDTH 60
#define FULL_HEIGHT 20
#define FULL_WIDTH 70

int main() {
    
    WINDOW *people_menu, *chat_window, *auth_window;
    int auth_window_ind = 0;
    bool is_logged = false;
    std::vector<std::string> menu_elements {"Alexandr", "Marina", "Uliana"};
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
                is_logged = true;
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
    noecho();
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