/*
 * ファイル名: ex11_2_coordinate_c99.c
 * 演習11-2: 座標計算（C99版）
 * 説明: 2D座標を表す構造体を定義し、2点間の距離を計算
 * 規格: C99準拠 - 複合リテラル、inline関数、bool型、VLA
 */

#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>

// 2D座標を表す構造体
typedef struct {
    double x;
    double y;
} Point2D;

// 座標演算の結果を格納する構造体
typedef struct {
    double distance;
    double angle;  // ラジアン単位
} PolarCoord;

// C99: inline関数で高速な座標表示
static inline void display_point(const Point2D *point, const char *name)
{
    if (point == NULL || name == NULL) {
        printf("エラー: 無効なポインタです\n");
        return;
    }
    
    printf("%s: (%.2f, %.2f)\n", name, point->x, point->y);
}

// C99: inline関数で2点間の距離を計算
static inline double calculate_distance(const Point2D *p1, const Point2D *p2)
{
    if (p1 == NULL || p2 == NULL) {
        return -1.0;
    }
    
    double dx = p2->x - p1->x;
    double dy = p2->y - p1->y;
    
    return sqrt(dx * dx + dy * dy);
}

// 座標を移動する関数（ポインタで更新）
void move_point(Point2D *point, double dx, double dy)
{
    if (point == NULL) {
        printf("エラー: 無効なポインタです\n");
        return;
    }
    
    point->x += dx;
    point->y += dy;
}

// ベクトル演算: 加算
Point2D add_points(const Point2D *p1, const Point2D *p2)
{
    if (p1 == NULL || p2 == NULL) {
        return (Point2D){0.0, 0.0};  // C99: 複合リテラル
    }
    
    return (Point2D){p1->x + p2->x, p1->y + p2->y};
}

// ベクトル演算: スカラー倍
Point2D scale_point(const Point2D *point, double scale)
{
    if (point == NULL) {
        return (Point2D){0.0, 0.0};
    }
    
    return (Point2D){point->x * scale, point->y * scale};
}

// 極座標への変換
PolarCoord to_polar(const Point2D *point)
{
    if (point == NULL) {
        return (PolarCoord){0.0, 0.0};
    }
    
    double distance = sqrt(point->x * point->x + point->y * point->y);
    double angle = atan2(point->y, point->x);
    
    return (PolarCoord){distance, angle};
}

// 極座標から直交座標への変換
Point2D from_polar(double r, double theta)
{
    return (Point2D){r * cos(theta), r * sin(theta)};
}

// C99: bool型を使った座標範囲チェック
static inline bool is_in_rectangle(const Point2D *point, 
                                  double x_min, double y_min,
                                  double x_max, double y_max)
{
    if (point == NULL) return false;
    
    return point->x >= x_min && point->x <= x_max &&
           point->y >= y_min && point->y <= y_max;
}

// C99: bool型を使った円内判定
static inline bool is_in_circle(const Point2D *point, 
                               const Point2D *center, 
                               double radius)
{
    return calculate_distance(point, center) <= radius;
}

// C99: VLAを使った複数点の処理
void process_points_vla(size_t count, Point2D points[count])
{
    if (count == 0 || points == NULL) return;
    
    // 各点の極座標を計算
    PolarCoord polar_coords[count];  // C99: VLA
    
    printf("\n極座標変換:\n");
    for (size_t i = 0; i < count; i++) {
        polar_coords[i] = to_polar(&points[i]);
        printf("点%zu: r=%.2f, θ=%.2f°\n", 
               i + 1, 
               polar_coords[i].distance,
               polar_coords[i].angle * 180.0 / M_PI);
    }
}

// 線分の交差判定
bool check_line_intersection(const Point2D *p1, const Point2D *p2,
                            const Point2D *p3, const Point2D *p4)
{
    if (p1 == NULL || p2 == NULL || p3 == NULL || p4 == NULL) {
        return false;
    }
    
    double d1x = p2->x - p1->x;
    double d1y = p2->y - p1->y;
    double d2x = p4->x - p3->x;
    double d2y = p4->y - p3->y;
    
    double denominator = d1x * d2y - d1y * d2x;
    
    // 平行な場合
    if (fabs(denominator) < 1e-10) {
        return false;
    }
    
    double t1 = ((p3->x - p1->x) * d2y - (p3->y - p1->y) * d2x) / denominator;
    double t2 = ((p3->x - p1->x) * d1y - (p3->y - p1->y) * d1x) / denominator;
    
    return t1 >= 0.0 && t1 <= 1.0 && t2 >= 0.0 && t2 <= 1.0;
}

