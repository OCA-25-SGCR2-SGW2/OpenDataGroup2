#pragma once
#include <string>

//通常検索を行うクラス
class Search {
private:


	//
	int count;

	std::string data[141]{
		"北海道","Hokkaido","ほっかいどう","青森県","Aomoriken ","あおもりけん","岩手県","Iwateken","いわてけん",
		"宮城県","Miyagiken","みやぎけん","秋田県","Akitaken","あきたけん","山形県","Yamagataken","やまがたけん",
		"福島県","Fukushimaken","ふくしまけん","茨城県","Ibarakiken","いばらきけん","栃木県","Tochigiken","とちぎけん",
		"群馬県","Gunmaken","ぐんまけん","埼玉県","Saitamaken","さいたまけん","千葉県","Chibaken","ちばけん",
		"東京都","Tokyoto","とうきょうと","神奈川県","Kanagawaken","かながわけん","新潟県","Niigataken","にいがたけん",
		"富山県","Toyamaken","とやまけん","石川県","Ishikawaken","いしかわけん","福井県","Fukuiken","ふくいけん",
		"山梨県","Yamanashiken","やまなしけん","長野県","Naganoken","ながのけん","岐阜県","Gifuken","ぎふけん",
		"静岡県","Shizuokaken","しずおかけん","愛知県","Aichiken","あいちけん","三重県","Mieken","みえけん",
		"滋賀県","Shigaken","しがけん","京都府","Kyotofu","きょうとふ","大阪府","Osakafu","おおさかふ",
		"兵庫県","Hyogoken","ひょうごけん","奈良県","Narakken","ならけん","和歌山県","Wakayamakken","わかやまけん",
		"鳥取県","Tottoriken","とっとりけん","島根県","Shimaneken","しまねけん","岡山県","Okayamaken","おかやまけん",
		"広島県","Hiroshimaken","ひろしまけん","山口県","Yamaguchiken","やまぐちけん","徳島県","Tokushimaken","とくしまけん",
		"香川県","Kagawaken","かがわけん","愛媛県","Ehimeken","えひめけん","高知県","Kochiken","こうちけん",
		"福岡県","Fukuokaken","ふくおかけん","佐賀県","Sagaken","さがけん","長崎県","Nagasakiken","ながさきけん",
		"熊本県","Kumamotoken","くまもとけん","大分県","Oitaken","おおいたけん","宮崎県","Miyazakiken","みやざきけん",
		"鹿児島県","Kagoshimaken","かごしまけん","沖縄県","Okinawaken","おきなわけん"
	};

	//県
	std::string prefecture[47]{
		"北海道","青森県","岩手県","宮城県","秋田県","山形県","福島県","茨城県","栃木県",
		"群馬県","埼玉県","千葉県","東京都","神奈川県","新潟県","富山県","石川県","福井県",
		"山梨県","長野県","岐阜県","静岡県","愛知県","三重県","滋賀県","京都府","大阪府",
		"兵庫県","奈良県","和歌山県","鳥取県","島根県","岡山県","広島県","山口県","徳島県",
		"香川県","愛媛県","高知県","福岡県","佐賀県","長崎県","熊本県","大分県","宮崎県",
		"鹿児島県","沖縄県"
	};



public:
	//
	bool Init();
	//
	void Updat();
	//
	void SearchiInput();
	//
	void DetailedInput(int number);

};
