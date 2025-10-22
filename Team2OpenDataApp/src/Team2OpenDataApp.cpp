#define NOMINMAX // これを定義するとwindows.hでmin,maxマクロが定義されない、std::numeric_limits<std::streamsize>::max()を使用するので、このマクロは定義しない。
#include <windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include "System.h"
#include "DataBuffer.h"
#include "PopulationData.h"
#include "PopulationAnalysis.h"
#include "information.h"
#include "FilteredSearch.h"
#include "search.h"

int main()
{
	SetConsoleOutputCP(CP_UTF8);  // 出力コードページをUTF-8に変更
	SetConsoleCP(CP_UTF8);		// 入力コードページをUTF-8に変更
	DataBuffer::Init();//データバッファを初期化
	PopulationData::Init();//人口データを初期化
	Search search;//通常検索クラスのインスタンスを生成
	while (true) {
		ShowInformation("option_info");//案内表示
		int option;
		std::cin >> option;
		while ((option > 5 || option < 1) || std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "不正な入力です。正しい値を入力してください。\n\n";
			ShowInformation("option_info");//案内表示
			std::cin >> option;
		}
		switch (option) {
		case 1:
			//検索
			search.Updat();//通常検索の更新
			break;
		case 2:
			processSearchListDisplay();//一覧表示
			break;
		case 3:
			//絞り込み検索
			processFilteredSearch();
			break;
		case 4:
			//人口比率分析
			PopulationAnalysis::DisplayPopulationRatioAnalysis();
			break;
		case 5:
			//終了
			return 0;
			break;
		}
	}

	system("pause");
	return 0;
}