#!/bin/bash
# 改ページのテスト

TEMPLATE="../custom-reference-1.docx"

# テスト用Markdownファイルを作成
cat > /tmp/test_pagebreak.md << 'EOF'
# テストドキュメント

## 第1章

これは第1章の内容です。

```{=openxml}
<w:p><w:r><w:br w:type="page"/></w:r></w:p>
```

## 第2章

これは第2章の内容です。

\newpage

## 第3章

これは第3章の内容です。

---

## 第4章

これは第4章の内容です。

EOF

# 各種方法でテスト
echo "改ページテスト1: OpenXML raw attribute"
pandoc /tmp/test_pagebreak.md \
    --reference-doc="$TEMPLATE" \
    -o /tmp/test_pagebreak1.docx \
    --from markdown+raw_attribute \
    --to docx

echo "改ページテスト2: 標準markdown"
pandoc /tmp/test_pagebreak.md \
    --reference-doc="$TEMPLATE" \
    -o /tmp/test_pagebreak2.docx \
    --from markdown \
    --to docx

echo "改ページテスト3: pandoc拡張"
pandoc /tmp/test_pagebreak.md \
    --reference-doc="$TEMPLATE" \
    -o /tmp/test_pagebreak3.docx \
    --from markdown+raw_tex \
    --to docx

echo "テストファイルを作成しました："
ls -la /tmp/test_pagebreak*.docx