#include<ncurses.h>
#include <string>
#include <vector>
int main() {
    WINDOW *people_menu, *chat_window;
    std::vector<std::string> menu_elements {"anton", "elina", "almaz", "gleb"};
    char item[7];
    int ch, cur_peop_ind = 0, width = 7;
    initscr();
    start_color();
    
    // attroff(COLOR_PAIR(1));
    people_menu = newwin( 20, 12, 0, 0 );
    chat_window = newwin(20, 70, 0, 12);

    box(people_menu, 0, 0); // borders
    box(chat_window, 0, 0);
    init_pair(1, COLOR_GREEN, COLOR_WHITE);
    attron(COLOR_PAIR(1));
    mvwprintw(people_menu, 0, 2, "%s", "Contacts");
    mvwprintw(chat_window, 0, 16, "%s", "Chat");
    attroff(COLOR_PAIR(1));
    for( cur_peop_ind=0; cur_peop_ind<menu_elements.size(); cur_peop_ind++ ) {
        if( cur_peop_ind == 0 ) 
            wattron( people_menu, A_STANDOUT ); 
        else
            wattroff( people_menu, A_STANDOUT );
        mvwprintw( people_menu, cur_peop_ind+1, 2, "%-7s", menu_elements[cur_peop_ind].c_str() );
    }
    wrefresh( people_menu );
    wrefresh( chat_window );
    cur_peop_ind = 0;
    noecho();
    keypad( people_menu, TRUE );
    curs_set( 0 );
    while(( ch = wgetch(people_menu)) != 'q'){ 
        mvwprintw( people_menu, cur_peop_ind+1, 2, "%-7s", menu_elements[cur_peop_ind].c_str() ); 
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
        mvwprintw( people_menu, cur_peop_ind+1, 2, "%-7s", menu_elements[cur_peop_ind].c_str());
        wattroff( people_menu, A_STANDOUT );
    }
    delwin( people_menu );
    delwin( chat_window );
    endwin();
    return 0;
}