#include "ChatBox.h"

ChatBox::ChatBox()
{
    active = false;     //�� ��������� ��� ���������
    m_toggle = false;   //�� ��������� ���� � ����
    std::cout << "Chat box " << this << " created\n";
}

ChatBox::ChatBox(const std::string& name)
{
    filename = name;
    active = false;     //�� ��������� ��� ���������
    m_toggle = false;   //�� ��������� ���� � ����
    std::cout << "Chat box " << this << " with name: " << filename << " created\n";
}

ChatBox::~ChatBox()
{
    std::cout << "Chat box " << this << " deleted\n";
}

void ChatBox::sendMsg(std::string& msg)
{
    m_messages.push_back(msg);
    //�������� ������ � ����
    m_file << msg << "\n";
}

void ChatBox::sendMsgFromFile(std::string& msg)
{
    m_messages.push_back(msg);
}

void ChatBox::showChatAll() const
{
    if (m_messages.size() == 0) { std::cout << "No messages here...\n"; return; }
    for (size_t i = 0; i < m_messages.size(); ++i)
    {
        std::cout << m_messages[i] << "\n";
    }
}

void ChatBox::showChatLast() const
{
    if (m_messages.size() == 0) return;
    std::cout << m_messages[m_messages.size() - 1] << "\n";
}

void ChatBox::setChatStatus(bool val)
{
    active = val;
    //���� ��������� �������� ��� �������� ���������������� �����
    if (val == false)   //���� ��� ���������� ����������, �� ��������� ��������������� ����
    {
        std::cout << "Chat " << filename << " closed!\n";
        m_file.close();
    }
    else if (m_toggle == false)
    {                   //����� ��������� ���� �� ������ � ������ �� ���� ��� �������
                        //�� ������ ���� �� �������� ������ ��� �� ������
        m_file.open(filename, std::ios::in | std::ios::out);
        if (m_file.is_open())     //���� ���� �������� - ������
        {
            std::cout << "Chat " << filename << " opened(toggle == false)!\n";
            m_file.seekg(0, std::ios_base::beg);
            while (!m_file.eof())
            {
                std::string msg;
                //m_file >> msg;                     //����� ��������� �� �����, ������� ������ ����� ������, �� �������
                //msg = m_file.get();           //������ ������ �����������
                std::getline(m_file, msg);      //��� ������ ��� ����
                sendMsgFromFile(msg);        //��������� ��������� � ��������� ������ ���������
            }
            m_file.close();
        }
        m_toggle = true;        //���������� ����
        m_file.open(filename, std::ios::in | std::ios::out | std::ios::app);    //��������� ���� �� ������
    }
    else
    {
        std::cout << "Chat " << filename << " opened(toggle == true)!\n";
        m_file.open(filename, std::ios::in | std::ios::out | std::ios::app);    //��������� ���� �� ������
    }
}

bool ChatBox::getChatStatus()
{
    return active;
}

