/*
Windows+VS环境下导入库方法：
属性->VC++->包含目录：MySQL-include，库目录：MySQL-lib
链接器->输入->附加依赖项：依赖的外部库的名称：libmysql.lib
*/

#pragma once
#include <iostream>
#include <mysql.h>
#include <vector>

class MySQLConntion
{
public:
	/// <summary>
	/// 初始化连接
	/// </summary>
	MySQLConntion();
	//断开连接
	~MySQLConntion();
	/// <summary>
	/// 连接服务器
	/// </summary>
	/// <param name="host">主机</param>
	/// <param name="user">用户名</param>
	/// <param name="pwd">密码</param>
	/// <param name="dbName">数据库名</param>
	/// <param name="port">端口(default=3306)</param>
	/// <returns></returns>
	bool connect(std::string host, std::string user, std::string pwd, std::string dbName, unsigned int port = 3306);
	/// <summary>
	/// 更新数据库：insert、delete、update
	/// </summary>
	/// <param name="sqlUpdate">增删改sql语句</param>
	/// <returns></returns>
	bool update(std::string sqlUpdate);
	/// <summary>
	/// 查询数据库
	/// </summary>
	/// <param name="sqlQuery">查询sql语句</param>
	/// <returns></returns>
	bool query(std::string sqlQuery);
	/// <summary>
	/// 查看所有字段名
	/// </summary>
	/// <returns></returns>
	std::vector<std::string> fields();
	/// <summary>
	/// 遍历查询数据集，指向下一条记录
	/// </summary>
	/// <returns></returns>
	bool next();
	/// <summary>
	/// 通过字段的index获取值
	/// </summary>
	/// <param name="index"></param>
	/// <returns></returns>
	std::string value(unsigned int index);
	/// <summary>
	/// 通过字段名获取字段值
	/// </summary>
	/// <param name="fieldName"></param>
	/// <returns></returns>
	std::string value(std::string fieldName);
	/// <summary>
	/// 开启事务操作，设置成手动提交、创建保存点
	/// </summary>
	/// <returns></returns>
	bool startTransaction();
	/// <summary>
	/// 事务提交
	/// </summary>
	/// <returns></returns>
	bool commit();
	/// <summary>
	/// 事务回滚
	/// </summary>
	/// <returns></returns>
	bool rollback();
private:
	/// <summary>
	/// 清空上一次查询结果
	/// </summary>
	void freeQueryResult();

	MYSQL* mysqlConn = nullptr;	//MySQL连接
	MYSQL_RES* queryResult = nullptr;	//查询结果集
	std::vector<std::string> fieldNames;	//当前结果集的所有字段名
	MYSQL_ROW queryResultRow = nullptr;	//当前查询记录
};

