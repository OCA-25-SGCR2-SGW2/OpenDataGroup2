//----------------------------------------------------------------------------------------
//!	@file	FilteredSearch.cpp
//! @brief	絞り込み検索を行う一連の処理
//! @author 山﨑愛
//----------------------------------------------------------------------------------------
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include "System.h"
#include "information.h"
#include "DataBuffer.h"
#include "FilteredSearch.h"
//----------------------------------------------------------------------------------------
//	絞り込み検索を行う一連の処理
//----------------------------------------------------------------------------------------
void processFilteredSearch() {
	//データのバッファから絞り込むデータを取得
	domain::RestaurantData filtered_data = DataBuffer::GetRestaurantData();
	//データのキー一覧を取得
	std::vector<std::string> data_keys = DataBuffer::GetDataKeys();
	while (true)
	{
		//絞り込み検索の案内を表示
		ShowInformation("filtered_search_info");//案内表示
		//ユーザーからの入力を取得
		int option = 0;
		// 範囲を動的にメッセージに反映
		std::u8string error_message = ToU8String("無効なオプションです。1から" + std::to_string(data_keys.size()) + "の数字を入力してください。\n");
		//不正な入力があった場合のコールバック関数
		auto callback_invalid = []() {
			ShowInformation("filtered_search_info");//案内表示
			};
		option = GetValidNum(1, static_cast<int>(data_keys.size()) + 1, error_message, callback_invalid);//オプションを入力
		//ここでサイズ+1の値が入力されたらループを終了
		if (option == static_cast<int>(data_keys.size()) + 1) {
			break;
		}
		//対応するデータキーを取得
		std::string selected_key = data_keys[option - 1];
		//ユーザーに検索文字列の入力を促す
		std::u8string prompt_message = u8"検索したい文字列を入力してください:\n";
		//UTF-8文字列を入力
		std::u8string u8_search_term = ReadLineUtf8(prompt_message);
		// データを絞り込み
		filtered_data = FilterData(filtered_data, selected_key, u8_search_term);
		//絞り込んだ結果を表示
		if (filtered_data.empty()) {
			//該当するデータがない場合のメッセージ
			std::u8string no_results_message = u8"該当するデータが見つかりませんでした、絞り込み検索を終了します。\n";
			printUtf8(no_results_message);
			printUtf8(u8"--------------------\n\n");
			break;
		}
		else {
			//ヒットしたデータ数を表示
			std::u8string results_message = ToU8String(std::to_string(filtered_data.size())) + u8"件のデータがヒットしました。\n";
			printUtf8(results_message);
			//データの表示
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
//----------------------------------------------------------------------------------------
//! データを絞り込む関数
//----------------------------------------------------------------------------------------
domain::RestaurantData FilterData(const domain::RestaurantData& data, const std::string& key, const std::u8string& term) {
	domain::RestaurantData result;
	std::copy_if(data.begin(), data.end(), std::back_inserter(result),
		[&](const auto& entry) {
			auto it = entry.find(key);
			return it != entry.end() && it->second.find(term) != std::u8string::npos;
		});
	return result;
}