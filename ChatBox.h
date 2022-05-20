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
    void sendMsg(std::string& msg);  //����� ������ msg � ������ ����� m_messages
    void sendMsgFromFile(std::string& msg);  //����� ������ msg � ������ ����� m_messages
    void showChatAll() const;             //�������� � ������� ���� ������ m_messages
    void showChatLast() const;            //�������� � ������� ������ ��������� ��������� (����� �� ������������...)
    void setChatStatus(bool val);
    bool getChatStatus();
private:
    std::vector<std::string> m_messages;    //������ ���������
    bool active;      //������ ����: ������� ��� ��� � ������ ������ � ���������� ���������, �� ��� ����� ���� ������� ������ ���� ���
    std::string filename;       //��� �����, ���� ����� �������� ��� ������� ����
    std::fstream m_file;        //����, � ������� ������� ��� ������� ����
    bool m_toggle;              //����, ������� �������������, ����������� �� ��� ������ ��� �� ������
};

