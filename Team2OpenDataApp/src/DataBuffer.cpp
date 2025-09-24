//-----------------------------------------------------------------------------
//! @file	DataBuffer.cpp
//! @brief	データのバッファクラス、複数のファイルでデータを使用したいので、staticクラスにします。
//! @author	山﨑愛
//-----------------------------------------------------------------------------
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "DataBuffer.h"
std::vector<RestaurantData> restrant_data_ = {};//staticなのでここで初期化
//-----------------------------------------------------------------------------
//	初期化関数
//-----------------------------------------------------------------------------
void DataBuffer::Init() {
	std::ifstream file("Data/restaurants.txt");//ファイルストリームを宣言して、ファイルを開く。
	if (!file) {
		std::cerr << "ファイルを開けませんでした。" << std::endl;
	}

	std::string line;
	while (std::getline(file, line)) { // 行ごとに読み取る
		std::stringstream sstr(line);//カンマ区切りなので、sstrを宣言
		int loop_count = 0;//カラムを追跡するためのカウンタ
		std::string item;//ラインの内容を格納する
		RestaurantData curr_line_data;//このラインのデータを格納する一時変数
		//sstrをカンマごとに読み取り
		while (std::getline(sstr, item, ',')) {
			loop_count++;//ループ回数をカウントする。
			//カウントごとに
			switch (loop_count) {
			case 1://店舗名
				curr_line_data.store_name = std::u8string(item.begin(), item.end());//店舗名
				break;
			case 4:
				curr_line_data.prefecture = std::u8string(item.begin(), item.end());//県
				break;
			case 5:
				curr_line_data.city = std::u8string(item.begin(), item.end());//市区町村
				break;
			case 6:
				curr_line_data.street = std::u8string(item.begin(), item.end());//番地
				break;
			case 7:
				curr_line_data.building = std::u8string(item.begin(), item.end());//建物名
				break;
			case 8:
				curr_line_data.station = std::u8string(item.begin(), item.end());//駅名
				break;
			case 9:
				curr_line_data.phone_number = std::u8string(item.begin(), item.end());//電話番号
				break;
			case 10:
				curr_line_data.genre = std::u8string(item.begin(), item.end());//ジャンル
				break;
			case 15:
				curr_line_data.url = std::u8string(item.begin(), item.end());//URL
				break;
			}
		}
		restrant_data_.push_back(curr_line_data);//バッファに格納
	}

	file.close(); // ファイルを閉じる
}