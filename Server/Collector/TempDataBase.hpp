#include <mutex>
#include <map>
class DataBaseAccounts {
    public:
        DataBaseAccounts() = default;
        ~DataBaseAccounts() = default;

        bool addAccount(std::string username, std::string password) {
            {
                std::lock_guard<std::mutex> lock(m_mutex); 
                if (!isUserExists(username)) {
                    data.insert({username, password});
                    return true;
                }
                return false;
            }
        }
        bool isUserExists(std::string username){
            auto it = data.find(username);
            if (it != data.end()) return true;
            return false;
        }
    private:
        std::mutex m_mutex;
        std::map<std::string, std::string> data; // login password
};

using t_pAccountsCollector = std::shared_ptr<DataBaseAccounts>;