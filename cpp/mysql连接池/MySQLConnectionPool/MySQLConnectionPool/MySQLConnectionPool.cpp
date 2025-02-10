#include <iostream>
#include "MySQLConntion.h"

int main()
{
	MySQLConntion* mysql = new MySQLConntion();
	
	if (mysql->connect("localhost", "root", "wk3217609", "test"))
	{
		std::cout << "connected.." << std::endl;
	}

	mysql->query("select * from machine;");
	
	for (auto field : mysql->fields())
	{
		std::cout << "field=" << field << std::endl;
	}

	while (mysql->next())
	{
		int colCount = 0;
		int fieldsCount = (int)mysql->fields().size();
		for (int i = 0; i < fieldsCount; i++)
		{
			std::cout << mysql->value(colCount++) << "\t";
		}
		std::cout << std::endl;
	}
	
	while (mysql->next())
	{
		std::cout << mysql->value("MachineName") << std::endl;
	}

	mysql->startTransaction();
	bool flag1 = mysql->update("insert into machine values('16','201','test');");
	bool flag2 = mysql->update("delete from machine where NO='1';");

	if (flag1 && flag2)
	{
		mysql->commit();
	}
	else
	{
		mysql->rollback();
	}

}
