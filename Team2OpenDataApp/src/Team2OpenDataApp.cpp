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

	//仮で、文字列をすべて読み取って出力する。
	//{
	//	std::ifstream file("Data/restaurants.txt");
	//	if (!file) {
	//		std::cerr << "ファイルを開けませんでした。" << std::endl;
	//		return 1;
	//	}

	//	std::string line;
	//	while (std::getline(file, line)) { // 行ごとに読み取る
	//		std::cout << line << std::endl;
	//	}

	//	file.close(); // ファイルを閉じる
	//}

	system("pause");
	return 0;
}