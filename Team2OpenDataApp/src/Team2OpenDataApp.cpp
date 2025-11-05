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
#include "PopulationData.h"
#include "PopulationAnalysis.h"
#include "information.h"
#include "FilteredSearch.h"
#include "FavoritesList.h"
#include "search.h"

int main()
{
	SetConsoleOutputCP(CP_UTF8);  // 出力コードページをUTF-8に変更
	SetConsoleCP(CP_UTF8);		  // 入力コードページをUTF-8に変更
	DataBuffer::Init();//データバッファを初期化
	PopulationData::Init();//人口データを初期化
	//お気に入りリストの宣言
	FavoritesList favorites_list;
	{
		std::ifstream is(FavoritesList::FILE_PATH); // 入力ファイルストリームを開く
		// ファイルが空なら処理を行わない
		if (!(is.peek() == std::ifstream::traits_type::eof())) {
			cereal::JSONInputArchive archive(is); // JSON形式のアーカイブを作成
			archive(favorites_list); // データをデシリアライズして読み込む
		}
	}
	Search search;//通常検索クラスのインスタンスを生成
	while (true) {
		ShowInformation("option_info");//案内表示
		int option = 0;
		// 不正入力時に再度案内を表示するコールバック
		auto callback_invalid = []() {
			ShowInformation("option_info");//案内表示
			};
		// 入力を取得（範囲は 1〜8）
		option = GetValidNum(1, 8,
			u8"不正な入力です。1から8の数字を入力してください。\n\n",
			callback_invalid);
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
			std::u8string u8_store_name = ReadLineUtf8();//店名をUTF-8で入力
			domain::RestaurantData restaurant_data = DataBuffer::GetRestaurantData();			//データバッファからrestaurantのデータを取得
			domain::RestaurantData fav_data = favorites_list.GetFavoritesData();				//お気に入りデータを取得
			bool found = false;//見つかったかどうかのフラグ
			for (const auto& entry : restaurant_data) {
				//店名が一致するしていたら
				if (entry.at("store_name") == u8_store_name) {
					found = true;//見つかったフラグを立てる
					//すでにお気に入りに登録されているか確認
					bool is_already_bookmarked = false;
					for (const auto& fav : fav_data) {
						if (fav.at("store_name") == u8_store_name) {
							std::u8string already_bookmarked_message = u8"指定された店名はすでにブックマークに登録されています。\n";
							printUtf8(already_bookmarked_message);
							found = true;
							is_already_bookmarked = true;
							break;
						}
					}
					//登録済みなら、ループを抜ける。
					if (is_already_bookmarked) {
						break;
					}
					//見つかったらお気に入りリストに追加
					favorites_list.AddFavorite(entry);
					//お気に入りリストの保存
					favorites_list.Save();
					std::u8string success_message = entry.at("store_name") + u8"をブックマークに追加しました。\n";
					printUtf8(success_message);
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
			//ブックマークの削除
		{
			while (true) {
				auto fav_data = favorites_list.GetFavoritesData();//お気に入り情報を取得
				//番号付きで表示
				size_t fav_data_size = fav_data.size();//お気に入りデータの個数
				//絞り込んだ結果を表示
				if (fav_data.empty()) {
					//該当するデータがない場合のメッセージ
					printUtf8(u8"--------------------");
					std::u8string no_results_message = u8"該当するデータが見つかりませんでした。\nブックマーク削除オプションを終了します。";
					printUtf8(no_results_message);
					printUtf8(u8"--------------------\n\n");
					break;
				}
				else {
					printUtf8(u8"--------------------");
					std::u8string results_message = u8"お気に入りは" + ToU8String(std::to_string(fav_data.size())) + u8"件あります。";
					printUtf8(results_message);
					for (const auto& entry : fav_data) {
						printUtf8(u8"--------------------\n");
						std::u8string results_message = u8"番号: " + ToU8String(std::to_string(&entry - &fav_data[0] + 1)) + u8"\n";
						printUtf8(results_message);
						for (const auto& [key, value] : entry) {
							std::u8string output = u8"" + std::u8string(key.begin(), key.end()) + u8": " + value + u8"\n";
							printUtf8(output);
						}
					}
					printUtf8(u8"--------------------\n\n");
				}
				ShowInformation("bookmark_delete_info");//案内表示
				int delete_idx = GetValidNum(
								0, static_cast<int>(fav_data_size),
								u8"無効な番号です。0から" + ToU8String(std::to_string(fav_data_size)) +
								u8"の数字を入力してください。\n終了する:0",
								[]() { ShowInformation("bookmark_delete_info"); } // 不正入力時に再表示
				);
				// 0 が入力されたら終了
				if (delete_idx == 0) {
					printUtf8(u8"--------------------");
					std::u8string exit_message = u8"0が入力されました。\nブックマーク削除オプションを終了します。";
					printUtf8(exit_message);
					printUtf8(u8"--------------------\n\n");
					break;
				}
				//対応するデータを削除
				if (favorites_list.DeleteFavorite(delete_idx - 1)) {//0は除外済み
					//お気に入りリストの保存
					favorites_list.Save();
					std::u8string success_message = u8"指定された番号のブックマークを削除しました。\n";
					printUtf8(success_message);
				}
				else {
					std::u8string failure_message = u8"指定された番号のブックマークの削除に失敗しました。\n";
					printUtf8(failure_message);
				}
				//もう一度削除するかどうかを確認
				std::u8string prompt_message = u8"別の項目も削除しますか？\n削除する:0\n終わる:1";
				printUtf8(prompt_message);
				int continue_option = GetValidNum(0, 1,
					u8"無効なオプションです。0か1を入力してください。\n削除する:0\n終わる:1");
				//1ならループを抜ける
				if (continue_option == 1) {
					break;
				}
				//0なら続行
			}
		}
		break;
		case 6:
			//ブックマークの表示
			favorites_list.ShowAllFavorites();	//お気に入りを表示
			break;
		case 7:
			//人口比率分析
			PopulationAnalysis::DisplayPopulationRatioAnalysis();
			break;
		case 8:
			//終了
			return 0;
			break;
		}
	}

	std::cout << "Press Enter to continue...";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin.get();
	return 0;
}