#include "MySQLConntion.h"

MySQLConntion::MySQLConntion()
{
	mysqlConn = mysql_init(mysqlConn);	//初始化连接
}

MySQLConntion::~MySQLConntion()
{
	if (mysqlConn != nullptr)
	{
		mysql_close(mysqlConn);	//关闭连接
		freeQueryResult();	//清空结果集queryResult和结果集中字段fieldNames
	}
}

bool MySQLConntion::connect(std::string host, std::string user, std::string pwd, std::string dbName, unsigned int port)
{
	mysqlConn = mysql_real_connect(mysqlConn, host.c_str(), user.c_str(), pwd.c_str(), dbName.c_str(), 
		port, nullptr, 0);	//失败返回NULL
	return mysqlConn != nullptr;	
}

bool MySQLConntion::update(std::string sqlUpdate)
{
	return mysql_query(mysqlConn, sqlUpdate.c_str()) == 0;	//修改成功返回0，否则返回非0
}

bool MySQLConntion::query(std::string sqlQuery)
{
	if (mysql_query(mysqlConn, sqlQuery.c_str()) != 0)	//查询成功返回非0
	{
		return false;
	}

	freeQueryResult();	//清空上次的查询结果和字段名
	queryResult = mysql_store_result(mysqlConn);	//从MySQL服务器把查询结果拉到客户端
	return true;
}

std::vector<std::string> MySQLConntion::fields()
{
	if (queryResult == nullptr)
	{
		return fieldNames;
	}

	std::vector<std::string>(0).swap(fieldNames);	//清空上次查询记录的字段
	int colCount = mysql_num_fields(queryResult);	//获取字段的个数
	MYSQL_FIELD* fields = mysql_fetch_fields(queryResult);	//获取字段名数组

	for (int i = 0; i < colCount; i++)
	{
		fieldNames.emplace_back(fields[i].name);	//遍历存储字段名
	}
	return fieldNames;
}

bool MySQLConntion::next()
{
	if (queryResult == nullptr)
	{
		return false;
	}

	queryResultRow = mysql_fetch_row(queryResult);	//从结果集取下一条记录
	return queryResultRow != nullptr;	//如果已经取完，返回NULL
}

std::string MySQLConntion::value(unsigned int index)
{
	if (queryResult == nullptr || queryResultRow == nullptr)
	{
		return std::string();	//返回空字符串
	}

	if (index < 0 || index >= mysql_num_fields(queryResult))
	{
		return std::string();
	}

	//防止某个字段的值包含'\0'，这样string(char*)到'\0'就会停止
	// char str[] = { '1', '2','3','4','5','\0','6','7' };
	//std::string s(str);	//12345
	//string(char*,int)遇到'\0'也不会停止，会把指定个数的char都包含
	unsigned long* colRealLengths = mysql_fetch_lengths(queryResult);	//获取该字段值的实际长度
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
