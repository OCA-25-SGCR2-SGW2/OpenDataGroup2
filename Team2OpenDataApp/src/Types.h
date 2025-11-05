#pragma once
//----------------------------------------------------------------------------------------
//!	@file	Types.h
//! @brief	共通で使用する型定義をまとめたヘッダーファイル
//! @author 山﨑愛
//----------------------------------------------------------------------------------------
#include <vector>
#include <unordered_map>
#include <string>
//共通で使用する型定義の名前空間
namespace domain {
	using RestaurantData = std::vector<std::unordered_map<std::string, std::u8string>>;
}// namespace domain