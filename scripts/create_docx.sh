#!/bin/bash

# docx生成コマンド - C言語プログラミング教材用
# 使用方法: ./create_docx.sh [オプション] [タイプ]

# 色付き出力用のカラーコード
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# ベースディレクトリ
BASE_DIR=$(cd "$(dirname "$0")/.." && pwd)
OUTPUT_DIR="$BASE_DIR/output/word"
TEMPLATE_DIR="$BASE_DIR/templates"

# 出力ディレクトリを作成
mkdir -p "$OUTPUT_DIR"

# ヘルプ表示
show_help() {
    cat << EOF
${BLUE}C言語プログラミング教材 - docx生成コマンド${NC}

${YELLOW}使用方法:${NC}
    ./create_docx.sh [オプション] [タイプ]

${YELLOW}タイプ:${NC}
    all             - すべての文書を生成
    basic           - 基礎編（第1-6章）
    intermediate    - 応用編（第7-11章）
    advanced        - 上級編（第12-16章）
    supplements     - 補章（C言語規格・開発環境）
    exercises       - 演習問題集（すべて）
    ex-basic        - 基礎編演習問題集
    ex-intermediate - 応用編演習問題集
    ex-advanced     - 上級編演習問題集

${YELLOW}オプション:${NC}
    -h, --help      - このヘルプを表示
    -v, --verbose   - 詳細なログを表示
    -o, --output    - 出力ディレクトリを指定
    -t, --template  - テンプレートファイルを指定
    -l, --list      - 生成可能な文書一覧を表示
    -c, --clean     - 生成前に出力ディレクトリをクリーンアップ

${YELLOW}例:${NC}
    ./create_docx.sh all                    # すべての文書を生成
    ./create_docx.sh basic                  # 基礎編のみ生成
    ./create_docx.sh -v exercises           # 演習問題集を詳細ログ付きで生成
    ./create_docx.sh -o /tmp/docs basic     # 出力先を指定して基礎編を生成
    ./create_docx.sh -c advanced            # クリーンアップ後に上級編を生成

EOF
}

# 生成可能な文書一覧を表示
show_list() {
    echo -e "${BLUE}生成可能な文書一覧:${NC}"
    echo ""
    echo -e "${YELLOW}メインテキスト:${NC}"
    echo "  - C言語プログラミング教材_メインテキスト_基礎編.docx"
    echo "  - C言語プログラミング教材_メインテキスト_応用編.docx"
    echo "  - C言語プログラミング教材_メインテキスト_上級編.docx"
    echo ""
    echo -e "${YELLOW}演習問題集:${NC}"
    echo "  - C言語プログラミング教材_演習問題集_基礎編.docx"
    echo "  - C言語プログラミング教材_演習問題集_応用編.docx"
    echo "  - C言語プログラミング教材_演習問題集_上級編.docx"
    echo ""
    echo -e "${YELLOW}補章:${NC}"
    echo "  - C言語プログラミング教材_補章.docx"
    echo ""
}

# ログ出力
log_info() {
    if [ "$VERBOSE" = "true" ]; then
        echo -e "${BLUE}[INFO]${NC} $1"
    fi
}

log_success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1"
}

log_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

log_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

# 文書生成関数
generate_basic() {
    log_info "基礎編メインテキストを生成中..."
    if bash "$BASE_DIR/scripts/create_main_textbook_basic.sh"; then
        log_success "基礎編メインテキストが生成されました"
    else
        log_error "基礎編メインテキストの生成に失敗しました"
        return 1
    fi
}

generate_intermediate() {
    log_info "応用編メインテキストを生成中..."
    if bash "$BASE_DIR/scripts/create_main_textbook_intermediate.sh"; then
        log_success "応用編メインテキストが生成されました"
    else
        log_error "応用編メインテキストの生成に失敗しました"
        return 1
    fi
}

generate_advanced() {
    log_info "上級編メインテキストを生成中..."
    if bash "$BASE_DIR/scripts/create_main_textbook_advanced.sh"; then
        log_success "上級編メインテキストが生成されました"
    else
        log_error "上級編メインテキストの生成に失敗しました"
        return 1
    fi
}

generate_supplements() {
    log_info "補章を生成中..."
    if bash "$BASE_DIR/scripts/create_supplementary_chapters.sh"; then
        log_success "補章が生成されました"
    else
        log_error "補章の生成に失敗しました"
        return 1
    fi
}

generate_ex_basic() {
    log_info "基礎編演習問題集を生成中..."
    if bash "$BASE_DIR/scripts/create_exercises_basic.sh"; then
        log_success "基礎編演習問題集が生成されました"
    else
        log_error "基礎編演習問題集の生成に失敗しました"
        return 1
    fi
}

generate_ex_intermediate() {
    log_info "応用編演習問題集を生成中..."
    if bash "$BASE_DIR/scripts/create_exercises_intermediate.sh"; then
        log_success "応用編演習問題集が生成されました"
    else
        log_error "応用編演習問題集の生成に失敗しました"
        return 1
    fi
}

