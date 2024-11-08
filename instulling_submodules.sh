#!/bin/bash

echo "script started..."
mkdir deps
cd deps
mkdir httpparser
git init httpparser
cd httpparser
git remote add origin https://github.com/nekipelov/httpparser.git
git config core.sparseCheckout true
echo "/src/httpparser/*" >> .git/info/sparse-checkout
git pull --depth=1 origin master
cd ..

mkdir httprequest
git init httprequest
cd httprequest
git remote add origin https://github.com/elnormous/HTTPRequest.git
git config core.sparseCheckout true
echo "/include/*" >> .git/info/sparse-checkout
git pull --depth=1 origin master
cd ..

mkdir libpqxx
git init libpqxx
cd libpqxx
git remote add origin https://github.com/jtv/libpqxx.git
git config core.sparseCheckout true
echo "/*" >> .git/info/sparse-checkout
git pull --depth=1 origin master
cd ..

mkdir nlohmann
git init nlohmann
cd nlohmann
git remote add origin https://github.com/nlohmann/json.git
git config core.sparseCheckout true
echo "/single_include/*" >> .git/info/sparse-checkout
git pull --depth=1 origin master
cd ..

mkdir sqlbuilder
git init sqlbuilder
cd sqlbuilder
git remote add origin https://github.com/six-ddc/sql-builder.git 
git config core.sparseCheckout true
echo "/sql.h" >> .git/info/sparse-checkout
git pull --depth=1 origin master
cd ..