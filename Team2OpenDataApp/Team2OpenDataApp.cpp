#include <windows.h>
#include <iostream>
#include <string>
#include "System.h"

int main()
{
	SetConsoleOutputCP(CP_UTF8);  // 出力コードページをUTF-8に変更
	std::u8string str = u8"こんにちは、世界";
	printUtf8(str);

	system("pause");
	return 0;
}