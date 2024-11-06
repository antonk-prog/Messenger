#include <PostgresAdapter.hpp>
#include <Session.hpp>

#include <iostream>
PostgresAdapter::PostgresAdapter(std::string db_connection_arguments){
    try{
        database_connection = std::make_shared<pqxx::connection>(db_connection_arguments);
    }
    catch (std::exception const &e) {
        std::cerr << "error in PostgresAdapter constructor" << std::endl;
        std::cerr << e.what() << std::endl;
    }
}
void PostgresAdapter::start_session_handler() {
    m_session_handle = true;
    for (int i = 0; i < 1; i++){
        my_threads[i] = std::thread(&PostgresAdapter::m_session_handler, this);
    }
}

void PostgresAdapter::m_session_handler() {
    t_pSession cur_session;

    while (m_session_handle){
        if (m_sessions.empty()){
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            continue;
        }

        while (!m_sessions.empty()){
            {
                std::lock_guard _lock(m_mutex);
                if (m_sessions.empty()) 
                    break;

                    cur_session = std::move(m_sessions.front());
                    m_sessions.pop();
                }
                if (cur_session.get() == nullptr)
                    break;
                handle(cur_session);
                cur_session.reset();
        }
    }
}

void PostgresAdapter::handle(t_pSession session) {
    session->sql_request;
}
