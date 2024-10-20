#include <AuthCollectorBase.hpp>

AuthCollectorBase::AuthCollectorBase(t_pAccountsCollector accounts_collector) {
	this->accounts_collector = accounts_collector;
}

bool AuthCollectorBase::checkUserExists(char* username, char* pass)
{
	if (accounts_collector->isUserExists(std::string(username))) return true;
	return false;
}

unsigned long AuthCollectorBase::getIdByUsername(char* username)
{
	/*
	TODO
	inv id by username from DB
	*/
	if (username == std::string("anton"))
		return 0;
	return 1;
}

unsigned long AuthCollectorBase::getIdByHash(std::string& hash)
{
	return m_ses[hash].getId();
}

std::string AuthCollectorBase::login(char* username, char* pass)
{
	if (!checkUserExists(username, pass))
		return std::string();

	std::string hash;
	AuthSessionBase ses(
		username,
		pass,
		getIdByUsername(username)
	);
	hash = ses.getHash();
	m_ses.insert(std::pair{hash, std::move(ses)});
	
	return hash;
}

bool AuthCollectorBase::registrate(char* username, char* pass){
	if (!checkUserExists(username, pass)){
		accounts_collector->addAccount(username, pass);
		return true;
	} 
	return false;
}
