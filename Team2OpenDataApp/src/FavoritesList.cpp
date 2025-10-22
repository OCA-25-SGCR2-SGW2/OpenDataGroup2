//----------------------------------------------------------------------------------------
//!	@file	FavoritesList.cpp
//! @brief	お気に入りリスト(ブックマーク)
//! @author 山﨑愛
//----------------------------------------------------------------------------------------
#include <vector>
#include <string>
#include <unordered_map>
#include <cereal/archives/json.hpp>       // JSON形式のアーカイブ
#include <cereal/types/string.hpp>        // string型のシリアライズをサポート
#include <cereal/types/vector.hpp>        // vector型のシリアライズをサポート
#include <cereal/types/unordered_map.hpp>   // unordered_map型のシリアライズをサポート
#include "FavoritesList.h"
#include "System.h"
//-----------------------------------------------------------------------------
//!	お気に入りデータを追加する関数
//-----------------------------------------------------------------------------
void FavoritesList::AddFavorite(const std::unordered_map<std::string, std::u8string>& favorite) {
	favorites_data_.push_back(favorite);
}
//-----------------------------------------------------------------------------
//!	お気に入りデータを取得する関数
//-----------------------------------------------------------------------------
std::vector<std::unordered_map<std::string, std::u8string>> FavoritesList::GetFavoritesData() const {
	return favorites_data_;
}
//-----------------------------------------------------------------------------
//! お気に入りデータをすべて見せる関数
//-----------------------------------------------------------------------------
void FavoritesList::ShowAllFavorites()const {
	//絞り込んだ結果を表示
	if (favorites_data_.empty()) {
		//該当するデータがない場合のメッセージ
		std::u8string no_results_message = u8"該当するデータが見つかりませんでした。\n";
		printUtf8(no_results_message);
		printUtf8(u8"--------------------\n\n");
	}
	else {
		printUtf8(u8"--------------------");
		std::u8string results_message = u8"お気に入りは" + std::u8string(reinterpret_cast<const char8_t*>(std::to_string(favorites_data_.size()).c_str())) + u8"件あります。";
		printUtf8(results_message);
		for (const auto& entry : favorites_data_) {
			printUtf8(u8"--------------------\n");
			for (const auto& [key, value] : entry) {
				std::u8string output = u8"" + std::u8string(key.begin(), key.end()) + u8": " + value + u8"\n";
				printUtf8(output);
			}
		}
		printUtf8(u8"--------------------\n\n");
	}
}