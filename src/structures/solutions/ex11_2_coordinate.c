/*
 * ファイル名: ex11_2_coordinate.c
 * 演習11-2: 座標計算
 * 説明: 2D座標を表す構造体を定義し、2点間の距離を計算
 * 規格: C90準拠
 */

#include <stdio.h>
#include <math.h>

/* 2D座標を表す構造体 */
struct Point2D {
    double x;
    double y;
};

/* 座標を表示する関数 */
void display_point(const struct Point2D *point, const char *name)
{
    if (point == NULL || name == NULL) {
        printf("エラー: 無効なポインタです\n");
        return;
    }
    
    printf("%s: (%.2f, %.2f)\n", name, point->x, point->y);
}

/* 2点間の距離を計算する関数（ポインタ引数） */
double calculate_distance(const struct Point2D *p1, const struct Point2D *p2)
{
    double dx, dy;
    
    if (p1 == NULL || p2 == NULL) {
        printf("エラー: 無効なポインタです\n");
        return -1.0;
    }
    
    dx = p2->x - p1->x;
    dy = p2->y - p1->y;
    
    return sqrt(dx * dx + dy * dy);
}

/* 座標を移動する関数（ポインタで更新） */
void move_point(struct Point2D *point, double dx, double dy)
{
    if (point == NULL) {
        printf("エラー: 無効なポインタです\n");
        return;
    }
    
    point->x += dx;
    point->y += dy;
}

/* 中点を計算する関数 */
struct Point2D calculate_midpoint(const struct Point2D *p1, const struct Point2D *p2)
{
    struct Point2D midpoint;
    
    if (p1 == NULL || p2 == NULL) {
        midpoint.x = 0.0;
        midpoint.y = 0.0;
        return midpoint;
    }
    
    midpoint.x = (p1->x + p2->x) / 2.0;
    midpoint.y = (p1->y + p2->y) / 2.0;
    
    return midpoint;
}

/* 原点からの距離を計算する関数 */
double distance_from_origin(const struct Point2D *point)
{
    struct Point2D origin = {0.0, 0.0};
    return calculate_distance(&origin, point);
}

/* 座標の象限を判定する関数 */
int get_quadrant(const struct Point2D *point)
{
    if (point == NULL) {
        return 0;
    }
    
    if (point->x > 0 && point->y > 0) {
        return 1;  /* 第1象限 */
    } else if (point->x < 0 && point->y > 0) {
        return 2;  /* 第2象限 */
    } else if (point->x < 0 && point->y < 0) {
        return 3;  /* 第3象限 */
    } else if (point->x > 0 && point->y < 0) {
        return 4;  /* 第4象限 */
    } else {
        return 0;  /* 軸上または原点 */
    }
}

int main(void)
{
    struct Point2D point1, point2;
    struct Point2D midpoint;
    double distance;
    double dx, dy;
    int quadrant;
    
    printf("===== 2D座標計算プログラム =====\n\n");
    
    /* デモ用: 固定値で初期化 */
    printf("点1の座標を入力 (x y): 0 0\n");
    point1.x = 0.0;
    point1.y = 0.0;
    
    printf("点2の座標を入力 (x y): 3 4\n");
    point2.x = 3.0;
    point2.y = 4.0;
    
    /* 座標の表示 */
    printf("\n");
    display_point(&point1, "点1");
    display_point(&point2, "点2");
    
    /* 2点間の距離を計算 */
    distance = calculate_distance(&point1, &point2);
    printf("2点間の距離: %.2f\n", distance);
    
    /* 中点の計算 */
    midpoint = calculate_midpoint(&point1, &point2);
    display_point(&midpoint, "\n2点の中点");
    
    /* 原点からの距離 */
    printf("\n原点からの距離:\n");
    printf("点1: %.2f\n", distance_from_origin(&point1));
    printf("点2: %.2f\n", distance_from_origin(&point2));
    
    /* 座標の移動 */
    printf("\n点1を移動します。\n");
    printf("移動量を入力 (dx dy): 1 1\n");
    dx = 1.0;
    dy = 1.0;
    
    move_point(&point1, dx, dy);
    
    printf("\n移動後の");
    display_point(&point1, "点1");
    
    /* 新しい距離の計算 */
    distance = calculate_distance(&point1, &point2);
    printf("新しい距離: %.2f\n", distance);
    
    /* 象限の判定 */
    printf("\n象限の判定:\n");
    quadrant = get_quadrant(&point1);
    printf("点1は");
    if (quadrant > 0) {
        printf("第%d象限にあります\n", quadrant);
    } else {
        printf("軸上または原点にあります\n");
    }
    
    quadrant = get_quadrant(&point2);
    printf("点2は");
    if (quadrant > 0) {
        printf("第%d象限にあります\n", quadrant);
    } else {
        printf("軸上または原点にあります\n");
    }
    
    /* 追加デモ: 複数点の管理 */
    printf("\n\n=== 複数点の管理デモ ===\n");
    
    struct Point2D points[] = {
        {1.0, 2.0},
        {-3.0, 4.0},
        {-2.0, -5.0},
        {4.0, -1.0},
        {0.0, 3.0}
    };
    int num_points = 5;
    int i, j;
    double max_distance = 0.0;
    int max_i = 0, max_j = 1;
    
    /* 全ての点を表示 */
    printf("\n登録された点:\n");
    for (i = 0; i < num_points; i++) {
        char name[20];
        sprintf(name, "点%d", i + 1);
        display_point(&points[i], name);
    }
    
    /* 最も離れた2点を見つける */
    for (i = 0; i < num_points - 1; i++) {
        for (j = i + 1; j < num_points; j++) {
            distance = calculate_distance(&points[i], &points[j]);
            if (distance > max_distance) {
                max_distance = distance;
                max_i = i;
                max_j = j;
            }
        }
    }
    
    printf("\n最も離れた2点:\n");
    printf("点%d (%.1f, %.1f) と 点%d (%.1f, %.1f)\n",
           max_i + 1, points[max_i].x, points[max_i].y,
           max_j + 1, points[max_j].x, points[max_j].y);
    printf("距離: %.2f\n", max_distance);
    
    /* 全点の重心を計算 */
    struct Point2D centroid = {0.0, 0.0};
    for (i = 0; i < num_points; i++) {
        centroid.x += points[i].x;
        centroid.y += points[i].y;
    }
    centroid.x /= num_points;
    centroid.y /= num_points;
    
    printf("\n全点の重心: (%.2f, %.2f)\n", centroid.x, centroid.y);
    
    return 0;
}

/*
実行例:
===== 2D座標計算プログラム =====

点1の座標を入力 (x y): 0 0
点2の座標を入力 (x y): 3 4

点1: (0.00, 0.00)
点2: (3.00, 4.00)
2点間の距離: 5.00

2点の中点: (1.50, 2.00)

原点からの距離:
点1: 0.00
点2: 5.00

点1を移動します。
移動量を入力 (dx dy): 1 1

移動後の点1: (1.00, 1.00)
新しい距離: 3.61

象限の判定:
点1は第1象限にあります
点2は第1象限にあります

=== 複数点の管理デモ ===

登録された点:
点1: (1.00, 2.00)
点2: (-3.00, 4.00)
点3: (-2.00, -5.00)
点4: (4.00, -1.00)
点5: (0.00, 3.00)

最も離れた2点:
点2 (-3.0, 4.0) と 点3 (-2.0, -5.0)
距離: 9.06

全点の重心: (0.00, 0.60)
*/
