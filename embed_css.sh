#!/bin/bash

# CSSを埋め込んだHTMLファイルを作成
for html_file in "C言語プログラミング教材_メインテキスト.html" "C言語プログラミング教材_演習課題集.html"; do
    if [ -f "$html_file" ]; then
        # 一時ファイルを作成
        temp_file="${html_file}.tmp"
        
        # HTMLファイルの<head>セクションにCSSを埋め込む
        awk '
        /<head>/ {
            print
            print "<style>"
            while ((getline line < "create_pdf_style.css") > 0) {
                print line
            }
            close("create_pdf_style.css")
            print "</style>"
            next
        }
        /<link.*css=/ {next}
        {print}
        ' "$html_file" > "$temp_file"
        
        # 元のファイルを置き換え
        mv "$temp_file" "$html_file"
        echo "CSSを埋め込みました: $html_file"
    fi
done