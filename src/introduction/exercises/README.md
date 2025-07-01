# 演習課題

## 演習の目的

この演習を通して、C言語の開発環境が正しく構築されているかを確認し、基本的なコンパイル手順を習得します。

## 演習課題

### 基礎問題

#### 問題1: 環境構築確認
サンプルプログラム `examples/environment_check.c` を使用して、以下の作業を実行してください。

1. **C90準拠でコンパイル・実行**
   ```bash
   make c90
   ```

2. **C99準拠でコンパイル・実行**
   ```bash
   make c99
   ```

3. **C11準拠でコンパイル・実行**
   ```bash
   make c11
   ```

4. **C17準拠でコンパイル・実行**
   ```bash
   make c17
   ```

5. **実行結果の確認**
   - 各規格でコンパイルしたプログラムの出力結果を比較してください
   - 規格による違いがあるかを確認してください

#### 問題2: コンパイラ情報の確認
以下のコマンドを実行して、開発環境の情報を調べてください。

1. **コンパイラバージョンの確認**
   ```bash
   gcc --version
   ```

2. **対応規格の確認**
   ```bash
   gcc -std=c90 --help
   gcc -std=c99 --help
   gcc -std=c11 --help
   gcc -std=c17 --help
   ```

3. **プリプロセッサマクロの確認**
   ```bash
   echo | gcc -dM -E -
   ```

#### 問題3: 基本的なプログラム作成
`solutions/ex1_3_hello_name.c` というファイルを作成し、以下の機能を実装してください。

**要求仕様:**
- ユーザーに名前の入力を求める
- 入力された名前を使って挨拶メッセージを表示する
- C90準拠で記述する

**実行例:**
```
あなたの名前を入力してください: 田中
こんにちは、田中さん！
```

### 応用問題

#### 問題4: 規格比較レポート
C90とC99の主な違いについて調べ、以下の点についてまとめてください。

1. **新しく追加されたデータ型**
2. **新しく追加された機能**
3. **プログラムの書き方で変わった点**
4. **組込み開発でC90が使われ続ける理由**

回答は `exercises/standards_comparison.md` に記述してください。

#### 問題5: コンパイル手順の詳細調査
以下のコンパイラオプションを使用して、コンパイル過程を段階的に確認してください。

1. **プリプロセッサ出力の確認**
   ```bash
   gcc -E examples/environment_check.c > preprocessed.i
   ```

2. **アセンブリコード生成**
   ```bash
   gcc -S examples/environment_check.c
   ```

3. **オブジェクトファイル生成**
   ```bash
   gcc -c examples/environment_check.c
   ```

4. **実行ファイル生成**
   ```bash
   gcc environment_check.o -o environment_check
   ```

各段階で生成されるファイルの内容を確認し、`exercises/compilation_report.md` にまとめてください。

#### 問題6: 環境固有情報の調査
以下の情報を調べて、`solutions/ex1_6_system_info.c` プログラムを作成してください。

**表示する情報:**
- 使用しているOS
- コンパイラの種類とバージョン
- CPUアーキテクチャ（32bit/64bit）
- エンディアン（ビッグエンディアン/リトルエンディアン）
- 各データ型のサイズ

## 提出形式

各問題の回答は以下のファイルに記述してください。

- **問題3**: `solutions/ex1_3_hello_name.c`
- **問題4**: `exercises/standards_comparison.md`
- **問題5**: `exercises/compilation_report.md`
- **問題6**: `solutions/ex1_6_system_info.c`

## 評価基準

### 基礎問題
- [ ] 環境確認プログラムが正常にコンパイル・実行できる
- [ ] 各規格でのコンパイルができる
- [ ] ex1_3_hello_name.cが要求仕様を満たしている
- [ ] C90準拠で記述されている

### 応用問題
- [ ] 規格比較が正確に記述されている
- [ ] コンパイル手順が理解できている
- [ ] 環境固有情報の取得ができている
- [ ] レポートが詳細で分かりやすい

## 参考資料

- [GCC公式ドキュメント](https://gcc.gnu.org/documentation.html)
- [C言語規格書](https://www.iso.org/standard/74528.html)
- [GNU Make マニュアル](https://www.gnu.org/software/make/manual/)

## 次の段階

演習課題が完了したら、[基本文法・Hello World](../../basics-syntax/README.md) に進んでください。