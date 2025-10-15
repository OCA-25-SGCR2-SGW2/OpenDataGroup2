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