/*
 * 演習9-4: 複数戻り値を持つ関数 - 解答例（C99版）
 * 
 * ポインター引数を使って複数の値を返す関数群を実装します。
 * C99の機能：//コメント、変数宣言位置の自由化、bool型、複合リテラル、designatedinit
 */
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>  /* abs()用 */

// 構造体定義（複数の値をまとめて返す別アプローチ）
typedef struct {
    int hours;
    int minutes;
    int seconds;
} Time;

typedef struct {
    double x;
    double y;
} Point;

typedef struct {
    double mean;
    double variance;
    double std_dev;
} Statistics;

// 関数プロトタイプ
// 時間変換
void seconds_to_hms(int total_seconds, int *hours, int *minutes, int *seconds);
Time seconds_to_time_struct(int total_seconds);  // C99: 構造体を返す版
void time_add(int h1, int m1, int s1, int h2, int m2, int s2, 
              int *result_h, int *result_m, int *result_s);
void time_diff(int h1, int m1, int s1, int h2, int m2, int s2, 
               int *diff_h, int *diff_m, int *diff_s);

// 座標計算
void polar_to_cartesian(double r, double theta, double *x, double *y);
Point polar_to_point(double r, double theta);  // C99: 構造体を返す版
void cartesian_to_polar(double x, double y, double *r, double *theta);
void midpoint(double x1, double y1, double x2, double y2, double *mid_x, double *mid_y);

// 統計計算
void basic_statistics(const double data[], int size, double *mean, double *variance, double *std_dev);
Statistics calculate_statistics(const double data[], int size);  // C99: 構造体を返す版
void min_max_range(const double data[], int size, double *min, double *max, double *range);
void percentiles(const double sorted_data[], int size, double *q1, double *median, double *q3);

// ヘルパー関数
void sort_doubles(double arr[], int size);
inline void swap_double(double *a, double *b);  // C99: inline関数

// 秒を時・分・秒に変換する関数
void seconds_to_hms(int total_seconds, int *hours, int *minutes, int *seconds)
{
    if (hours == NULL || minutes == NULL || seconds == NULL)
    {
        return;
    }
    
    *hours = total_seconds / 3600;
    total_seconds %= 3600;
    *minutes = total_seconds / 60;
    *seconds = total_seconds % 60;
}

// 秒をTime構造体に変換する関数（C99版）
Time seconds_to_time_struct(int total_seconds)
{
    Time result = {
        .hours = total_seconds / 3600,
        .minutes = (total_seconds % 3600) / 60,
        .seconds = total_seconds % 60
    };  // C99: designated initializer
    
    return result;
}

// 2つの時刻を加算する関数
void time_add(int h1, int m1, int s1, int h2, int m2, int s2, 
              int *result_h, int *result_m, int *result_s)
{
    if (result_h == NULL || result_m == NULL || result_s == NULL)
    {
        return;
    }
    
    int total_seconds = (h1 * 3600 + m1 * 60 + s1) + (h2 * 3600 + m2 * 60 + s2);
    seconds_to_hms(total_seconds, result_h, result_m, result_s);
}

// 2つの時刻の差を計算する関数
void time_diff(int h1, int m1, int s1, int h2, int m2, int s2, 
               int *diff_h, int *diff_m, int *diff_s)
{
    if (diff_h == NULL || diff_m == NULL || diff_s == NULL)
    {
        return;
    }
    
    int seconds1 = h1 * 3600 + m1 * 60 + s1;
    int seconds2 = h2 * 3600 + m2 * 60 + s2;
    int diff_seconds = abs(seconds1 - seconds2);  // C99: abs()関数
    
    seconds_to_hms(diff_seconds, diff_h, diff_m, diff_s);
}

// 極座標を直交座標に変換する関数
void polar_to_cartesian(double r, double theta, double *x, double *y)
{
    if (x == NULL || y == NULL)
    {
        return;
    }
    
    *x = r * cos(theta);
    *y = r * sin(theta);
}

// 極座標をPoint構造体に変換する関数（C99版）
Point polar_to_point(double r, double theta)
{
    return (Point){  // C99: 複合リテラル
        .x = r * cos(theta),
        .y = r * sin(theta)
    };
}

// 直交座標を極座標に変換する関数
void cartesian_to_polar(double x, double y, double *r, double *theta)
{
    if (r == NULL || theta == NULL)
    {
        return;
    }
    
    *r = hypot(x, y);  // C99: hypot関数（sqrt(x*x + y*y)より精度が高い）
    *theta = atan2(y, x);
}

