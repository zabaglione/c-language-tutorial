# フォルダ構造再編成レポート

## 日付: 2025-07-01

## 実施内容

### 問題点
- `docs/` と `output/docs/` という同名で異なる目的のフォルダが存在していた
- 混乱を招く可能性があった

### 実施した変更

1. **新しいフォルダ構造の作成**
   ```
   output/
   ├── word/   # Word文書 (.docx)
   ├── pdf/    # PDF文書
   └── html/   # HTML文書
   
   reports/    # レポート・報告書（旧docs/から移動）
   ```

2. **ファイルの移動**
   - `output/docs/*.docx` → `output/word/`
   - `output/*.html` → `output/html/`
   - `output/*.pdf` → `output/pdf/`（既存）
   - `docs/*報告*.md` → `reports/`
   - `docs/*report*.md` → `reports/`

3. **スクリプトの更新**
   - すべてのシェルスクリプトで `output/docs` → `output/word` に変更
   - Pythonスクリプトも同様に更新
   - PDF生成スクリプトを `output/pdf/` に出力するよう更新

4. **ドキュメントの更新**
   - `CLAUDE.md` - プロジェクト構造の説明を更新
   - `FOLDER_STRUCTURE.md` - 新規作成（詳細なフォルダ構造の説明）

### 結果

- **明確な構造**: 各出力形式ごとに専用フォルダ
- **一貫性**: すべての生成物は `output/` 配下に統一
- **整理整頓**: レポート類は専用の `reports/` フォルダへ

### 影響を受けたファイル

**スクリプト**:
- `scripts/create_merged_docs_no_samples.sh`
- `scripts/create_merged_docs_final.sh`
- `scripts/create_merged_docs_pandoc_fixed_codeblock.sh`
- `scripts/create_chapter_docs.py`
- `scripts/merge_docx_files.py`
- `scripts/create_pdf.sh`

**ドキュメント**:
- `CLAUDE.md`
- `FOLDER_STRUCTURE.md` (新規)

## 今後の運用

1. すべての生成物は適切な `output/` サブフォルダに保存
2. プロジェクトドキュメントは `docs/` に保持
3. 作業報告書は `reports/` に保存