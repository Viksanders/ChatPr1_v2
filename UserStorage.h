#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>
#include <fstream>
#include "User.h"
#include "SHA1.h"

//��������� ������� �� ������ ��� ���-������� �� ���������� ����������� �������� (������ �������)
class UserStorage   //�� ��� ���� ����� ���� ��������� - ���������� ����� ������������� � �� ID
{                   //����� ����� �� ID ��������� � ������� ���������� ������� ��� ������� � ��, �� � ������� ������ ���� ������ � ��������� �� ����
public:
    UserStorage();
    ~UserStorage();
    void init();                //�������������: �������� ������������� �� ������
    bool IsLoginFree(const std::string& name); //���������� ���������� �������� � ���, ��� ����� ��������
    void AddUser(const std::string& name, const std::string& password);   //��������� ������ ������������ ��� �����������, �������� ���� �� �����������
    void AddUserFromFile(const std::string& name, const std::vector<uint>& hash);   //����������� ������� ������������ �� ��������� �� ������
    int GetIDbyName(const std::string& name);   //���� ������������ �� ����� � ���������� ��� ID. ���� ������ ����� ���
                                        //�� ���������� -1
    int GetUsersNumber() const;       //���������� ���������� �������������
    void PrintUserList();       //������� �� ����� ����� ���� �������������, ������ ��� ������
    std::shared_ptr<User> getUser(const int ID);      //������ ��������� �� ������������ �� ��� ID
    std::shared_ptr<User> getUser(const std::string& name);    //���������� ��� ������ �� ����� ��� ������ ����
    bool isPasswordCorrect(const std::string& name, const std::string& password);
    void setStatusByName(const std::string& name, const bool status);
private:
    //std::vector<User*> m_storage;
    std::unordered_map<std::string, std::shared_ptr<User> > m_storage;   //������ ������� �� ���-�������, � �������� ����� ������������ ���, �������� - ��������� �� �����
    std::fstream m_file;            //����, � ������� ������������ ������ � ���� ���� ������
};
