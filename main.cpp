#include<ncurses.h>
#include <vector>
#include <string>

#define PEOPLE_HEIGHT 20
#define PEOPLE_WIDTH 12
#define CHAT_HEIGHT 20
#define CHAT_WIDTH 60

int main() {
    WINDOW *people_menu, *chat_window;
    std::vector<std::string> menu_elements {};
    menu_elements.push_back("SEARCH");
    menu_elements.push_back("SETTINGS");
    int ch, cur_peop_ind = 0;
    initscr();
    
    // attroff(COLOR_PAIR(1));
    people_menu = newwin( PEOPLE_HEIGHT, PEOPLE_WIDTH, 0, 0 );
    chat_window = newwin(CHAT_HEIGHT, CHAT_WIDTH, 0, 12);

    box(people_menu, 0, 0); // borders
    box(chat_window, 0, 0);
    attron(COLOR_PAIR(0));
    mvwprintw(people_menu, 0, 2, "%s", "Contacts");
    mvwprintw(chat_window, 0, 16, "%s", "Chat");
    attroff(COLOR_PAIR(0));
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
    curs_set( 0 );
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
    endwin();
    return 0;
}