generate_ex_advanced() {
    log_info "上級編演習問題集を生成中..."
    if bash "$BASE_DIR/scripts/create_exercises_advanced.sh"; then
        log_success "上級編演習問題集が生成されました"
    else
        log_error "上級編演習問題集の生成に失敗しました"
        return 1
    fi
}

# 依存関係チェック
check_dependencies() {
    log_info "依存関係をチェック中..."

    # pandocの確認
    if ! command -v pandoc &> /dev/null; then
        log_error "pandocがインストールされていません"
        echo "インストール方法:"
        echo "  macOS: brew install pandoc"
        echo "  Ubuntu: sudo apt install pandoc"
        return 1
    fi

    log_info "pandoc: $(pandoc --version | head -n1)"

    # 必要なディレクトリの確認
    if [ ! -d "$BASE_DIR/src" ]; then
        log_error "ソースディレクトリが見つかりません: $BASE_DIR/src"
        return 1
    fi

    log_info "依存関係チェック完了"
    return 0
}

# クリーンアップ
cleanup() {
    log_info "出力ディレクトリをクリーンアップ中..."
    rm -rf "$OUTPUT_DIR"/*.docx
    log_info "クリーンアップ完了"
}

# 変数の初期化
VERBOSE=false
CLEAN=false
TYPE=""
CUSTOM_OUTPUT=""
CUSTOM_TEMPLATE=""

# 引数解析
while [[ $# -gt 0 ]]; do
    case $1 in
        -h|--help)
            show_help
            exit 0
            ;;
        -v|--verbose)
            VERBOSE=true
            shift
            ;;
        -o|--output)
            CUSTOM_OUTPUT="$2"
            shift 2
            ;;
        -t|--template)
            CUSTOM_TEMPLATE="$2"
            shift 2
            ;;
        -l|--list)
            show_list
            exit 0
            ;;
        -c|--clean)
            CLEAN=true
            shift
            ;;
        -*)
            log_error "不明なオプション: $1"
            show_help
            exit 1
            ;;
        *)
            if [ -z "$TYPE" ]; then
                TYPE="$1"
            else
                log_error "複数のタイプが指定されました: $TYPE, $1"
                exit 1
            fi
            shift
            ;;
    esac
done

# カスタム出力ディレクトリの設定
if [ -n "$CUSTOM_OUTPUT" ]; then
    OUTPUT_DIR="$CUSTOM_OUTPUT"
    mkdir -p "$OUTPUT_DIR"
fi

# 依存関係チェック
if ! check_dependencies; then
    exit 1
fi

# クリーンアップ実行
if [ "$CLEAN" = "true" ]; then
    cleanup
fi

# タイプが指定されていない場合
if [ -z "$TYPE" ]; then
    log_error "タイプが指定されていません"
    show_help
    exit 1
fi

# 開始メッセージ
echo -e "${BLUE}C言語プログラミング教材 - docx生成開始${NC}"
echo -e "タイプ: ${YELLOW}$TYPE${NC}"
echo -e "出力先: ${YELLOW}$OUTPUT_DIR${NC}"
echo ""

# 生成開始時間
start_time=$(date +%s)

# タイプに応じた処理
case $TYPE in
    all)
        log_info "すべての文書を生成します..."
        generate_basic && \
        generate_intermediate && \
        generate_advanced && \
        generate_supplements && \
        generate_ex_basic && \
        generate_ex_intermediate && \
        generate_ex_advanced
        ;;
    basic)
        generate_basic
        ;;
    intermediate)
        generate_intermediate
        ;;
    advanced)
        generate_advanced
        ;;
    supplements)
        generate_supplements
        ;;
    exercises)
        log_info "すべての演習問題集を生成します..."
        generate_ex_basic && \
        generate_ex_intermediate && \
        generate_ex_advanced
        ;;
    ex-basic)
        generate_ex_basic
        ;;
    ex-intermediate)
        generate_ex_intermediate
        ;;
    ex-advanced)
        generate_ex_advanced
        ;;
    *)
        log_error "不明なタイプ: $TYPE"
        echo ""
        show_help
        exit 1
        ;;
esac

# 結果チェック
if [ $? -eq 0 ]; then
    # 終了時間と実行時間計算
    end_time=$(date +%s)
    execution_time=$((end_time - start_time))

    echo ""
    log_success "docx生成が完了しました！"
    echo -e "実行時間: ${YELLOW}${execution_time}秒${NC}"
    echo -e "出力先: ${YELLOW}$OUTPUT_DIR${NC}"

    # 生成されたファイル一覧
    echo ""
    echo -e "${BLUE}生成されたファイル:${NC}"
    ls -la "$OUTPUT_DIR"/*.docx 2>/dev/null | while read -r line; do
        echo "  $line"
    done
else
    log_error "docx生成中にエラーが発生しました"
    exit 1
fi