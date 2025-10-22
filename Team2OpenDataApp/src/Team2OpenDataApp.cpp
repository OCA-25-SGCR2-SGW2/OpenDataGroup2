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
#include "search.h"

int main()
{
	SetConsoleOutputCP(CP_UTF8);  // 出力コードページをUTF-8に変更
	SetConsoleCP(CP_UTF8);		  // 入力コードページをUTF-8に変更
	DataBuffer::Init();//データバッファを初期化
	//お気に入りリストの宣言
	FavoritesList favavorites_list;
	{
		std::ifstream is("Data/FavoritesList.json"); // 入力ファイルストリームを開く
		// ファイルが空なら処理を行わない
		if (!(is.peek() == std::ifstream::traits_type::eof())) {
			cereal::JSONInputArchive archive(is); // JSON形式のアーカイブを作成
			archive(favavorites_list); // データをデシリアライズして読み込む
		}
	}
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
			//店名でブックマーク
		{
			ShowInformation("bookmark_input_info");//案内表示
			std::string str_store_name;
			std::cin >> str_store_name;
			//UTF-8文字列に変換
			std::u8string u8_store_name(reinterpret_cast<const char8_t*>(str_store_name.c_str()));
			//データバッファからrestaurantのデータを取得
			std::vector<std::unordered_map<std::string, std::u8string>> data = DataBuffer::GetRestaurantData();
			bool found = false;//見つかったかどうかのフラグ
			for (const auto& entry : data) {
				if (entry.at("store_name") == u8_store_name) {
					//見つかったらお気に入りリストに追加
					favavorites_list.AddFavorite(entry);
					//お気に入りリストの保存
					{
						std::ofstream os("Data/FavoritesList.json"); // ファイルに書き込む
						cereal::JSONOutputArchive archive(os);
						archive(favavorites_list); // オブジェクトを保存
					}
					std::u8string success_message = entry.at("store_name") + u8"をブックマークに追加しました。\n";
					printUtf8(success_message);
					found = true;
					break;
				}
			}
			if (!found) {
				std::u8string not_found_message = u8"指定された店名は見つかりませんでした。\n";
				printUtf8(not_found_message);
			}
		}
		break;
		case 5:
			//ブックマークの表示
			favavorites_list.ShowAllFavorites();	//お気に入りを表示
			break;
		case 6:
			//終了
			return 0;
			break;
		}
	}

	system("pause");
	return 0;
}