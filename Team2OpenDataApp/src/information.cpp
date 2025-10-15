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
//	オプションの案内を表示する関数
//----------------------------------------------------------------------------------------
void ShowOptionInformation() {
	std::u8string infomation = u8"オプションを選択してください\n1:検索\n2:一覧表示\n3:絞り込み検索\n4:終了\n";//オプションの案内メッセージ(仮)
	printUtf8(infomation);
}
//----------------------------------------------------------------------------------------
//	検索文字列の一覧表示の案内を表示する関数
//----------------------------------------------------------------------------------------
void ShowSearchListInformation() {
	std::u8string infomation = u8"どの一覧を表示しますか:\n1:店名\n2:都道府県\n3:都市名\n4:番地\n5:建物名\n6:駅名\n7:電話番号\n8:飲食のジャンル\n9:サイトのURL";//オプションの案内メッセージ(仮)
	printUtf8(infomation);
}
//----------------------------------------------------------------------------------------
//! @brief	検索の案内を表示する関数
//----------------------------------------------------------------------------------------
void ShowSearchInformation() {
	std::u8string infomation = u8"検索オプションを選択してください\n1:都道府県\n2:地域\n3:ジャンル\n4:駅\n";//案内メッセージ(仮)
	printUtf8(infomation);
}
//----------------------------------------------------------------------------------------
//	絞り込み検索の案内を表示する関数
//----------------------------------------------------------------------------------------
void ShowFilteredSearchInformation() {
	std::u8string infomation = u8"絞り込み検索オプションを選択してください\n1:店名\n2:都道府県\n3:都市名\n4:番地\n5:建物名\n6:駅名\n7:電話番号\n8:飲食のジャンル\n9:サイトのURL\n10:終了";//案内メッセージ(仮)
	printUtf8(infomation);
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
	ShowSearchListInformation();//案内表示
	auto data_keys = DataBuffer::GetDataKeys();//データのキー一覧を取得
	int data_key_idx = 0;//データキーのインデックス番号
	std::cin >> data_key_idx;//番号を入力
	//入力が不正な場合、再度入力を促す
	while ((data_key_idx > data_keys.size() || data_key_idx < 1) || std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "不正な入力です。正しい値を入力してください。\n\n";
		ShowSearchListInformation();//案内表示
		std::cin >> data_key_idx;//番号を入力
	}
	data_key_idx--;//配列のインデックスに合わせるために-1する
	//一覧表示
	ShowSearchSuggestions(data_keys[data_key_idx]);//一覧の表示
	std::cout << std::endl;//改行
}