#include <AuthCollectorBase.hpp>

AuthCollectorBase::AuthCollectorBase() {
}

bool AuthCollectorBase::checkUserExists(char* username, char* pass)
{
	return true;
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
		return true;
	} 
	return false;
}
