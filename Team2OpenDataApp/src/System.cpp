//-----------------------------------------------------------------------------
//! @file	System.cpp
//! @brief	システム関係の関数などをまとめたファイル
//! @author	山﨑愛
//-----------------------------------------------------------------------------
#include <iostream>
#include <string>
#include "System.h"
//-----------------------------------------------------------------------------
//! @brief	UTF-8で文字列を表示する関数
//-----------------------------------------------------------------------------
void printUtf8(const std::u8string& str) {
	std::cout << ToString(str) << std::endl;
}
//-----------------------------------------------------------------------------
//! @brief	stringをu8stringに変換する関数
//-----------------------------------------------------------------------------
std::u8string ToU8String(const std::string& str) {
	return std::u8string(str.begin(), str.end());
}
//-----------------------------------------------------------------------------
//! @brief	u8stringをstringに変換する関数
//-----------------------------------------------------------------------------
std::string ToString(const std::u8string& u8str) {
	return std::string(u8str.begin(), u8str.end());
}
//-----------------------------------------------------------------------------
//! @brief	数値入力を安全に取得する関数
//-----------------------------------------------------------------------------
int GetValidNum(int min, int max, const std::u8string& error_message, const std::function<void()>& on_invalid) {
	int num;
	while (true) {
		// ユーザーからの入力を取得
		std::cin >> num;
		// 入力が有効かつ範囲内であるかをチェック
		if (!std::cin.fail() && num >= min && num <= max) {
			return num;// 有効な入力の場合、数値を返す
		}
		// 無効な場合の入力エラー処理
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		printUtf8(error_message);
		// コールバックが指定されていれば呼び出す
		if (on_invalid) {
			on_invalid();
		}
	}
}
//-----------------------------------------------------------------------------
//! @brief ユーザーから1行のUTF-8文字列入力を取得する関数
//-----------------------------------------------------------------------------
std::u8string ReadLineUtf8(const std::u8string& prompt) {
	printUtf8(prompt);
	std::string str_search_term;
	std::getline(std::cin >> std::ws, str_search_term);
	return ToU8String(str_search_term);
}