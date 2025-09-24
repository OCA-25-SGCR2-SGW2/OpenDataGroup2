#include <windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include "System.h"
#include "DataBuffer.h"
#include "information.h"

int main()
{
	SetConsoleOutputCP(CP_UTF8);  // 出力コードページをUTF-8に変更
	std::u8string str = u8"こんにちは、世界";
	printUtf8(str);
	DataBuffer::Init();//データバッファを初期化

	ShowSearchInformation();//案内の表示

	system("pause");
	return 0;
}