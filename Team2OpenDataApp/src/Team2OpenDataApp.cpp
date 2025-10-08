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
	DataBuffer::Init();//データバッファを初期化
	while (true) {
		ShowOptionInformation();//オプションの案内表示
		int option;
		std::cin >> option;
		switch (option) {
		case 1:
			//検索
			break;
		case 2:
			processSearchListDisplay();//一覧表示
			break;
		case 3:
			//終了
			return 0;
			break;
		}
	}

	system("pause");
	return 0;
}