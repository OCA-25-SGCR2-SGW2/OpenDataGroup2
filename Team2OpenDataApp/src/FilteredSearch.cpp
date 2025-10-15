//----------------------------------------------------------------------------------------
//!	@file	FilteredSearch.cpp
//! @brief	絞り込み検索を行う一連の処理
//! @author 山﨑愛
//----------------------------------------------------------------------------------------
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include "System.h"
#include "information.h"
#include "DataBuffer.h"
//----------------------------------------------------------------------------------------
//	絞り込み検索を行う一連の処理
//----------------------------------------------------------------------------------------
void processFilteredSearch() {
	//データのバッファから絞り込むデータを取得
	std::vector<std::unordered_map<std::string, std::u8string>> filtered_data = DataBuffer::GetRestaurantData();
	//データのキー一覧を取得
	std::vector<std::string> data_keys = DataBuffer::GetDataKeys();
	while (true)
	{
		//絞り込み検索の案内を表示
		ShowFilteredSearchInformation();
		//ユーザーからの入力を取得
		int option = 0;
		std::cin >> option;
		//ここで10が入力されたらループを終了
		if (option == 10) {
			break;
		}
		//例外処理
		if (option < 1 || option > 9) {
			std::u8string error_message = u8"無効なオプションです。1から9の数字を入力してください。\n";
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			printUtf8(error_message);
			printUtf8(u8"--------------------\n\n");
			return;
		}
		//対応するデータキーを取得
		std::string selected_key = data_keys[option - 1];
		//ユーザーに検索文字列の入力を促す
		std::u8string prompt_message = u8"検索したい文字列を入力してください:\n";
		printUtf8(prompt_message);
		std::string str_search_term;
		std::cin >> str_search_term;
		//UTF-8文字列に変換
		std::u8string u8_search_term(reinterpret_cast<const char8_t*>(str_search_term.c_str()));
		//削除を行うので、逆順イテレータ
		for (int i = static_cast<int>(filtered_data.size()) - 1; i >= 0; --i) {
			//文字列が一致するかを検索して
			if (filtered_data[i][selected_key].find(u8_search_term) == std::u8string::npos) {
				//なければ削除
				filtered_data.erase(filtered_data.begin() + i);
			}
		}
		//絞り込んだ結果を表示
		if (filtered_data.empty()) {
			//該当するデータがない場合のメッセージ
			std::u8string no_results_message = u8"該当するデータが見つかりませんでした、絞り込み検索を終了します。\n";
			printUtf8(no_results_message);
			printUtf8(u8"--------------------\n\n");
			break;
		}
		else {
			std::u8string results_message = std::u8string(reinterpret_cast<const char8_t*>(std::to_string(filtered_data.size()).c_str())) + u8"件のデータがヒットしました。\n";
			for (const auto& entry : filtered_data) {
				printUtf8(u8"--------------------\n");
				for (const auto& [key, value] : entry) {
					std::u8string output = u8"" + std::u8string(key.begin(), key.end()) + u8": " + value + u8"\n";
					printUtf8(output);
				}
			}
			printUtf8(u8"--------------------\n\n");
		}
	}

}