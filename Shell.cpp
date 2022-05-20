#include "Shell.h"

int User::ID_count = 0;

Shell::Shell()
{
    m_YOU = nullptr;               //это просто чтобы варнинг убрать
    m_CHAT = nullptr;   //m_links.GetMain();
    m_active = true;
    std::cout << "Shell " << this << " created\n";
}

Shell::~Shell()
{
    std::cout << "Shell " << this << " deleted\n";
}

void Shell::close() { m_active = false; }

bool Shell::isOpened() const { return m_active; }

STATE Shell::registration()
{
    std::cout << "WELLCOME TO REGISTRATION MENU. TO GO BACK TYPE /b TO CONSOLE.\n";
    std::cout << "Enter name: ";
    std::string name;
    std::getline(std::cin, name);
    if (!m_users.IsLoginFree(name)) { std::cout << "This name is buisy!\n"; return MainMenu; }
    if (name == "/b") return MainMenu;

    std::cout << "Enter password: ";
    std::string password;
    std::getline(std::cin, password);
    if (password == "/b") return MainMenu;

    std::cout << "User " << name << " registered. Your password: " << password << "\n";
    m_users.AddUser(name, password);    //приходится передавать по значению, а не по ссылке
    m_links.AddUser();                  //добавляем пользователя в хранилище чатов и устанавливаем все взаимосвязи ЛС
    return MainMenu;
}

STATE Shell::logIn()
{
    std::cout << "WELLCOME TO LOG IN MENU. TO GO BACK TYPE /b TO CONSOLE.\n";
    std::cout << "Enter name: ";
    std::string name;
    std::getline(std::cin, name);
    if (name == "/b") return MainMenu;

    std::cout << "Enter password: ";
    std::string password;
    std::getline(std::cin, password);
    if (password == "/b") return MainMenu;

    if (!m_users.isPasswordCorrect(name, password)) { std::cout << "No such name or password!\n"; return MainMenu; } //проверка имени и пароля
    std::cout << name << " (you) has come online!\n";
    m_YOU = m_users.getUser(name);              //устанавливаем залогиненного пользователя в клиенте чата
    m_YOU->SetStatus(true);                     //меняем статус пользователю на онлайн
    m_CHAT = m_links.GetMain();                 //по умолчанию попадаем в общий чат
    m_CHAT->setChatStatus(true);                //активируем новый чат
    return Typing;
}

STATE Shell::logOut()
{
    std::cout << "Good bye!\n";     //Прощание
    if (m_YOU == nullptr) return MainMenu;
    m_YOU->SetStatus(false);        //Ставим статус пользователя на оффлайн
    m_YOU = nullptr;                //Присваиваем внутренним переменным клиента чата нулевые указатели (этого в принципе наверное можно и не делать)
    m_CHAT->setChatStatus(false);   //делаем предыдущий чат неактивным
    m_CHAT = nullptr;
    return MainMenu;
}

STATE Shell::MainMenuFcn()
{
    std::cout << "Wellcome to chat PACKET YAROVOY!\n";
    std::cout << "Type /r to register new user\n";
    std::cout << "Type /l to log in as already registered user\n";
    std::cout << "Type /lout to log out (avaliable after log in only!)\n";
    std::cout << "Type /get to see all messages from current chat (avaliable after log in only!)\n";
    std::cout << "Type /e to exit\n";

    std::string temp;
    std::getline(std::cin, temp);

    if (temp == "/e") return Exit;
    else if (temp == "/l") return LogInScreen;
    else if (temp == "/r") return Registration;

    std::cout << "No such command or command is not avaliable from main menu\n";
    return MainMenu;
}

STATE Shell::MsgOrCmd()
{
    std::cout << "Your message:";
    std::string temp;
    std::getline(std::cin, temp);

    //обработка команд
    if (temp == "/lout") return LogOutScreen;
    else if ((temp[0] == '/'))
    {
        if ((temp[1] == 's') && (temp[2] == ' '))
        {
            std::string name = temp.substr(3);
            if (m_users.IsLoginFree(name)) { std::cout << "No such user!\n"; return Typing; }
            std::cout << "Now you are writing to " << name << "\n";
            m_CHAT->setChatStatus(false);       //делаем предыдущий чат неактивным
            m_CHAT = m_links.Get(m_users.GetIDbyName(name), m_YOU->GetID());
            m_CHAT->setChatStatus(true);       //активируем новый чат
        }
        else if ((temp[1] == 'a') && (temp[2] == 'l') && (temp[3] == 'l'))
        {
            std::cout << "Now you are writing to main chat\n";
            m_CHAT->setChatStatus(false);       //делаем предыдущий чат неактивным
            m_CHAT = m_links.GetMain();
            m_CHAT->setChatStatus(true);       //активируем новый чат
        }
        else if ((temp[1] == 'g') && (temp[2] == 'e') && (temp[3] == 't'))
        {
            m_CHAT->showChatAll();
        }
        else
        {
            std::cout << "No such command! Only /lout and /s UserName are avaliable.\n";
            return Typing;
        }
    }
    else
    {
        temp = "[" + m_YOU->GetName() + "]:" + " " + temp;
        m_CHAT->sendMsg(temp);
    }
    return Typing;
}

void Shell::work()
{
    //инициализация оболочки: загрузка пользователей и создание чатов под них
    m_users.init();
    for (int i = 0; i < m_users.GetUsersNumber(); ++i)
    {
        m_links.AddUser();
    }

    STATE state = MainMenu;
    bool flag = true;

    while (flag)
    {
        switch (state)
        {
        case MainMenu:
            state = MainMenuFcn();
            break;
        case Registration:
            state = registration();
            break;
        case LogInScreen:
            state = logIn();
            break;
        case LogOutScreen:
            state = logOut();
            break;
        case Typing:
            state = MsgOrCmd();
            break;
        case Exit:
            flag = false;
            break;
        default:
            state = MainMenu;
            break;
        }
    }

}

