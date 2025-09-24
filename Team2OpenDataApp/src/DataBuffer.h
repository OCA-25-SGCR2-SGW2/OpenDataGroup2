#pragma once
//-----------------------------------------------------------------------------
//! @file	DataBuffer.h
//! @brief	データのバッファクラス、複数のファイルでデータを使用したいので、staticクラスにします。
//! @author	山﨑愛
//-----------------------------------------------------------------------------
#include <vector>
#include <unordered_map>
//-----------------------------------------------------------------------------
//	データのバッファクラス
//-----------------------------------------------------------------------------
class DataBuffer {
public:
	static void Init();//初期化関数
	//-----------------------------------------------------------------------------
	//!	@brief	レストランデータを取得する関数
	//! @return	restaurantのデータを格納したバッファ
	//-----------------------------------------------------------------------------
	static std::vector<std::unordered_map<std::string, std::u8string>> GetRestaurantData() { return restaurant__data_; };
private:
	static std::vector<std::unordered_map<std::string, std::u8string>> restaurant__data_;//restaurantのデータを格納したバッファ
};