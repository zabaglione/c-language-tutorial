#!/bin/bash

echo "📚 C言語学習教材 PDF作成スクリプト"
echo "================================"

# Check if Chrome is available for PDF conversion
if command -v "/Applications/Google Chrome.app/Contents/MacOS/Google Chrome" &> /dev/null; then
    echo "✅ Google Chrome found - PDF conversion available"
    
    # Convert HTML to PDF using Chrome with proper settings
    "/Applications/Google Chrome.app/Contents/MacOS/Google Chrome" \
        --headless \
        --disable-gpu \
        --print-to-pdf="../output/pdf/C言語学習教材.pdf" \
        --print-to-pdf-no-header \
        --hide-scrollbars \
        --virtual-time-budget=10000 \
        --run-all-compositor-stages-before-draw \
        "file://$(pwd)/C言語学習教材_styled.html"
    
    if [ $? -eq 0 ]; then
        echo "✅ PDF作成完了: ../output/pdf/C言語学習教材.pdf"
        ls -lh "../output/pdf/C言語学習教材.pdf"
    else
        echo "❌ PDF作成に失敗しました"
    fi
else
    echo "❌ Google Chrome not found"
    echo "📋 Manual conversion options:"
    echo "1. Open 'C言語学習教材_styled.html' in browser"
    echo "2. Use Print → Save as PDF"
    echo "3. Or install wkhtmltopdf for command line conversion"
fi

echo ""
echo "📄 Created files:"
echo "- complete_tutorial.md (統合Markdownファイル)"
echo "- C言語学習教材.html (基本HTMLファイル)"
echo "- C言語学習教材_styled.html (スタイル付きHTMLファイル)"
if [ -f "../output/pdf/C言語学習教材.pdf" ]; then
    echo "- ../output/pdf/C言語学習教材.pdf (PDFファイル)"
fi