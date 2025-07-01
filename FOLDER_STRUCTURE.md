# フォルダ構造 (Folder Structure)

## プロジェクト構成

```
c-language-tutorial/
├── src/                    # ソースコード（各章の教材）
│   ├── introduction/       # 第1章: 導入・環境構築
│   ├── basics-syntax/      # 第2章: 基本文法
│   └── ...                 # 他の章
├── scripts/                # ビルド・生成スクリプト
│   ├── create_*.sh         # 各種生成スクリプト
│   └── *.py                # Pythonユーティリティ
├── output/                 # 生成された成果物
│   ├── word/              # Word文書 (.docx)
│   ├── pdf/               # PDF文書
│   └── html/              # HTML文書
├── docs/                   # プロジェクトドキュメント
│   ├── main_textbook.md    # 統合版教科書（Markdown）
│   ├── exercises_workbook.md # 演習問題集（Markdown）
│   └── *.md                # その他のドキュメント
├── reports/                # 各種レポート・報告書
│   ├── *報告.md            # 作業報告書
│   └── *report.md          # 評価レポート
└── custom-reference-1.docx # Wordテンプレートファイル
```

## 各フォルダの説明

### `/src`
- 教材のソースコード
- 各章ごとにサブフォルダ
- README.md、examples/、exercises/、solutions/を含む

### `/scripts`
- ドキュメント生成スクリプト
- PDFやWord文書を作成するツール

### `/output`
- **すべての生成物はここに保存**
- `word/`: Word文書（.docx）
- `pdf/`: PDF文書
- `html/`: HTML文書

### `/docs`
- プロジェクトのドキュメント
- Markdown形式の統合版教材

### `/reports`
- 作業報告書
- 評価レポート
- プロジェクトの進捗記録

## 命名規則

### Word文書 (`/output/word/`)
- 章別: `chapter_XX_textbook.docx`, `chapter_XX_exercises.docx`
- 統合版: `C言語プログラミング教材_メインテキスト.docx`, `C言語プログラミング教材_演習問題集.docx`

### PDF文書 (`/output/pdf/`)
- メイン教材: `C言語学習教材.pdf`
- 分割版: `C言語プログラミング教材_メインテキスト.pdf`, `C言語プログラミング教材_演習課題集.pdf`

### HTML文書 (`/output/html/`)
- 基本版: `C言語学習教材.html`
- スタイル付き: `C言語学習教材_styled.html`