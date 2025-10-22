//-----------------------------------------------------------------------------
//! @file	PopulationAnalysis.cpp
//! @brief	都道府県別検索結果と人口比率の分析クラスの実装
//! @author	AI Assistant
//-----------------------------------------------------------------------------
#include "PopulationAnalysis.h"
#include "DataBuffer.h"
#include "PopulationData.h"
#include "System.h"
#include <iostream>
#include <algorithm>
#include <iomanip>

//-----------------------------------------------------------------------------
//	都道府県別の検索結果数を集計する関数
//-----------------------------------------------------------------------------
std::unordered_map<std::u8string, int> PopulationAnalysis::CountResultsByPrefecture() {
	std::unordered_map<std::u8string, int> prefecture_counts;
	
	// DataBufferからレストランデータを取得
	auto restaurant_data = DataBuffer::GetRestaurantData();
	
	// 都道府県ごとにカウント
	for (const auto& entry : restaurant_data) {
		auto it = entry.find("prefecture");
		if (it != entry.end()) {
			prefecture_counts[it->second]++;
		}
	}
	
	return prefecture_counts;
}

//-----------------------------------------------------------------------------
//	都道府県別の人口比率（10万人あたり）を計算して表示する関数
//-----------------------------------------------------------------------------
void PopulationAnalysis::DisplayPopulationRatioAnalysis() {
	printUtf8(u8"==================== 都道府県別検索結果数と人口比率分析 ====================\n\n");
	
	auto sorted_data = GetSortedByRatio();
	
	if (sorted_data.empty()) {
		printUtf8(u8"データがありません。\n");
		return;
	}
	
	// ヘッダー表示
	printUtf8(u8"都道府県");
	std::cout << std::setw(20) << "検索結果数";
	std::cout << std::setw(15) << "人口";
	std::cout << std::setw(20) << "10万人あたり" << std::endl;
	printUtf8(u8"--------------------------------------------------------------------------\n");
	
	// データ表示
	for (const auto& [prefecture, count, population, ratio] : sorted_data) {
		printUtf8(prefecture);
		std::cout << std::setw(20 - 8) << count; // UTF-8文字分調整
		std::cout << std::setw(15) << population;
		std::cout << std::setw(20) << std::fixed << std::setprecision(2) << ratio << std::endl;
	}
	
	printUtf8(u8"\n==========================================================================\n\n");
}

//-----------------------------------------------------------------------------
//	人口比率順にソートされた都道府県リストを取得
//-----------------------------------------------------------------------------
std::vector<std::tuple<std::u8string, int, int, double>> PopulationAnalysis::GetSortedByRatio() {
	std::vector<std::tuple<std::u8string, int, int, double>> result;
	
	// 都道府県別の検索結果数を取得
	auto prefecture_counts = CountResultsByPrefecture();
	
	// 人口データと結合して比率を計算
	for (const auto& [prefecture, count] : prefecture_counts) {
		int population = PopulationData::GetPopulation(prefecture);
		if (population > 0) {
			double ratio = PopulationData::CalculateRatioPerPopulation(count, prefecture);
			result.push_back(std::make_tuple(prefecture, count, population, ratio));
		}
	}
	
	// 比率の降順でソート
	std::sort(result.begin(), result.end(),
		[](const auto& a, const auto& b) {
			return std::get<3>(a) > std::get<3>(b);
		}
	);
	
	return result;
}