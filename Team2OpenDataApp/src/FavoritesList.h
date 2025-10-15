#pragma once
//----------------------------------------------------------------------------------------
//!	@file	FavoritesList.h
//! @brief	お気に入りリスト(ブックマーク)
//! @author 山﨑愛
//----------------------------------------------------------------------------------------
class FavoritesList {
public:
	//-----------------------------------------------------------------------------
	//	cereal用のシリアライズ関数
	//! @param ar [in] 保存（Output）または読み込み（Input）に使われるテンプレート型引数
	//-----------------------------------------------------------------------------
	template <class Archive>
	void serialize(Archive& ar) {
		// CEREAL_NVPは「名前付き値ペア」。JSONでキー名を保持するために使う
		ar(cereal::make_nvp("favorites_data_", favorites_data_));
	}
private:
	std::vector<std::unordered_map<std::string, std::string>> favorites_data_;//お気に入りのデータを格納したバッファ
};