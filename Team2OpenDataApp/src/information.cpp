//----------------------------------------------------------------------------------------
//!	@file	information.cpp
//! @brief	案内関数群
//! @author 山﨑愛
//----------------------------------------------------------------------------------------
#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include "System.h"
#include "information.h"
#include "DataBuffer.h"
//----------------------------------------------------------------------------------------
//	案内を表示する関数
//	オプションの案内を表示する関数
//! @param	key [in] 引き出したい案内メッセージのキー
//----------------------------------------------------------------------------------------
void ShowInformation(const std::string& key) {
	auto it = INFORMATION_MESSAGES.find(key);
	if (it != INFORMATION_MESSAGES.end()) {
		printUtf8(it->second);
	}
	else {
		//開発者向けのエラーメッセージ
		printUtf8(u8"指定されたキーは存在しません。\n");
	}
}
//----------------------------------------------------------------------------------------
//!	@brief	ステータスごとに、検索時にヒットする文字列を表示させる関数
//----------------------------------------------------------------------------------------
void ShowSearchSuggestions(std::string data_key) {
	//データバッファからrestaurantのデータを取得
	std::vector<std::unordered_map<std::string, std::u8string>> data = DataBuffer::GetRestaurantData();
	//std::setを使って、重複を排除しながら格納
	std::set<std::u8string> suggestions;
	for (const auto& entry : data) {
		auto it = entry.find(data_key);
		if (it != entry.end()) {
			suggestions.insert(it->second);
		}
	}
	//表示
	for (const auto& suggestion : suggestions) {
		printUtf8(suggestion);
	}
}
//----------------------------------------------------------------------------------------
//	検索時にヒットする文字列一覧を表示する一連の処理
//----------------------------------------------------------------------------------------
void processSearchListDisplay() {
	ShowInformation("search_list_info");//案内表示
	auto data_keys = DataBuffer::GetDataKeys();//データのキー一覧を取得
	int data_key_idx = 0;//データキーのインデックス番号
	std::cin >> data_key_idx;//番号を入力
	//入力が不正な場合、再度入力を促す
	while ((data_key_idx > data_keys.size() || data_key_idx < 1) || std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "不正な入力です。正しい値を入力してください。\n\n";
		ShowInformation("search_list_info");//案内表示
		std::cin >> data_key_idx;//番号を入力
	}
	data_key_idx--;//配列のインデックスに合わせるために-1する
	//一覧表示
	ShowSearchSuggestions(data_keys[data_key_idx]);//一覧の表示
	std::cout << std::endl;//改行
}