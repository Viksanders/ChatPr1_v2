#pragma once
#include "SHA1.h"

class User
{
public:
    User(const std::string& login, const std::string& password) : m_login(login)    //Констуктор создания нового юзера по логину и паролю
    {
        ID = ID_count;
        ++ID_count;
        std::string password_tmp = password;        //временная строка для пароля, который будет солиться
        uint salt = static_cast<uint>(ID);
        password_tmp += std::to_string(salt);       //добавляем её к паролю
        m_hpassword = sha1_str(password_tmp);       //считаем солёный хеш
        sha1_add_salt(m_hpassword, salt);            //добавляем эту соль к хешу
        m_status = false;
        std::cout << "USER constructor " << this << " called\n";
    };
    User(const std::string& login, const std::vector<uint>& hash) : m_login(login), m_hpassword(hash)    //конструктор для добавления готового юзера
    {
        ID = ID_count;              //данный конструктор должен вызываться только при старте программы!
        ++ID_count;
        m_status = false;
        std::cout << "User " << this << " added from disk storage\n";
    }
    virtual ~User()
    {
        //delete[] m_hpassword;                 //с использованием вектора делит стал не нужен
        std::cout << "USER destructor " << this << " called\n";
    }  //зачем виртуальный? Чтобы потом класс Moderator унаследовать (но это не точно)
    std::string GetName() const { return m_login; };    //выдать имя
    std::vector<uint> GetPassword() const { return m_hpassword; };                   //выдать пароль, а теперь уже хеш (больше не используется)
    bool isPasswordCorrect(const std::string& password) const
    {
        std::string password_tmp = password;
        uint salt = sha1_pick_salt(m_hpassword);
        password_tmp += std::to_string(salt);
        std::vector<uint> hash_to_check = sha1_str(password_tmp);         //std::vector<uint> hash_to_check = sha1_str(password); добавили соль
        bool compare = two_hashes_compare(m_hpassword, hash_to_check, hash_size);
        //delete[] hash_to_check;
        return compare;
    };
    void SetPassword(const std::string& password)                    //смена пароля
    {
        //delete[] m_hpassword;             //с использованием умного указателя делит стал не нужен
        m_hpassword = sha1_str(password);
    };
    int GetID() const { return ID; };                             //Получить ID пользователя
    bool GetStatus() const { return m_status; };                  //Узнать статус пользоваетля: онлайн или оффлайн
    void SetStatus(bool status) { m_status = status; };     //Установить статус пользователя: онлайн или оффлайн
private:
    std::string m_login;        //логин - оно же имя
    //uint* m_hpassword;     //ТЕПЕРЬ ЗДЕСЬ ХЕШ ОТ ПАРОЛЯ
    std::vector<uint> m_hpassword;    //хеш от пароля теперь через vector
    static int ID_count;        //счетчик для установки ID
    int ID;                     //уникальный ID каждого пользователя
    bool m_status;              //Статус - онлайн пользователь или оффлайн
};
