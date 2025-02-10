/*
Windows+VS�����µ���ⷽ����
����->VC++->����Ŀ¼��MySQL-include����Ŀ¼��MySQL-lib
������->����->����������������ⲿ������ƣ�libmysql.lib
*/

#pragma once
#include <iostream>
#include <mysql.h>
#include <vector>

class MySQLConntion
{
public:
	/// <summary>
	/// ��ʼ������
	/// </summary>
	MySQLConntion();
	//�Ͽ�����
	~MySQLConntion();
	/// <summary>
	/// ���ӷ�����
	/// </summary>
	/// <param name="host">����</param>
	/// <param name="user">�û���</param>
	/// <param name="pwd">����</param>
	/// <param name="dbName">���ݿ���</param>
	/// <param name="port">�˿�(default=3306)</param>
	/// <returns></returns>
	bool connect(std::string host, std::string user, std::string pwd, std::string dbName, unsigned int port = 3306);
	/// <summary>
	/// �������ݿ⣺insert��delete��update
	/// </summary>
	/// <param name="sqlUpdate">��ɾ��sql���</param>
	/// <returns></returns>
	bool update(std::string sqlUpdate);
	/// <summary>
	/// ��ѯ���ݿ�
	/// </summary>
	/// <param name="sqlQuery">��ѯsql���</param>
	/// <returns></returns>
	bool query(std::string sqlQuery);
	/// <summary>
	/// �鿴�����ֶ���
	/// </summary>
	/// <returns></returns>
	std::vector<std::string> fields();
	/// <summary>
	/// ������ѯ���ݼ���ָ����һ����¼
	/// </summary>
	/// <returns></returns>
	bool next();
	/// <summary>
	/// ͨ���ֶε�index��ȡֵ
	/// </summary>
	/// <param name="index"></param>
	/// <returns></returns>
	std::string value(unsigned int index);
	/// <summary>
	/// ͨ���ֶ�����ȡ�ֶ�ֵ
	/// </summary>
	/// <param name="fieldName"></param>
	/// <returns></returns>
	std::string value(std::string fieldName);
	/// <summary>
	/// ����������������ó��ֶ��ύ�����������
	/// </summary>
	/// <returns></returns>
	bool startTransaction();
	/// <summary>
	/// �����ύ
	/// </summary>
	/// <returns></returns>
	bool commit();
	/// <summary>
	/// ����ع�
	/// </summary>
	/// <returns></returns>
	bool rollback();
private:
	/// <summary>
	/// �����һ�β�ѯ���
	/// </summary>
	void freeQueryResult();

	MYSQL* mysqlConn = nullptr;	//MySQL����
	MYSQL_RES* queryResult = nullptr;	//��ѯ�����
	std::vector<std::string> fieldNames;	//��ǰ������������ֶ���
	MYSQL_ROW queryResultRow = nullptr;	//��ǰ��ѯ��¼
};

