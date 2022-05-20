#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

class ChatBox
{
public:
    ChatBox();
    ChatBox(const std::string& name);
    ~ChatBox();
    void sendMsg(std::string& msg);  //кладёт строку msg в массив строк m_messages
    void sendMsgFromFile(std::string& msg);  //кладёт строку msg в массив строк m_messages
    void showChatAll() const;             //печатает в консоль весь массив m_messages
    void showChatLast() const;            //печатает в консоль только последнее сообщение (метод не используется...)
    void setChatStatus(bool val);
    bool getChatStatus();
private:
    std::vector<std::string> m_messages;    //массив сообщений
    bool active;      //статус чата: активен или нет в данный момент в клиентской программе, за раз может быть активен только один чат
    std::string filename;       //имя файла, куда будет писаться лог данного чата
    std::fstream m_file;        //файл, в который пишется лог данного чата
    bool m_toggle;              //флаг, который сигнализирует, открывается ли чат первый раз за сессию
};

