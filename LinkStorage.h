#pragma once
#include "ChatBox.h"
#include <memory>

class LinkStorage
{
public:
    LinkStorage();    //Конструкторы копирования, перемещения и прочее не реализуем, т.к. "хранилище взаимосвязей" предполагается только одно на всю программу
    ~LinkStorage();   //В деструктре удаляем динамически созданные данные
    void AddUser();             //Добавить новый элемент
    std::shared_ptr<ChatBox> Get(int ID1, int ID2) const;
    std::shared_ptr<ChatBox> GetMain() const;
    void PrintAddresses() const;      //Вывести на экран адреса указателей, записанные в каждой ячейке массива ТОЛЬКО ДЛЯ ОТЛАДКИ
    //void PrintData();           //Вевести данные по указателю из каждой ячейки ТОЛЬКО ДЛЯ ОТЛАДКИ
private:
    //std::vector<std::vector<T*> > m_storage;   //двумерный массив, основанный на классе вектор для хранения указателей на пользовательские чаты
    //T* m_mainPtr;                              //указатель на основной объект (в случае чата - на общий чат)
    std::vector<std::vector<std::shared_ptr<ChatBox> > > m_storage;
    std::shared_ptr<ChatBox> m_mainPtr;
    int m_count;                                //число пользователей
};


/*  //Класс для теста LinkStorage
struct staticInt
{
    static int i;
    int x = 0;
    staticInt() { x = i;  ++i; }
    friend std::ostream& operator<<(std::ostream& output, const staticInt& v);
};
int staticInt::i = 0;
std::ostream& operator<<(std::ostream& output, const staticInt& v)
{
    output << v.x;
    return output;
}
//*/
