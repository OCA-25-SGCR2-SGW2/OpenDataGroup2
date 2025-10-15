#define NOMINMAX // これを定義するとwindows.hでmin,maxマクロが定義されない、std::numeric_limits<std::streamsize>::max()を使用するので、このマクロは定義しない。
#include <windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include <cereal/archives/json.hpp>       // JSON形式のアーカイブ
#include <cereal/types/string.hpp>        // string型のシリアライズをサポート
#include <cereal/types/vector.hpp>        // vector型のシリアライズをサポート
#include <cereal/types/unordered_map.hpp>   // unordered_map型のシリアライズをサポート
#include "System.h"
#include "DataBuffer.h"
#include "information.h"
#include "FilteredSearch.h"
#include "FavoritesList.h"
int main()
{
	SetConsoleOutputCP(CP_UTF8);  // 出力コードページをUTF-8に変更
	SetConsoleCP(CP_UTF8);		// 入力コードページをUTF-8に変更
	DataBuffer::Init();//データバッファを初期化
	//お気に入りリストの宣言
	FavoritesList favavorites_list;
	//お気に入りリストの読み込み
	{
		//std::ifstream is("data.json"); // 入力ファイルストリームを開く
		//cereal::JSONInputArchive archive(is); // JSON形式のアーカイブを作成
		//archive(favavorites_list); // データをデシリアライズして読み込む
	}
	while (true) {
		ShowInformation("option_info");//案内表示
		int option;
		std::cin >> option;
		while ((option > 4 || option < 1) || std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "不正な入力です。正しい値を入力してください。\n\n";
			ShowInformation("option_info");//案内表示
			std::cin >> option;
		}
		switch (option) {
		case 1:
			//検索
			break;
		case 2:
			processSearchListDisplay();//一覧表示
			break;
		case 3:
			//絞り込み検索
			processFilteredSearch();
			break;
		case 4:
			//終了
			return 0;
			break;
		}
	}
	//お気に入りリストの保存
	{
		std::ofstream os("data.json"); // ファイルに書き込む
		cereal::JSONOutputArchive archive(os);
		archive(favavorites_list); // オブジェクトを保存
	}

	system("pause");
	return 0;
}