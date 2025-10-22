#pragma once
//----------------------------------------------------------------------------------------
//!	@file	FavoritesList.h
//! @brief	お気に入りリスト(ブックマーク)
//! @author 山﨑愛
//----------------------------------------------------------------------------------------
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
	std::vector<std::unordered_map<std::string, std::u8string>> GetFavoritesData()const;

	//-----------------------------------------------------------------------------
	// お気に入りデータをすべて見せる関数
	//-----------------------------------------------------------------------------
	void ShowAllFavorites()const;

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
				converted[key] = std::string(reinterpret_cast<const char*>(value.c_str()));
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
				converted[key] = std::u8string(reinterpret_cast<const char8_t*>(value.c_str()));
			}
			favorites_data_.emplace_back(std::move(converted));
		}
	}
private:
	std::vector<std::unordered_map<std::string, std::u8string>> favorites_data_;//お気に入りのデータを格納したバッファ
};