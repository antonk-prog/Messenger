#!/bin/bash
echo "started script..."
mkdir deps
cd deps
mkdir httpparser
cd httpparser
git clone https://github.com/nekipelov/httpparser.git .
cd ..
mkdir httprequest
cd httprequest
git clone https://github.com/elnormous/HTTPRequest.git .
cd ..
mkdir libpqxx
cd libpqxx
git clone https://github.com/jtv/libpqxx.git .
cd ..
mkdir nlohmann
cd nlohmann
git clone https://github.com/nlohmann/json.git .
cd ..
mkdir sqlbuilder
cd sqlbuilder
git clone https://github.com/six-ddc/sql-builder.git .
cd ..
echo "script finished working"
