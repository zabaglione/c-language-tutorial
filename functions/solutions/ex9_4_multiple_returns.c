/*
 * 演習9-4: 複数戻り値を持つ関数 - 解答例
 * 
 * ポインター引数を使って複数の値を返す関数群を実装します。
 */
#include <stdio.h>
#include <math.h>

/* 関数プロトタイプ */
/* 時間変換 */
void seconds_to_hms(int total_seconds, int *hours, int *minutes, int *seconds);
void time_add(int h1, int m1, int s1, int h2, int m2, int s2, 
              int *result_h, int *result_m, int *result_s);
void time_diff(int h1, int m1, int s1, int h2, int m2, int s2, 
               int *diff_h, int *diff_m, int *diff_s);

/* 座標計算 */
void polar_to_cartesian(double r, double theta, double *x, double *y);
void cartesian_to_polar(double x, double y, double *r, double *theta);
void midpoint(double x1, double y1, double x2, double y2, double *mid_x, double *mid_y);

/* 統計計算 */
void basic_statistics(double data[], int size, double *mean, double *variance, double *std_dev);
void min_max_range(double data[], int size, double *min, double *max, double *range);
void percentiles(double sorted_data[], int size, double *q1, double *median, double *q3);

/* ヘルパー関数 */
void sort_doubles(double arr[], int size);
void swap_double(double *a, double *b);

/* 秒を時・分・秒に変換する関数 */
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

/* 2つの時刻を加算する関数 */
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

/* 2つの時刻の差を計算する関数 */
void time_diff(int h1, int m1, int s1, int h2, int m2, int s2, 
               int *diff_h, int *diff_m, int *diff_s)
{
    if (diff_h == NULL || diff_m == NULL || diff_s == NULL)
    {
        return;
    }
    
    int seconds1 = h1 * 3600 + m1 * 60 + s1;
    int seconds2 = h2 * 3600 + m2 * 60 + s2;
    int diff_seconds = seconds1 - seconds2;
    
    /* 負の場合は正に変換 */
    if (diff_seconds < 0)
    {
        diff_seconds = -diff_seconds;
    }
    
    seconds_to_hms(diff_seconds, diff_h, diff_m, diff_s);
}

/* 極座標を直交座標に変換する関数 */
void polar_to_cartesian(double r, double theta, double *x, double *y)
{
    if (x == NULL || y == NULL)
    {
        return;
    }
    
    *x = r * cos(theta);
    *y = r * sin(theta);
}

/* 直交座標を極座標に変換する関数 */
void cartesian_to_polar(double x, double y, double *r, double *theta)
{
    if (r == NULL || theta == NULL)
    {
        return;
    }
    
    *r = sqrt(x * x + y * y);
    *theta = atan2(y, x);
}

/* 2点の中点を求める関数 */
void midpoint(double x1, double y1, double x2, double y2, double *mid_x, double *mid_y)
{
    if (mid_x == NULL || mid_y == NULL)
    {
        return;
    }
    
    *mid_x = (x1 + x2) / 2.0;
    *mid_y = (y1 + y2) / 2.0;
}

/* 基本統計量を計算する関数 */
void basic_statistics(double data[], int size, double *mean, double *variance, double *std_dev)
{
    if (mean == NULL || variance == NULL || std_dev == NULL || size <= 0)
    {
        return;
    }
    
    /* 平均値を計算 */
    double sum = 0.0;
    int i;
    for (i = 0; i < size; i++)
    {
        sum += data[i];
    }
    *mean = sum / size;
    
    /* 分散を計算 */
    double sum_sq_diff = 0.0;
    for (i = 0; i < size; i++)
    {
        double diff = data[i] - *mean;
        sum_sq_diff += diff * diff;
    }
    *variance = sum_sq_diff / size;
    
    /* 標準偏差を計算 */
    *std_dev = sqrt(*variance);
}

