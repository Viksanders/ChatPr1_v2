#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "LinkStorage.h"
#include "ChatBox.h"
#include "User.h"
#include "UserStorage.h"

enum STATE { MainMenu, Registration, LogInScreen, LogOutScreen, Typing, Exit };

class Shell
{
public:
    Shell();
    ~Shell();
    void close();           //команда на закрытие чата, выставляющая флаг во внешний мир о том, что чат нужно закрыть
    bool isOpened() const;        //проверить статус флага открытости чата
    void work();            //main loop
private:
    UserStorage m_users;
    LinkStorage m_links;
    std::shared_ptr<User> m_YOU;              //указатель на текущего залогиненного пользователя
    std::shared_ptr<ChatBox> m_CHAT;          //указатель на текущий активный чат
    bool m_active;          //флаг для сообщения внешнему миру о том, что чат не работает и его надо закрывать

    STATE registration();    //регистрация нового юзера
    STATE logIn();           //вход за старого юзера
    STATE logOut();          //выход за текущего юзера
    STATE MainMenuFcn();
    STATE MsgOrCmd();        //ввод сообщения или команды
};