// 2点の中点を求める関数
void midpoint(double x1, double y1, double x2, double y2, double *mid_x, double *mid_y)
{
    if (mid_x == NULL || mid_y == NULL)
    {
        return;
    }
    
    *mid_x = (x1 + x2) / 2.0;
    *mid_y = (y1 + y2) / 2.0;
}

// 基本統計量を計算する関数
void basic_statistics(const double data[], int size, double *mean, double *variance, double *std_dev)
{
    if (mean == NULL || variance == NULL || std_dev == NULL || size <= 0)
    {
        return;
    }
    
    // 平均値を計算
    double sum = 0.0;
    for (int i = 0; i < size; i++)  // C99: forループ内で変数宣言
    {
        sum += data[i];
    }
    *mean = sum / size;
    
    // 分散を計算
    double sum_sq_diff = 0.0;
    for (int i = 0; i < size; i++)
    {
        double diff = data[i] - *mean;  // C99: 使用箇所で変数宣言
        sum_sq_diff += diff * diff;
    }
    *variance = sum_sq_diff / size;
    
    // 標準偏差を計算
    *std_dev = sqrt(*variance);
}

// 統計量をStatistics構造体で返す関数（C99版）
Statistics calculate_statistics(const double data[], int size)
{
    if (size <= 0)
    {
        return (Statistics){0.0, 0.0, 0.0};  // C99: 複合リテラル
    }
    
    Statistics stats;
    
    // 平均値を計算
    double sum = 0.0;
    for (int i = 0; i < size; i++)
    {
        sum += data[i];
    }
    stats.mean = sum / size;
    
    // 分散を計算
    double sum_sq_diff = 0.0;
    for (int i = 0; i < size; i++)
    {
        double diff = data[i] - stats.mean;
        sum_sq_diff += diff * diff;
    }
    stats.variance = sum_sq_diff / size;
    
    // 標準偏差を計算
    stats.std_dev = sqrt(stats.variance);
    
    return stats;
}

// 最小値、最大値、範囲を求める関数
void min_max_range(const double data[], int size, double *min, double *max, double *range)
{
    if (min == NULL || max == NULL || range == NULL || size <= 0)
    {
        return;
    }
    
    *min = *max = data[0];
    
    for (int i = 1; i < size; i++)  // C99: forループ内で変数宣言
    {
        if (data[i] < *min)
        {
            *min = data[i];
        }
        if (data[i] > *max)
        {
            *max = data[i];
        }
    }
    
    *range = *max - *min;
}

// パーセンタイル（四分位数）を計算する関数
void percentiles(const double sorted_data[], int size, double *q1, double *median, double *q3)
{
    if (q1 == NULL || median == NULL || q3 == NULL || size <= 0)
    {
        return;
    }
    
    // 中央値（第2四分位数）
    if (size % 2 == 0)
    {
        *median = (sorted_data[size/2 - 1] + sorted_data[size/2]) / 2.0;
    }
    else
    {
        *median = sorted_data[size/2];
    }
    
    // 第1四分位数
    int q1_pos = size / 4;
    if (size % 4 == 0)
    {
        *q1 = (sorted_data[q1_pos - 1] + sorted_data[q1_pos]) / 2.0;
    }
    else
    {
        *q1 = sorted_data[q1_pos];
    }
    
    // 第3四分位数
    int q3_pos = (3 * size) / 4;
    if ((3 * size) % 4 == 0)
    {
        *q3 = (sorted_data[q3_pos - 1] + sorted_data[q3_pos]) / 2.0;
    }
    else
    {
        *q3 = sorted_data[q3_pos];
    }
}

// 配列をソートするヘルパー関数
void sort_doubles(double arr[], int size)
{
    bool swapped;  // C99: bool型
    
    for (int i = 0; i < size - 1; i++)
    {
        swapped = false;
        
        for (int j = 0; j < size - 1 - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap_double(&arr[j], &arr[j + 1]);
                swapped = true;
            }
        }
        
        // 交換がなければソート完了
        if (!swapped)
        {
            break;
        }
    }
}

// 2つの要素を交換するヘルパー関数
inline void swap_double(double *a, double *b)  // C99: inline関数
{
    double temp = *a;
    *a = *b;
    *b = temp;
}

