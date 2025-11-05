#pragma once
//----------------------------------------------------------------------------------------
//!	@file	FavoritesList.h
//! @brief	お気に入りリスト(ブックマーク)
//! @author 山﨑愛
//----------------------------------------------------------------------------------------
#include "Types.h"
class FavoritesList {
public:
	//-----------------------------------------------------------------------------
	//	お気に入りデータを追加する関数
	//! @param favorite [in] 追加したい店のデータ
	//-----------------------------------------------------------------------------
	void AddFavorite(const std::unordered_map<std::string, std::u8string>& favorite);

	//-----------------------------------------------------------------------------
	// お気に入りデータを取得する関数
	//! @return お気に入りデータ
	//-----------------------------------------------------------------------------
	domain::RestaurantData GetFavoritesData()const;

	//-----------------------------------------------------------------------------
	// お気に入りデータをすべて見せる関数
	//-----------------------------------------------------------------------------
	void ShowAllFavorites()const;

	//-----------------------------------------------------------------------------
	// お気に入りデータを削除する関数
	//! @param index [in] 削除したいデータのインデックス番号
	//! @return 成功したらtrue、失敗したらfalse
	//-----------------------------------------------------------------------------
	bool DeleteFavorite(size_t index);

	//-----------------------------------------------------------------------------
	// お気に入りリストをファイルに保存する関数
	//! @param path [in] 保存先のファイルパス（省略可能、デフォルトはFILE_PATH）
	//-----------------------------------------------------------------------------
	void Save(const std::string& path = FILE_PATH) const;

	//-----------------------------------------------------------------------------
	//	cereal用のセーブ処理用関数
	//! @param ar [in] 保存に使われるテンプレート型引数
	//-----------------------------------------------------------------------------
	template <class Archive>
	void save(Archive& ar)const {
		// 一時バッファ：u8string を string に変換して保存用に使う
		std::vector<std::unordered_map<std::string, std::string>> temp;
		temp.reserve(favorites_data_.size());

		for (const auto& map : favorites_data_) {
			std::unordered_map<std::string, std::string> converted;
			for (const auto& [key, value] : map) {
				// std::u8string → std::string に変換（UTF-8として扱う）
				converted[key] = ToString(value);
			}
			temp.emplace_back(std::move(converted));
		}
		// favorites_data_ を "favorites_data_" という名前で保存
		ar(cereal::make_nvp("favorites_data_", temp));
	}

	//-----------------------------------------------------------------------------
	//	cereal用のロード処理用関数
	//! @param ar [in] ロードに使われるテンプレート型引数
	//-----------------------------------------------------------------------------
	template <class Archive>
	void load(Archive& ar) {
		// 一時バッファ：保存時に string に変換されたデータを受け取る
		std::vector<std::unordered_map<std::string, std::string>> temp;
		ar(cereal::make_nvp("favorites_data_", temp));

		// 読み込んだデータを favorites_data_ に変換して格納
		favorites_data_.clear();
		favorites_data_.reserve(temp.size());

		for (const auto& map : temp) {
			std::unordered_map<std::string, std::u8string> converted;
			for (const auto& [key, value] : map) {
				// std::string → std::u8string に変換（UTF-8として扱う）
				converted[key] = ToU8String(value);
			}
			favorites_data_.emplace_back(std::move(converted));
		}
	}
private:
	domain::RestaurantData favorites_data_;//お気に入りのデータを格納したバッファ
public:
	static constexpr const char* FILE_PATH = "Data/FavoritesList.json";//お気に入りリストの保存先ファイルパス
};