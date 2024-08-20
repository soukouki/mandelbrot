

int putchar();
int printf();
int scanf();

typedef int fixed_point;

// 固定小数点数を初期化
fixed_point fp_from_int(int n) {
    return n * 10000;
}

// 整数に変換
int fp_to_int(fixed_point x) {
    return x / 10000;
}

// 固定小数点数を加算
fixed_point fp_add(fixed_point x, fixed_point y) {
    return x + y;
}

// 固定小数点数を減算
fixed_point fp_sub(fixed_point x, fixed_point y) {
    return x - y;
}

// 固定小数点数を乗算
fixed_point fp_mul(fixed_point x, fixed_point y) {
    return (x * y) / 10000;
}

// 固定小数点数を除算
fixed_point fp_div(fixed_point x, fixed_point y) {
    return (x * 10000) / y;
}

// 固定小数点数を比較（等しいか）
int fp_eq(fixed_point x, fixed_point y) {
    return x == y;
}

// 固定小数点数を比較（小さいか）
int fp_lt(fixed_point x, fixed_point y) {
    return x < y;
}

// 固定小数点数を比較（大きいか）
int fp_gt(fixed_point x, fixed_point y) {
    return x > y;
}

int char_width;
int char_height;
int max_iter;

fixed_point re_min;
fixed_point re_max;
fixed_point im_min;
fixed_point im_max;
fixed_point d_width;
fixed_point d_height;

int draw() {
    for (int y = 0; y < char_height; y++) {
        for (int x = 0; x < char_width; x++) {
            // 実部と虚部を計算
            fixed_point re = fp_add(re_min, fp_mul(fp_from_int(x), d_width));
            fixed_point im = fp_add(im_min, fp_mul(fp_from_int(y), d_height));

            fixed_point zx = fp_from_int(0);
            fixed_point zy = fp_from_int(0);
            int iter = 0;

            while (fp_add(fp_mul(zx, zx), fp_mul(zy, zy)) < fp_from_int(4) && iter < max_iter) {
                fixed_point temp = fp_add(fp_sub(fp_mul(zx, zx), fp_mul(zy, zy)), re);
                zy = fp_add(fp_mul(fp_mul(fp_from_int(2), zx), zy), im);
                zx = temp;
                iter++;
            }

            //  .,-~:;=!*#$@の12種類の文字を使って描画
            if (iter == max_iter) {
                putchar('@');
            } else if (iter > max_iter * 11 / 12) {
                putchar('#');
            } else if (iter > max_iter * 10 / 12) {
                putchar('$');
            } else if (iter > max_iter * 9 / 12) {
                putchar('*');
            } else if (iter > max_iter * 8 / 12) {
                putchar('=');
            } else if (iter > max_iter * 7 / 12) {
                putchar(';');
            } else if (iter > max_iter * 6 / 12) {
                putchar(':');
            } else if (iter > max_iter * 5 / 12) {
                putchar('~');
            } else if (iter > max_iter * 4 / 12) {
                putchar('-');
            } else if (iter > max_iter * 3 / 12) {
                putchar(',');
            } else if (iter > max_iter * 2 / 12) {
                putchar('.');
            } else {
                putchar(' ');
            }
        }
        putchar('\n');
    }
    return 0;
}

int operate() {
    printf("wasd/u(p)/d(own)/kl(inc/dec max_iter) : ");
    int c;
    c = 0;
    if(scanf("%c%*c", &c) == -1) {
        return -1;
    }
    printf("\n");
    fixed_point re_center = fp_div(fp_add(re_min, re_max), fp_from_int(2));
    fixed_point im_center = fp_div(fp_add(im_min, im_max), fp_from_int(2));
    fixed_point re_size = fp_sub(re_max, re_min);
    fixed_point im_size = fp_sub(im_max, im_min);
    fixed_point re_moving = fp_div(re_size, fp_from_int(10));
    fixed_point im_moving = fp_div(im_size, fp_from_int(10));
    if(c == 119) { // 'w'
        // 虚軸を減らす
        im_min = fp_sub(im_min, im_moving);
        im_max = fp_sub(im_max, im_moving);
    } else if(c == 97) { // 'a'
        // 実軸を減らす
        re_min = fp_sub(re_min, re_moving);
        re_max = fp_sub(re_max, re_moving);
    } else if(c == 115) { // 's'
        // 虚軸を増やす
        im_min = fp_add(im_min, im_moving);
        im_max = fp_add(im_max, im_moving);
    } else if(c == 100) { // 'd'
        // 実軸を増やす
        re_min = fp_add(re_min, re_moving);
        re_max = fp_add(re_max, re_moving);
    } else if(c == 105) { // 'i'
        // 2倍に拡大
        re_min = fp_div(fp_add(re_min, re_center), fp_from_int(2));
        re_max = fp_div(fp_add(re_max, re_center), fp_from_int(2));
        im_min = fp_div(fp_add(im_min, im_center), fp_from_int(2));
        im_max = fp_div(fp_add(im_max, im_center), fp_from_int(2));
        d_width = fp_div(d_width, fp_from_int(2));
        d_height = fp_div(d_height, fp_from_int(2));
    } else if(c == 111) { // 'o'
        // 2倍に縮小
        re_min = fp_add(re_min, fp_sub(re_min, re_center));
        re_max = fp_add(re_max, fp_sub(re_max, re_center));
        im_min = fp_add(im_min, fp_sub(im_min, im_center));
        im_max = fp_add(im_max, fp_sub(im_max, im_center));
        d_width = fp_mul(d_width, fp_from_int(2));
        d_height = fp_mul(d_height, fp_from_int(2));
    } else if(c == 107) { // 'k'
        // max_iterを増やす
        max_iter = max_iter * 2;
    } else if(c == 108) { // 'l'
        // max_iterを減らす
        max_iter = max_iter / 2;
    }
    return 0;
}

int main() {
    // 画面サイズ
    char_width = 200;
    char_height = 70;
    // char_width = 100;
    // char_height = 40;
    max_iter = 1000;
    // 描画範囲の設定 (-1.5, -1)から(0.5, 1)
    re_min = fp_div(fp_from_int(-15), fp_from_int(10));
    re_max = fp_div(fp_from_int(5), fp_from_int(10));
    im_min = fp_from_int(-1);
    im_max = fp_from_int(1);
    // 描画範囲を幅と高さで割る
    d_width = fp_div(fp_sub(re_max, re_min), fp_from_int(char_width));
    d_height = fp_div(fp_sub(im_max, im_min), fp_from_int(char_height));

    int stop = 0;
    while(stop == 0) {
        printf("%c[2J", 27);
        draw();
        printf("re_min: %d, re_max: %d, im_min: %d, im_max: %d, ", re_min, re_max, im_min, im_max);
        printf("d_width: %d, d_height: %d, max_iter: %d\n", d_width, d_height, max_iter);
        stop = operate();
    }
    return 0;
}