// メイン関数 - テスト用
int main(void)
{
    printf("=== 複数戻り値を持つ関数のテスト（C99版） ===\n\n");
    
    // 時間変換のテスト
    printf("=== 時間変換 ===\n");
    int hours, minutes, seconds;
    
    seconds_to_hms(7265, &hours, &minutes, &seconds);
    printf("7265秒 = %d時間 %d分 %d秒\n", hours, minutes, seconds);
    
    // C99: 構造体を返す版のテスト
    Time time = seconds_to_time_struct(7265);
    printf("構造体版: %d時間 %d分 %d秒\n", time.hours, time.minutes, time.seconds);
    
    int h1 = 2, m1 = 45, s1 = 30;
    int h2 = 1, m2 = 50, s2 = 40;
    int result_h, result_m, result_s;
    
    time_add(h1, m1, s1, h2, m2, s2, &result_h, &result_m, &result_s);
    printf("%d:%02d:%02d + %d:%02d:%02d = %d:%02d:%02d\n", 
           h1, m1, s1, h2, m2, s2, result_h, result_m, result_s);
    
    time_diff(h1, m1, s1, h2, m2, s2, &result_h, &result_m, &result_s);
    printf("%d:%02d:%02d - %d:%02d:%02d = %d:%02d:%02d\n\n", 
           h1, m1, s1, h2, m2, s2, result_h, result_m, result_s);
    
    // 座標変換のテスト
    printf("=== 座標変換 ===\n");
    double r = 5.0, theta = M_PI / 4;  // 45度
    double x, y;
    
    polar_to_cartesian(r, theta, &x, &y);
    printf("極座標(r=%.2f, θ=%.2f) → 直交座標(x=%.2f, y=%.2f)\n", 
           r, theta, x, y);
    
    // C99: 構造体を返す版のテスト
    Point point = polar_to_point(r, theta);
    printf("構造体版: (x=%.2f, y=%.2f)\n", point.x, point.y);
    
    double x2 = 3.0, y2 = 4.0;
    double r2, theta2;
    cartesian_to_polar(x2, y2, &r2, &theta2);
    printf("直交座標(x=%.2f, y=%.2f) → 極座標(r=%.2f, θ=%.2f)\n", 
           x2, y2, r2, theta2);
    
    double mid_x, mid_y;
    midpoint(0, 0, 10, 10, &mid_x, &mid_y);
    printf("(0, 0)と(10, 10)の中点: (%.2f, %.2f)\n\n", mid_x, mid_y);
    
    // 統計計算のテスト
    printf("=== 統計計算 ===\n");
    double data[] = {85.5, 90.2, 78.3, 92.1, 88.7, 79.5, 91.3, 86.4, 83.2, 87.6};
    int size = sizeof(data) / sizeof(data[0]);
    
    // ポインター版
    double mean, variance, std_dev;
    basic_statistics(data, size, &mean, &variance, &std_dev);
    
    printf("データ: ");
    for (int i = 0; i < size; i++)  // C99: forループ内で変数宣言
    {
        printf("%.1f ", data[i]);
    }
    printf("\n");
    printf("ポインター版 - 平均: %.2f, 分散: %.2f, 標準偏差: %.2f\n", 
           mean, variance, std_dev);
    
    // C99: 構造体を返す版
    Statistics stats = calculate_statistics(data, size);
    printf("構造体版 - 平均: %.2f, 分散: %.2f, 標準偏差: %.2f\n", 
           stats.mean, stats.variance, stats.std_dev);
    
    double min, max, range;
    min_max_range(data, size, &min, &max, &range);
    printf("最小値: %.2f, 最大値: %.2f, 範囲: %.2f\n", min, max, range);
    
    // データをソートしてパーセンタイル計算
    double sorted_data[10];
    for (int i = 0; i < size; i++)
    {
        sorted_data[i] = data[i];
    }
    sort_doubles(sorted_data, size);
    
    double q1, median, q3;
    percentiles(sorted_data, size, &q1, &median, &q3);
    printf("第1四分位数: %.2f, 中央値: %.2f, 第3四分位数: %.2f\n", q1, median, q3);
    
    // C99: 複合リテラルを使ったテスト
    printf("\n=== 複合リテラルのテスト ===\n");
    Statistics instant_stats = calculate_statistics(
        (double[]){1.0, 2.0, 3.0, 4.0, 5.0}, 5
    );  // C99: 複合リテラル
    printf("即席配列の統計: 平均=%.2f, 分散=%.2f, 標準偏差=%.2f\n",
           instant_stats.mean, instant_stats.variance, instant_stats.std_dev);
    
    return 0;
}