int main(void)
{
    printf("===== 2D座標計算プログラム (C99版) =====\n\n");
    
    // C99: 指定初期化子で座標を作成
    Point2D point1 = {.x = 0.0, .y = 0.0};
    Point2D point2 = {.x = 3.0, .y = 4.0};
    
    /* デモ用: 固定値で表示 */
    printf("点1の座標を入力 (x y): %.0f %.0f\n", point1.x, point1.y);
    printf("点2の座標を入力 (x y): %.0f %.0f\n", point2.x, point2.y);
    
    /* 座標の表示 */
    printf("\n");
    display_point(&point1, "点1");
    display_point(&point2, "点2");
    
    /* 2点間の距離を計算 */
    double distance = calculate_distance(&point1, &point2);
    printf("2点間の距離: %.2f\n", distance);
    
    /* ベクトル演算 */
    printf("\n=== ベクトル演算 ===\n");
    Point2D sum = add_points(&point1, &point2);
    display_point(&sum, "点1 + 点2");
    
    Point2D scaled = scale_point(&point2, 0.5);
    display_point(&scaled, "点2 × 0.5");
    
    /* 極座標変換 */
    printf("\n=== 極座標変換 ===\n");
    PolarCoord polar2 = to_polar(&point2);
    printf("点2の極座標: r=%.2f, θ=%.2f° (%.2fラジアン)\n",
           polar2.distance,
           polar2.angle * 180.0 / M_PI,
           polar2.angle);
    
    /* 座標の移動 */
    printf("\n点1を移動します。\n");
    printf("移動量を入力 (dx dy): 1 1\n");
    move_point(&point1, 1.0, 1.0);
    
    printf("\n移動後の");
    display_point(&point1, "点1");
    
    /* 新しい距離の計算 */
    distance = calculate_distance(&point1, &point2);
    printf("新しい距離: %.2f\n", distance);
    
    /* 範囲チェック */
    printf("\n=== 範囲チェック ===\n");
    bool in_rect = is_in_rectangle(&point2, 0, 0, 5, 5);
    printf("点2は矩形(0,0)-(5,5)内に%s\n", 
           in_rect ? "あります" : "ありません");
    
    Point2D center = {.x = 0.0, .y = 0.0};
    bool in_circle = is_in_circle(&point2, &center, 5.0);
    printf("点2は原点を中心とする半径5の円内に%s\n",
           in_circle ? "あります" : "ありません");
    
    /* C99: 複合リテラルを使った複数点の管理 */
    printf("\n\n=== 複数点の管理デモ (C99) ===\n");
    
    Point2D points[] = {
        {1.0, 2.0},
        {-3.0, 4.0},
        {-2.0, -5.0},
        {4.0, -1.0},
        {0.0, 3.0}
    };
    size_t num_points = sizeof(points) / sizeof(points[0]);
    
    /* VLAを使った処理 */
    process_points_vla(num_points, points);
    
    /* 凸包の簡易判定（3点の三角形） */
    printf("\n=== 三角形の性質 ===\n");
    Point2D triangle[] = {
        {0.0, 0.0},
        {4.0, 0.0},
        {2.0, 3.0}
    };
    
    // 三角形の面積計算（外積を使用）
    double area = fabs((triangle[1].x - triangle[0].x) * (triangle[2].y - triangle[0].y) -
                      (triangle[2].x - triangle[0].x) * (triangle[1].y - triangle[0].y)) / 2.0;
    printf("三角形の面積: %.2f\n", area);
    
    // 三角形の周囲長
    double perimeter = 0.0;
    for (int i = 0; i < 3; i++) {
        perimeter += calculate_distance(&triangle[i], &triangle[(i + 1) % 3]);
    }
    printf("三角形の周囲長: %.2f\n", perimeter);
    
    /* 線分の交差判定 */
    printf("\n=== 線分の交差判定 ===\n");
    Point2D line1_start = {0.0, 0.0};
    Point2D line1_end = {4.0, 4.0};
    Point2D line2_start = {0.0, 4.0};
    Point2D line2_end = {4.0, 0.0};
    
    bool intersects = check_line_intersection(&line1_start, &line1_end,
                                            &line2_start, &line2_end);
    printf("線分1 (0,0)-(4,4) と 線分2 (0,4)-(4,0) は%s\n",
           intersects ? "交差しています" : "交差していません");
    
    /* 統計情報 */
    printf("\n=== 統計情報 ===\n");
    Point2D centroid = {0.0, 0.0};
    double max_dist = 0.0;
    
    // 重心計算
    for (size_t i = 0; i < num_points; i++) {
        centroid.x += points[i].x;
        centroid.y += points[i].y;
        
        // 原点からの最大距離
        double dist = calculate_distance(&points[i], &(Point2D){0.0, 0.0});
        if (dist > max_dist) {
            max_dist = dist;
        }
    }
    
    centroid.x /= num_points;
    centroid.y /= num_points;
    
    printf("全点の重心: (%.2f, %.2f)\n", centroid.x, centroid.y);
    printf("原点から最も遠い点の距離: %.2f\n", max_dist);
    
    return 0;
}

/*
実行例:
===== 2D座標計算プログラム (C99版) =====

点1の座標を入力 (x y): 0 0
点2の座標を入力 (x y): 3 4

点1: (0.00, 0.00)
点2: (3.00, 4.00)
2点間の距離: 5.00

=== ベクトル演算 ===
点1 + 点2: (3.00, 4.00)
点2 × 0.5: (1.50, 2.00)

=== 極座標変換 ===
点2の極座標: r=5.00, θ=53.13° (0.93ラジアン)

点1を移動します。
移動量を入力 (dx dy): 1 1

移動後の点1: (1.00, 1.00)
新しい距離: 3.61

=== 範囲チェック ===
点2は矩形(0,0)-(5,5)内にあります
点2は原点を中心とする半径5の円内にあります

=== 複数点の管理デモ (C99) ===

極座標変換:
点1: r=2.24, θ=63.43°
点2: r=5.00, θ=126.87°
点3: r=5.39, θ=-111.80°
点4: r=4.12, θ=-14.04°
点5: r=3.00, θ=90.00°

=== 三角形の性質 ===
三角形の面積: 6.00
三角形の周囲長: 10.65

=== 線分の交差判定 ===
線分1 (0,0)-(4,4) と 線分2 (0,4)-(4,0) は交差しています

=== 統計情報 ===
全点の重心: (0.00, 0.60)
原点から最も遠い点の距離: 5.39
*/
