#if !defined(S_URI_HPP)
#define S_URI_HPP

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

#define OK_HTTP_STRING "HTTP/1.0 200 OK\r\n"

struct URIParam
{
    std::string key;
    std::string value;
};

class URI
{
using URI_IT = std::string::iterator;
public:
    std::map<std::string, std::string> params;

    void Parse(std::string& uri)
    {
        URIParam temp;
        URI_IT startParam, endParam, eqChar;
        URI_IT argsStart = std::find(uri.begin(), uri.end() + uri.size(), '?');
        
        if (argsStart == uri.end())
            return ;

        startParam = argsStart;
        while (startParam != uri.end())
        {
            startParam++;
            endParam = std::find(startParam, uri.end(), '&');
            eqChar = std::find(startParam, endParam, '=');
            if (eqChar != endParam)
            {
                if (eqChar + 1 != endParam)
                    params[std::string(startParam, eqChar)] =
                        std::string(eqChar + 1, endParam);
            }
            startParam = endParam;
        }
    }

    std::string urlDecode(std::string &SRC) {
        std::string ret;
        char ch;
        int i, ii;
        for (i=0; i<SRC.length(); i++) {
            if (SRC[i]=='%') {
                sscanf(SRC.substr(i+1,2).c_str(), "%x", &ii);
                ch=static_cast<char>(ii);
                ret+=ch;
                i=i+2;
            } else {
                ret+=SRC[i];
            }
        }
        return (ret);
    }

};

#endif