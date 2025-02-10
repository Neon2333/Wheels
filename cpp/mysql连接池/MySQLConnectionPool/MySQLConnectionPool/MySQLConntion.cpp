#include "MySQLConntion.h"

MySQLConntion::MySQLConntion()
{
	mysqlConn = mysql_init(mysqlConn);	//��ʼ������
}

MySQLConntion::~MySQLConntion()
{
	if (mysqlConn != nullptr)
	{
		mysql_close(mysqlConn);	//�ر�����
		freeQueryResult();	//��ս����queryResult�ͽ�������ֶ�fieldNames
	}
}

bool MySQLConntion::connect(std::string host, std::string user, std::string pwd, std::string dbName, unsigned int port)
{
	mysqlConn = mysql_real_connect(mysqlConn, host.c_str(), user.c_str(), pwd.c_str(), dbName.c_str(), 
		port, nullptr, 0);	//ʧ�ܷ���NULL
	return mysqlConn != nullptr;	
}

bool MySQLConntion::update(std::string sqlUpdate)
{
	return mysql_query(mysqlConn, sqlUpdate.c_str()) == 0;	//�޸ĳɹ�����0�����򷵻ط�0
}

bool MySQLConntion::query(std::string sqlQuery)
{
	if (mysql_query(mysqlConn, sqlQuery.c_str()) != 0)	//��ѯ�ɹ����ط�0
	{
		return false;
	}

	freeQueryResult();	//����ϴεĲ�ѯ������ֶ���
	queryResult = mysql_store_result(mysqlConn);	//��MySQL�������Ѳ�ѯ��������ͻ���
	return true;
}

std::vector<std::string> MySQLConntion::fields()
{
	if (queryResult == nullptr)
	{
		return fieldNames;
	}

	std::vector<std::string>(0).swap(fieldNames);	//����ϴβ�ѯ��¼���ֶ�
	int colCount = mysql_num_fields(queryResult);	//��ȡ�ֶεĸ���
	MYSQL_FIELD* fields = mysql_fetch_fields(queryResult);	//��ȡ�ֶ�������

	for (int i = 0; i < colCount; i++)
	{
		fieldNames.emplace_back(fields[i].name);	//�����洢�ֶ���
	}
	return fieldNames;
}

bool MySQLConntion::next()
{
	if (queryResult == nullptr)
	{
		return false;
	}

	queryResultRow = mysql_fetch_row(queryResult);	//�ӽ����ȡ��һ����¼
	return queryResultRow != nullptr;	//����Ѿ�ȡ�꣬����NULL
}

std::string MySQLConntion::value(unsigned int index)
{
	if (queryResult == nullptr || queryResultRow == nullptr)
	{
		return std::string();	//���ؿ��ַ���
	}

	if (index < 0 || index >= mysql_num_fields(queryResult))
	{
		return std::string();
	}

	//��ֹĳ���ֶε�ֵ����'\0'������string(char*)��'\0'�ͻ�ֹͣ
	// char str[] = { '1', '2','3','4','5','\0','6','7' };
	//std::string s(str);	//12345
	//string(char*,int)����'\0'Ҳ����ֹͣ�����ָ��������char������
	unsigned long* colRealLengths = mysql_fetch_lengths(queryResult);	//��ȡ���ֶ�ֵ��ʵ�ʳ���
	return std::string(queryResultRow[index], colRealLengths[index]);	
}

std::string MySQLConntion::value(std::string fieldName)
{
	if (queryResult == nullptr || queryResultRow == nullptr)
	{
		return std::string();
	}

	if (fieldName == "")
	{
		return std::string();
	}

	for (unsigned int i = 0; i < fieldNames.size(); i++)
	{
		if (fieldName == fieldNames[i])
		{
			return value(i);
		}
	}
	return std::string();
}

void MySQLConntion::freeQueryResult()
{
	if (queryResult != nullptr)
	{
		mysql_free_result(queryResult);
		std::vector<std::string>(0).swap(fieldNames);
	}
}

bool MySQLConntion::startTransaction()
{
	return mysql_autocommit(mysqlConn, 0) == 0;
}

bool MySQLConntion::commit()
{
	return mysql_commit(mysqlConn) == 0;
}

bool MySQLConntion::rollback()
{
	return mysql_rollback(mysqlConn) == 0;
}
