# pandocスタイル設定オプション

## 表のスタイル設定

```bash
# 表のスタイルを変更
pandoc input.md -o output.docx --reference-doc=template.docx
```

## リストのスタイル設定

以下の方法でリストスタイルをカスタマイズできます：

### 1. CSSスタイルを使用
```bash
pandoc input.md -o output.docx --css=custom-styles.css
```

### 2. HTMLクラスを指定
```markdown
::: {.custom-list}
- リスト項目1
- リスト項目2
:::
```

### 3. 直接HTMLを使用
```html
<ul style="list-style-type: disc; margin: 1em 0;">
<li>カスタムリスト項目1</li>
<li>カスタムリスト項目2</li>
</ul>
```

## 推奨方法

1. reference-styled.docxをWordで開く
2. 必要なスタイルを手動で調整
3. テンプレートとして保存
4. pandocで --reference-doc オプションを使用