/* 最小値、最大値、範囲を求める関数 */
void min_max_range(double data[], int size, double *min, double *max, double *range)
{
    if (min == NULL || max == NULL || range == NULL || size <= 0)
    {
        return;
    }
    
    *min = data[0];
    *max = data[0];
    
    int i;
    for (i = 1; i < size; i++)
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

/* パーセンタイル（四分位数）を計算する関数 */
void percentiles(double sorted_data[], int size, double *q1, double *median, double *q3)
{
    if (q1 == NULL || median == NULL || q3 == NULL || size <= 0)
    {
        return;
    }
    
    /* 中央値（第2四分位数） */
    if (size % 2 == 0)
    {
        *median = (sorted_data[size/2 - 1] + sorted_data[size/2]) / 2.0;
    }
    else
    {
        *median = sorted_data[size/2];
    }
    
    /* 第1四分位数 */
    int q1_pos = size / 4;
    if (size % 4 == 0)
    {
        *q1 = (sorted_data[q1_pos - 1] + sorted_data[q1_pos]) / 2.0;
    }
    else
    {
        *q1 = sorted_data[q1_pos];
    }
    
    /* 第3四分位数 */
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

/* 配列をソートするヘルパー関数 */
void sort_doubles(double arr[], int size)
{
    int i, j;
    for (i = 0; i < size - 1; i++)
    {
        for (j = 0; j < size - 1 - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap_double(&arr[j], &arr[j + 1]);
            }
        }
    }
}

/* 2つの要素を交換するヘルパー関数 */
void swap_double(double *a, double *b)
{
    double temp = *a;
    *a = *b;
    *b = temp;
}

/* メイン関数 - テスト用 */
int main(void)
{
    printf("=== 複数戻り値を持つ関数のテスト ===\n\n");
    
    /* 時間変換のテスト */
    printf("=== 時間変換 ===\n");
    int hours, minutes, seconds;
    
    seconds_to_hms(7265, &hours, &minutes, &seconds);
    printf("7265秒 = %d時間 %d分 %d秒\n", hours, minutes, seconds);
    
    int h1 = 2, m1 = 45, s1 = 30;
    int h2 = 1, m2 = 50, s2 = 40;
    int result_h, result_m, result_s;
    
    time_add(h1, m1, s1, h2, m2, s2, &result_h, &result_m, &result_s);
    printf("%d:%02d:%02d + %d:%02d:%02d = %d:%02d:%02d\n", 
           h1, m1, s1, h2, m2, s2, result_h, result_m, result_s);
    
    time_diff(h1, m1, s1, h2, m2, s2, &result_h, &result_m, &result_s);
    printf("%d:%02d:%02d - %d:%02d:%02d = %d:%02d:%02d\n\n", 
           h1, m1, s1, h2, m2, s2, result_h, result_m, result_s);
    
    /* 座標変換のテスト */
    printf("=== 座標変換 ===\n");
    double r = 5.0, theta = M_PI / 4;  /* 45度 */
    double x, y;
    
    polar_to_cartesian(r, theta, &x, &y);
    printf("極座標(r=%.2f, θ=%.2f) → 直交座標(x=%.2f, y=%.2f)\n", 
           r, theta, x, y);
    
    double x2 = 3.0, y2 = 4.0;
    double r2, theta2;
    cartesian_to_polar(x2, y2, &r2, &theta2);
    printf("直交座標(x=%.2f, y=%.2f) → 極座標(r=%.2f, θ=%.2f)\n", 
           x2, y2, r2, theta2);
    
    double mid_x, mid_y;
    midpoint(0, 0, 10, 10, &mid_x, &mid_y);
    printf("(0, 0)と(10, 10)の中点: (%.2f, %.2f)\n\n", mid_x, mid_y);
    
    /* 統計計算のテスト */
    printf("=== 統計計算 ===\n");
    double data[] = {85.5, 90.2, 78.3, 92.1, 88.7, 79.5, 91.3, 86.4, 83.2, 87.6};
    int size = sizeof(data) / sizeof(data[0]);
    double mean, variance, std_dev;
    
    basic_statistics(data, size, &mean, &variance, &std_dev);
    printf("データ: ");
    int i;
    for (i = 0; i < size; i++)
    {
        printf("%.1f ", data[i]);
    }
    printf("\n");
    printf("平均: %.2f, 分散: %.2f, 標準偏差: %.2f\n", mean, variance, std_dev);
    
    double min, max, range;
    min_max_range(data, size, &min, &max, &range);
    printf("最小値: %.2f, 最大値: %.2f, 範囲: %.2f\n", min, max, range);
    
    /* データをソートしてパーセンタイル計算 */
    double sorted_data[10];
    for (i = 0; i < size; i++)
    {
        sorted_data[i] = data[i];
    }
    sort_doubles(sorted_data, size);
    
    double q1, median, q3;
    percentiles(sorted_data, size, &q1, &median, &q3);
    printf("第1四分位数: %.2f, 中央値: %.2f, 第3四分位数: %.2f\n", q1, median, q3);
    
    return 0;
}