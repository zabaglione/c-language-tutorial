#!/bin/bash

# macOSのwkhtmltopdfまたはcutyPDFを使用してHTMLをPDFに変換

echo "HTMLファイルをPDFに変換します..."

# Chromeがインストールされているか確認
if [ -d "/Applications/Google Chrome.app" ]; then
    echo "Google Chromeを使用してPDFを生成します..."
    
    # メインテキストのPDF生成
    "/Applications/Google Chrome.app/Contents/MacOS/Google Chrome" \
        --headless \
        --disable-gpu \
        --print-to-pdf="C言語プログラミング教材_メインテキスト.pdf" \
        --no-pdf-header-footer \
        "file://$PWD/C言語プログラミング教材_メインテキスト.html"
    
    # 演習課題集のPDF生成
    "/Applications/Google Chrome.app/Contents/MacOS/Google Chrome" \
        --headless \
        --disable-gpu \
        --print-to-pdf="C言語プログラミング教材_演習課題集.pdf" \
        --no-pdf-header-footer \
        "file://$PWD/C言語プログラミング教材_演習課題集.html"
    
    echo "PDFの生成が完了しました。"
    echo "- C言語プログラミング教材_メインテキスト.pdf"
    echo "- C言語プログラミング教材_演習課題集.pdf"
else
    echo "Google Chromeがインストールされていません。"
    echo "以下の方法でPDFを作成してください："
    echo "1. 生成されたHTMLファイルをブラウザで開く"
    echo "2. 印刷メニューから「PDFとして保存」を選択"
    echo ""
    echo "生成されたHTMLファイル:"
    echo "- C言語プログラミング教材_メインテキスト.html"
    echo "- C言語プログラミング教材_演習課題集.html"
fi