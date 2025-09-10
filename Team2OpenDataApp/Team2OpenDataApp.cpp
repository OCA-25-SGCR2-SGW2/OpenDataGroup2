#include <windows.h>
#include <iostream>
#include <string>

int main()
{
	SetConsoleOutputCP(CP_UTF8);  // 出力コードページをUTF-8に変更
	std::u8string str = u8"こんにちは、世界";
	std::cout << reinterpret_cast<const char*>(str.c_str()) << std::endl;

	system("pause");
	return 0;
}