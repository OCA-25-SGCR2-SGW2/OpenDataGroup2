//	mainで打たれた都道府県名を引っ張ってくる
//　データが入っている関数からデータを引っ張ってくる
//　両方のデータを比較する
//　一致すれば出す
#include "Search.h"
#include <iostream>
#include <string>
#include <vector>
#include "DataBuffer.h"
#include "System.h"
#include <set>
using namespace std;

bool Search::Init() {
	count = 0;
	with_data = false;
	str_search_term = "";


	return true;
}
std::string ToString(const std::u8string& u8str) {
	return std::string(u8str.begin(), u8str.end());
}
void Search::Updat() {


	auto data_keys = DataBuffer::GetDataKeys();

	int search_number = 0;//検索内容番号を入れる
	SearchiInput();
	cout << endl;
	std::cin >> search_number;//番号を入力
	while (search_number > data_keys.size()) {
		std::cout << "不正な入力です。正しい値を入力してください。\n\n";
		SearchiInput();//案内表示
		std::cin >> search_number;//番号を入力
	}

	DetailedInput(search_number);//細かい事をきく 

}



void Search::SearchiInput()	//検索内容を入力させる
{
	cout << "検索したい番号を入力してください:\n1:店名\n2:都道府県\n3:都市名\n4:番地\n5:建物名\n6:駅名\n7:電話番号\n8:飲食のジャンル\n9:サイトのURL";
	cout << endl;

}

void Search::DetailedInput(int number)//検索内容を聞いた後に細かい事をきく 
{
	std::vector<std::unordered_map<std::string, std::u8string>> filtered_data = DataBuffer::GetRestaurantData();
	std::vector<std::string> data_keys = DataBuffer::GetDataKeys();
	std::string search[9]{
		"店名","都道府県","都市名","番地","建物名","駅名","電話番号","飲食のジャンル","サイトのURL\n"
	};

	//対応するデータキーを取得
	std::string selected_key = data_keys[number - 1];
	//ユーザーに検索文字列の入力を促す

	
	
	Character_Classification(number);
	while (!with_data)
	{
		std::cout << "不正な入力です。正しい値を入力してください。\n";
		Character_Classification(number);
	}


	//std::cin >> str_search_term;
	//UTF-8文字列に変換
	std::u8string u8_search_term(reinterpret_cast<const char8_t*>(str_search_term.c_str()));
	//削除を行うので、逆順イテレータ
	for (int i = static_cast<int>(filtered_data.size()) - 1; i >= 0; --i) {
		//文字列が一致するかを検索して
		if (filtered_data[i][selected_key].find(u8_search_term) == std::u8string::npos) {
			//なければ削除
			filtered_data.erase(filtered_data.begin() + i);
		}
	}
	//絞り込んだ結果を表示
	if (filtered_data.empty()) {
		//該当するデータがない場合のメッセージ
		std::u8string no_results_message = u8"該当するデータが見つかりませんでした、絞り込み検索を終了します。\n";
		printUtf8(no_results_message);
		printUtf8(u8"--------------------\n\n");

	}
	else {
		std::u8string results_message = std::u8string(reinterpret_cast<const char8_t*>(std::to_string(filtered_data.size()).c_str())) + u8"件のデータがヒットしました。\n";
		for (const auto& entry : filtered_data) {
			printUtf8(u8"--------------------\n");
			for (const auto& [key, value] : entry) {
				std::u8string output = u8"" + std::u8string(key.begin(), key.end()) + u8": " + value + u8"\n";
				printUtf8(output);
			}
		}
		printUtf8(u8"--------------------\n\n");
	}
}

void Search::Character_Classification(int number)
{
	if (number == 2)
	{
		std::cout << "漢字またはひらがなまたはカタカナで入力してください。(例：大阪府) \n\n";
		std::string str;
		std::cin >> str;

		for (int i = 0; i < 141; i++)
		{
			if (str == data[i])
			{
				int a = i / 3;
				str_search_term = prefecture[a];
				with_data = true;
				return;
			}
			else {
				with_data = false;
			}
		}
	}
	else {
		std::u8string prompt_message = u8"検索したい文字列を入力してください:\n";
		printUtf8(prompt_message);
		std::cin >> str_search_term;
		with_data = true;
	}
}
