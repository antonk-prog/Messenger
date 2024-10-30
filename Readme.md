## Dependencies:
This project uses libraries which located in github, so it is needed to submodule them. Also pqxx library uses libpq so it is necessary to download it first. Execute next steps:
1. sudo apt install libpq-dev
2. git submodule init
3. git submodule update
## How to build:


1. mkdir build && cd build
2. cmake ../
3. sudo make install
4. ../bin/Server
5. ../bin/Client


Пользователь (клиент) подключается к серверу (как только запускается приложение). Сервер предлагает зарегестрироваться или войти. Если пользователь выбирает войти, то сервер проверяет, есть ли такой клиент в базе данных, иначе предлагает зарегестрироваться. При регистрации информация о пользователе заносится в базу данных. Пользователь выбирает в меню "найти пользователя", где происходит поиск по логину. Если пользователь существует, отправить ему запрос на "дружбу". Если запрос принят, то "открыть переписку".


В планах:
- юай: написать классы: переделать InputWindow(чтобы в конструкторе можно было указать координаты куда поставить и без лейбла), GlobalWindow (где будут находится ContactsWindow, ChatWindow.)
- написать интерфейс, независящий от протокола, а затем конкретные реализации. Сервер не зависит от реализации протокола.
- написать инструкцию, как установить и использовать проект:
зайти в папку build и выполнить команды:
cmake ../
make install
../bin/client
../bin/server