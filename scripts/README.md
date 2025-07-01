# スクリプトディレクトリ

このディレクトリには、C言語学習教材の管理・生成用スクリプトが格納されています。

## 主要なスクリプト

### 1. 教材管理スクリプト

#### update_chapter_readmes.py
- **用途**: `docs/main_textbook.md`の内容を各章の`src/*/README.md`に反映
- **使用方法**: `python3 scripts/update_chapter_readmes.py`
- **説明**: main_textbook.mdを更新した後、その内容を各章のREADME.mdに分割して反映させます

#### generate_main_textbook.py
- **用途**: 各章の`src/*/README.md`から`docs/main_textbook.md`を生成
- **使用方法**: `python3 scripts/generate_main_textbook.py`
- **説明**: 各章のREADME.mdとexamplesディレクトリのサンプルコードから統合されたmain_textbook.mdを生成します
- **出力**: `docs/main_textbook_generated.md`として保存（確認後にリネーム）

### 2. Word文書生成スクリプト

#### create_main_textbook.sh
- **用途**: メインテキストのWord文書を生成
- **出力**: `output/word/C言語プログラミング教材_メインテキスト.docx`

#### create_exercises.sh
- **用途**: 演習問題集のWord文書を生成
- **出力**: `output/word/C言語プログラミング教材_演習問題集.docx`

#### create_word_simple.sh / create_word_clean.sh / create_word_filtered.sh
- **用途**: 異なるフォーマットオプションでWord文書を生成

### 3. PDF生成スクリプト

#### create_pdf.sh
- **用途**: HTML経由でPDF文書を生成
- **要件**: Chrome/Chromiumがインストールされていること
- **出力**: `output/pdf/`ディレクトリ

### 4. その他のユーティリティ

#### combine_chapters.sh
- **用途**: 複数の章を結合して単一のドキュメントを作成

#### run_cppcheck.sh
- **用途**: C言語のサンプルコードに対して静的解析を実行

## 使用フロー

### ケース1: main_textbook.mdを編集した場合
```bash
# 1. main_textbook.mdを編集
# 2. 各章のREADME.mdに反映
python3 scripts/update_chapter_readmes.py
```

### ケース2: 各章のREADME.mdを編集した場合
```bash
# 1. src/*/README.mdを編集
# 2. main_textbook.mdを再生成
python3 scripts/generate_main_textbook.py
# 3. 生成されたファイルを確認
# 4. 問題なければリネーム
mv docs/main_textbook_generated.md docs/main_textbook.md
```

### ケース3: 配布用ドキュメントを生成
```bash
# Word文書の生成
./scripts/create_main_textbook.sh
./scripts/create_exercises.sh

# PDF文書の生成
./scripts/create_pdf.sh
```

## 注意事項

1. **文字コード**: すべてのファイルはUTF-8で保存してください
2. **改行コード**: LF（Unix形式）を使用してください
3. **Python**: Python 3.6以上が必要です
4. **権限**: シェルスクリプトには実行権限が必要です（`chmod +x script.sh`）

## トラブルシューティング

### "Permission denied"エラー
```bash
chmod +x scripts/*.sh
chmod +x scripts/*.py
```

### Pythonパスエラー
```bash
# Python3のパスを確認
which python3
# 必要に応じてスクリプトの1行目を修正
```

### 文字化け
- ファイルの文字コードがUTF-8であることを確認
- ターミナルの文字コード設定を確認