# 🍣レストランアプリ🍴

簡単なCLI操作お気に入りデータを管理・保存できる C++ アプリケーションです。UTF-8 文字列対応、JSON形式でのデータ保存を内部で行います。

---

## 📸 こんな感じのアプリ✨


---

## ✨ 主な機能

- お気に入りデータの登録・編集・削除
- UTF-8 文字列の安全な表示
- cereal ライブラリを使った JSON シリアライズ／デシリアライズ
- コマンドラインベースの簡易 UI
![アプリのスクリーンショット](images/screenshot.png)
---

## 🚀 インストール方法

### 🔧 必要環境

- C++20 対応のコンパイラ（例：g++, clang++, MSVC）
- CMake（任意）
- cereal ライブラリ（ヘッダオンリー）

### 📦 セットアップ手順

```bash
# リポジトリをクローン
git clone https://github.com/yourname/Team2OpenDataApp.git
cd Team2OpenDataApp

# ビルド（CMakeを使う場合）
mkdir build && cd build
cmake ..
make

# 実行
./Team2OpenDataApp