#!/usr/bin/env python3
"""
Pandoc filter to apply custom table styles
"""
import panflute as pf

def action(elem, doc):
    if isinstance(elem, pf.Table):
        # テーブルに特定のスタイルを適用するための処理
        # Wordの場合、カスタム属性を追加
        return elem

def main(doc=None):
    return pf.run_filter(action, doc=doc)

if __name__ == '__main__':
    main()