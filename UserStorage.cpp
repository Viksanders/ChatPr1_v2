#include "UserStorage.h"

UserStorage::UserStorage()
{
    std::cout << "User storage " << this << " created\n";
}

UserStorage::~UserStorage()
{
    std::cout << "User storage " << this << " deleted\n";
}

void UserStorage::init()
{
    //��������� ���� ��� ������
    std::fstream m_file("Users.txt", ios::in | ios::out);

    if (!m_file.is_open()) std::cout << "Cannot open file\n";
    else
    {
        std::cout << "Opened\n";
        m_file.seekg(0, std::ios_base::beg);  //������ ��������� � ������

        //�������� ���������� � ������ � m_storage
        while (!m_file.eof())
        {
            std::string name;
            std::vector<uint> hash;
            hash.resize(6);

            m_file >> name;                     //����� ��� �� �����
            if (m_file.eof() == true) break;    //���������, �� ���������� �� ����

            for (int i = 0; i < 6; ++i)         //����� ��� �� ����� ��������, ������� ��� ����� � ������
            {
                m_file >> hash[i];
            }
            if (m_file.eof() == true) break;    //����� ���������, �� ���������� �� ����

            AddUserFromFile(name, hash);        //��������� ������������
        }
    }
    m_file.close();     //��������� ����
}

bool UserStorage::IsLoginFree(const std::string& name)
{
    for (std::unordered_map<std::string, std::shared_ptr<User> >::iterator it = m_storage.begin(); it != m_storage.end(); ++it)
    {
        if (it->first == name) return false;    //������ it->first � ������ ���������� ����� ���� �� ��������� it->second->GetName()
    }
    return true;
}

void UserStorage::AddUser(const std::string& name, const std::string& password)
{
    if (IsLoginFree(name))  //������������ �������� ���� ������ ������������� � ����������� ��������
    {
        m_storage.insert(std::make_pair(name, new User(name, password)));
        //m_storage.insert(std::make_pair(name, std::make_shared<User>(User(name, password))));
        //������� � ���� ��� ������������ � ��� �� ��� ������
        m_file.open("Users.txt", ios::in | ios::out | ios::app); //��������� ���� ��� ������ ����� �������������, ������ ������ � �����
        std::vector<uint> hash = m_storage.find(name)->second->GetPassword();
        m_file << name << "\t";
        for (size_t i = 0; i < hash.size(); ++i)
        {
            m_file << hash[i] << " ";
        }
        m_file << "\n";
        m_file.close();
    }
    else
    {
        std::cout << "\nAlready exists!\n";
        return;
    }
}

void UserStorage::AddUserFromFile(const std::string& name, const std::vector<uint>& hash)
{
    m_storage.insert(std::make_pair(name, new User(name, hash)));
}

int UserStorage::GetIDbyName(const std::string& name)
{
    std::unordered_map<std::string, std::shared_ptr<User> >::iterator it = m_storage.find(name);
    if (it != m_storage.end()) return it->second->GetID();
    else return -1;
}

int UserStorage::GetUsersNumber() const { return m_storage.size(); }

void UserStorage::PrintUserList()
{
    for (std::unordered_map<std::string, std::shared_ptr<User> >::iterator it = m_storage.begin(); it != m_storage.end(); ++it)
    {
        std::cout << it->first << " Online: " << it->second->GetStatus() << "\n";
    }
}

std::shared_ptr<User> UserStorage::getUser(int ID)
{
    for (std::unordered_map<std::string, std::shared_ptr<User> >::iterator it = m_storage.begin(); it != m_storage.end(); ++it)
    {
        if (it->second->GetID() == ID) return it->second;
    }
    return nullptr;
}

std::shared_ptr<User> UserStorage::getUser(const std::string& name)
{
    std::unordered_map<std::string, std::shared_ptr<User> >::iterator it = m_storage.find(name);
    if (it != m_storage.end()) return it->second;
    else return nullptr;
}

bool UserStorage::isPasswordCorrect(const std::string& name, const std::string& password)
{
    std::unordered_map<std::string, std::shared_ptr<User> >::iterator it = m_storage.find(name);
    if (it == m_storage.end()) return false; //��� ������ �����
    else if (it->second->isPasswordCorrect(password) == true) return true;   //��, ��� ����� �������� ������, �� � ���� ������� ���, ����� �� ����������, ������� ��� ������...
    else return false;
}

void UserStorage::setStatusByName(const std::string& name, const bool status)
{
    std::unordered_map<std::string, std::shared_ptr<User> >::iterator it = m_storage.find(name);
    if (it == m_storage.end()) return;
    else it->second->SetStatus(status);
}
