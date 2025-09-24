#pragma once
//-----------------------------------------------------------------------------
//! @file	DataBuffer.h
//! @brief	データのバッファクラス、複数のファイルでデータを使用したいので、staticクラスにします。
//! @author	山﨑愛
//-----------------------------------------------------------------------------
#include <vector>
//-----------------------------------------------------------------------------
//	レストランのデータが入った構造体
//-----------------------------------------------------------------------------
struct RestaurantData {
	std::u8string store_name = u8"情報なし";		//店舗名
	std::u8string prefecture = u8"情報なし";		//県
	std::u8string city = u8"情報なし";			//市区町村
	std::u8string street = u8"情報なし";			//番地
	std::u8string building = u8"情報なし";		//建物名
	std::u8string station = u8"情報なし";		//駅名
	std::u8string genre = u8"情報なし";			//ジャンル
	std::u8string phone_number = u8"情報なし";	//電話番号
	std::u8string url = u8"情報なし";			//URL
};
//-----------------------------------------------------------------------------
//	データのバッファクラス
//-----------------------------------------------------------------------------
class DataBuffer {
public:
	static void Init();//初期化関数
private:
	static std::vector<RestaurantData> restaurant__data_;//restaurantのデータを格納したバッファ
};