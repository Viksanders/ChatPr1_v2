#include "LinkStorage.h"

LinkStorage::LinkStorage()
{
    //m_mainPtr = new T;      //—оздаЄм тольк общий дл€ всех пользователей указатель (общий чат)
    m_mainPtr = std::make_shared<ChatBox>("ChatMain.txt");
    m_count = 0;            //ѕри создании количество пользователей равно нулю

    m_storage.resize(1);    //—оздаЄм двумерый массив 1 на 1
    m_storage[0].resize(1);

    m_storage[0][0] = nullptr;  //ћассив содержит просто один нулевой указатель, это можно было и не указывать

    std::cout << "Link storage " << this << " created\n";
}

LinkStorage::~LinkStorage()
{
    /*  //после добавлени€ умных указателей деструктор как таковой стал не нужен
    delete m_mainPtr;       //удал€ем общий объект (общий чат)
    for (size_t i = 0; i < m_storage.size(); ++i)
    {
        delete m_storage[i][i];     //”дал€ем диагональ 2д массива, т.е. удал€ем чаты с самими собой
        m_storage[i][i] = nullptr;
    }
    size_t ctr = 1;             //счетчик дл€ смещени€ диагонального элемента при переходе на новую строку
    for (size_t i = 0; i < m_storage.size() - 1; ++i)
    {
        for (size_t j = ctr; j < m_storage.size(); ++j)
        {
            delete m_storage[i][j];
            m_storage[i][j] = nullptr; //это делать не об€зательно, просто дл€ нагл€дности
            m_storage[j][i] = nullptr; //чтобы ещЄ раз напомнить, что m_storage[i][j] и m_storage[j][i] это один и тот же чат
        }
        ++ctr;                     //смещаем счетчик диагонального элемента при переходе на следующую строку
    }
    //*/
    std::cout << "Link storage " << this << " deleted\n";
}

void LinkStorage::AddUser()
{
    ++m_count;  //увеличиваем количество пользователей на единицу при добавлении нового пользоваетл€ (в чат)

    if (m_count == 1) //≈сли это первый добавленный пользователь, то создаетс€ только чат с "самим собой", т.е. «аметки
    {
        //m_storage[0][0] = new T; 
        m_storage[0][0] = std::make_shared<ChatBox>("Chat00.txt");
        return;
    }
    else
    {
        //ƒобавл€ем +1 строку и +1 столбец
        m_storage.resize(m_count);
        for (size_t i = 0; i < m_storage.size(); ++i) { m_storage[i].resize(m_count); }

        //m_storage[m_storage.size() - 1][m_storage.size() - 1] = new T;    //—оздаЄм чат с самим собой дл€ новоиспеченного пользовател€
        std::string chat_name = "Chat" + std::to_string(m_storage.size() - 1) + std::to_string(m_storage.size() - 1) + ".txt";
        m_storage[m_storage.size() - 1][m_storage.size() - 1] = std::make_shared<ChatBox>(chat_name);    //—оздаЄм чат с самим собой дл€ новоиспеченного пользовател€
        for (size_t i = 0; i < m_storage.size() - 1; ++i)     //ƒобавл€ем личные сообщени€ пользовател€ с остальными пользовател€ми
        {
            //m_storage[i][m_storage.size() - 1] = new T;       //создаЄм личный чат между пользователем A и B;
            chat_name = "Chat" + std::to_string(i) + std::to_string(m_storage.size() - 1) + ".txt";
            m_storage[i][m_storage.size() - 1] = std::make_shared<ChatBox>(chat_name);       //создаЄм личный чат между пользователем A и B;
            m_storage[m_storage.size() - 1][i] = m_storage[i][m_storage.size() - 1];    //„ат между пользователем B и A это тот же самый чат, что между A и B
        }
    }
}

void LinkStorage::PrintAddresses() const
{
    if (m_count == 0) { std::cout << "контейнер пуст\n"; return; }

    for (size_t i = 0; i < m_storage.size(); ++i)
    {
        for (size_t j = 0; j < m_storage.size(); ++j)
        {
            std::cout << m_storage[i][j] << "\t";
        }
        std::cout << "\n";
    }
}

/*
void LinkStorage::PrintData()
{
    if (m_count == 0) { std::cout << "контейнер пуст\n"; return; }

    for (size_t i = 0; i < m_storage.size(); ++i)
    {
        for (size_t j = 0; j < m_storage.size(); ++j)
        {
            std::cout << *m_storage[i][j] << "\t";
        }
        std::cout << "\n";
    }
}
*/

std::shared_ptr<ChatBox> LinkStorage::Get(int ID1, int ID2) const
{
    return m_storage[ID1][ID2];
}

std::shared_ptr<ChatBox> LinkStorage::GetMain() const
{
    return m_mainPtr;
}
