# fract-ol

`fract-ol`は、[MiniLibX](https://github.com/42Paris/minilibx-linux)グラフィックライブラリを使用して、美しいフラクタル図形をリアルタイムで探索できるインタラクティブなプログラムです。
このプロジェクトは、複素数平面の可視化、イベント処理、そしてグラフィックスプログラミングの基礎を学ぶことを目的としています。

## ✨ 機能

このプログラムには、以下の機能が実装されています。

  * **多彩なフラクタル**: 3種類の異なるフラクタル（マンデルブロ集合、ジュリア集合、バーニングシップ）を描画できます。
  * **無限ズーム**: マウスホイールを使って、フラクタルの細部を無限に拡大・縮小できます。
  * **マウス追従ズーム**: ズームは常にマウスカーソルの位置を中心に行われます。
  * **視点移動**: 矢印キーで表示領域を自由に移動できます。
  * **インタラクティブな色彩**: `C`キーを押すことで、サイケデリックなカラーパレットを動的に変更できます。
  * **ビューのリセット**: `R`キーでいつでも初期状態のビューに戻れます。

## Fractals

描画可能なフラクタルは以下の通りです。

1.  **Mandelbrot**: `Z = Z^2 + C` の漸化式で、`C`を変化させたときに`Z`が発散しない点の集合。
2.  **Julia**: 上記と同じ数式で、`C`を固定値とし、初期値`Z`を変化させる。`C`の値によって全く異なる模様が生まれます。
3.  **Burning Ship**: マンデルブロ集合の計算式の変形で、複素数の絶対値を取ることで、炎や船のような独特の形状を描きます。

## 🛠️ コンパイル

プロジェクトをコンパイルするには、`make`コマンドを実行してください。

```bash
make
```

これにより、`fractol`という名前の実行ファイルが生成されます。

## 🚀 使い方

以下のコマンドでプログラムを起動します。

```bash
./fractol <fractal_name> [param1] [param2]
```

### 使用例

  * **マンデルブロ集合を表示:**

    ```bash
    ./fractol mandelbrot
    ```

  * **バーニングシップを表示:**

    ```bash
    ./fractol burning_ship
    ```

  * **ジュリア集合を表示 (パラメータ指定):**
    ジュリア集合は、実部と虚部の2つのパラメータを取ります。

    ```bash
    # おすすめのパラメータ例
    ./fractol julia -0.7 0.27015
    ./fractol julia -0.8 0.156
    ```

引数が無効な場合や指定されなかった場合は、使い方が表示されます。

## 🕹️ 操作方法

| キー / マウス操作 | アクション                     |
| :---------------- | :----------------------------- |
| `マウスホイール`  | マウス位置を中心にズームイン/アウト |
| `↑` `↓` `←` `→`    | 視点の移動                     |
| `C`               | カラーパレットのシフト         |
| `R`               | 視点と色をリセット             |
| `ESC`             | プログラムを終了               |

## 📁 ディレクトリ構成

プロジェクトは、役割ごとにファイルを分離したクリーンな構成になっています。

```
.
├── Makefile
├── README.md
├── include
│   └── fractol.h
├── minilibx-linux
└── src
    ├── event_handlers.c
    ├── fractal_calculations.c
    ├── init.c
    ├── main.c
    ├── render.c
    └── utils.c
```

## 🔢 フラクタルの数学的背景

このプログラムで描画されるフラクタルは、複素数平面上での単純な漸化式の反復計算によって生まれます。ピクセルの一つ一つが複素数平面上の点に対応しており、その点が特定の計算ルールに従ったときに発散するかどうかで色が決まります。

### 1\. マンデルブロ集合 (Mandelbrot Set)

マンデルブロ集合は、以下の漸化式によって定義されます。

![alt text](image.png)

この式の各要素は以下の通りです。

  * **C**: 複素数平面上の点の座標。`render.c`でピクセルごとに計算され、この点 `C` がマンデルブロ集合に属するかどうかを判定します。
  * **Z**: 計算のたびに値が変化する複素数。初期値は常にZo=0です。
この計算を何度も繰り返したとき、`Z` の値が無限に大きくならずに、ある範囲に留まり続けるような点 `C` の集まりがマンデルブロ集合です。プログラムでは、`Z` の原点からの距離の2乗が`4.0`を超えた時点で「発散した」とみなし、その時点での繰り返し回数 `i` を返します。

### 2\. ジュリア集合 (Julia Set)

ジュリア集合は、マンデルブロ集合と全く同じ漸化式から生まれます。

![alt text](image-1.png)

しかし、`Z`と`C`の役割がマンデルブロ集合とは逆になります。

  * **Z**: 複素数平面上の点の座標。各ピクセルの位置が、計算の初期値 Zo=0 となります。
  * **C**: プログラム起動時に引数として与えられる**固定の複素数**。

この定数`C`の値を少し変えるだけで、全く異なる形の美しい図形が生まれます。これが、ジュリア集合が「パラメータによって無限のバリエーションを持つ」と言われる理由です。

### 3\. バーニングシップ (Burning Ship)

バーニングシップは、マンデルブロ集合の計算式を少し変形させたものです。基本的な構造は同じですが、`Z`の2乗を計算する際に、`Z`の実部と虚部の**絶対値**を取る点が異なります。

![alt text](image-2.png)

コード上では、虚部の計算が以下のように実装されています。

`z.im = 2.0 * fabs(z.re) * fabs(z.im) + c.im;`

`fabs()`は浮動小数点数の絶対値を取る関数です。このわずかな変更により、複素数平面の対称性が崩れ、まるで炎を上げて沈んでいく帆船のような、独特で複雑な形状が生み出されます。

##  かんたんに言うと

### **全体の流れ：起動から終了まで**

このプログラムは、大きく分けて**「準備」**、**「描画」**、そして**「操作待機」**の3つのフェーズで動いています。

#### **1. 準備フェーズ（起動時） 🏗️**
プログラムを起動すると、まず以下の準備が一気に行われます。

* **引数のチェック (`main.c`)**: `./fractol mandelbrot` のように、正しい引数が与えられているかを確認します。もし不正な場合は、使い方を表示して終了します。
* **初期化 (`init.c`)**:
    * グラフィックライブラリ(MiniLibX)を起動し、ウィンドウと、絵を描くための「キャンバス」（イメージ）を用意します。
    * ズーム率や表示位置、色などの設定をすべて初期状態に戻します。
* **イベントの予約 (`init.c`)**: 「もしキーが押されたらこの関数を呼んでね」「マウスホイールが動いたらこの関数を呼んでね」といった**予約** (`mlx_hook`) を行い、ユーザーの操作に対応できるようにします。

#### **2. 初回描画フェーズ 🎨**
準備が整うと、最初のフラクタル画像を描画します。

* **全ピクセルを走査 (`render.c`)**:
    * `fractol_render`関数が、画面の左上から右下まで、**ピクセルを一つずつ**順番に見ていきます。
* **計算と色付け (`fractols.c`, `render.c`)**:
    * 各ピクセルの位置を、フラクタルを計算するための「複素数」に変換します。
    * その複素数を使い、`mandelbrot`などの関数で数学的な計算を行います。
    * 計算結果（発散するまでの速さ）に応じて、`put_color`関数がそのピクセルに塗る色を決定します。
* **表示**:
    * すべてのピクセルの色が決まったら、完成した「キャンバス」をウィンドウに表示します。

#### **3. 操作待機フェーズ（イベントループ） 🔄**
初回描画が終わると、プログラムは`mlx_loop`関数によって**無限ループ**に入り、ひたすらユーザーの操作を待ち続けます。

* **イベント発生**: ユーザーが矢印キーを押したり、マウスホイールを回したりします。
* **担当関数を呼び出し (`events.c`)**: `mlx_loop`がイベントを検知し、準備フェーズで予約しておいた担当の関数（`fractol_handle_key`など）を呼び出します。
* **状態の更新**: 呼び出された関数は、ズーム率や表示位置などの値を変更します。
* **再描画**: 状態が変わったので、**再び描画フェーズ（ステップ2）が実行**され、新しい状態で画面が更新されます。
* **待機に戻る**: 再描画が終わると、プログラムは再び操作待機状態に戻ります。

この**「待機 → 操作 → 更新 → 再描画」**のループが、ユーザーが`ESC`キーを押すか、ウィンドウを閉じるまで無限に繰り返されます。最後に`fractol_close_window`が呼ばれて、後片付けをしてからプログラムは完全に終了します。

## 💡 コード解説

### `include/fractol.h`
プロジェクト全体の**設計図**となるヘッダファイルです。
* `t_fractol`構造体を定義し、プログラムの状態（ズーム率、オフセット、色など）を管理します。
* キーコードやウィンドウサイズなどの定数を定義します。
* プロジェクト全体で使用される関数のプロトタイプ宣言をまとめ、異なるファイル間の連携を可能にします。
#### **イベントとキーコードの定数**
```c
/* X11 Event constants (defined directly to avoid header dependency) */
# define KEY_PRESS 2
# define BUTTON_PRESS 4
// ...
/* X11 Key codes (defined directly to avoid header dependency) */
# define ESC_KEY 65307
```
  * **由来**: これらの数字は、MiniLibXが内部で使用している**X Window System (X11)** というグラフィックシステムの標準ヘッダファイル（`X11/X.h`や`X11/keysym.h`）で定義されている値です。
  * **なぜ直接定義するのか**: 本来であれば`#include <X11/X.h>`のようにしてこれらの定数を読み込みますが、X11のヘッダファイルは非常に巨大で、不要な情報も多く含まれています。そこで、このプロジェクトで**必要な定数だけを直接書き出す**ことで、コンパイルを速くし、依存関係をシンプルに保つという意図があります。
      * `KEY_PRESS 2`: キーボードのキーが押されたイベントを示します。
      * `BUTTON_PRESS 4`: マウスのボタンが押されたイベントを示します。
      * `MOTION_NOTIFY 6`: マウスカーソルが移動したイベントを示します。
      * `DESTROY_NOTIFY 17`: ウィンドウが閉じられようとしているイベントを示します。
      * `ESC_KEY 65307`: `ESC`キーに対応するキーコード（keysym）です。
      * `LEFT_KEY 65361` から `DOWN_KEY 65364`: それぞれ左、右、上、下の矢印キーに対応するキーコードです。
#### **プログラム設定の定数**
```c
# define WIDTH 800
# define HEIGHT 800
# define MAX_ITER 100
```
これらはプログラムの挙動を制御する設定値です。
  * `WIDTH`, `HEIGHT`: 生成されるウィンドウの幅と高さを定義します。
  * `MAX_ITER`: フラクタルの計算を何回繰り返すかの最大値です。この値を大きくすると描画が精細になりますが、計算に時間がかかります。
#### **便利な別名とマウスコード**
```c
# define ESC ESC_KEY
// ...
# define ZOOM_IN 4
# define ZOOM_OUT 5
```
これらは、既存の定数に別名を付けたり、特定の操作に意味を持たせたりするためのものです。
  * `ESC`, `LEFT`, `RIGHT`, `UP`, `DOWN`: X11のキーコードに、より短く直感的な別名を付けています。これにより、イベント処理のコードが読みやすくなります。
  * `ZOOM_IN 4`, `ZOOM_OUT 5`: X11では、マウスホイールのスクロールもボタンプレスとして扱われます。`4`がホイールの上スクロール、`5`が下スクロールに対応する、標準的なボタンコードです。

### `main.c`
プログラムの**エントリーポイント**です。以下の役割を担います。
* 起動時のコマンドライン引数を検証し、表示するフラクタルの種類を決定します。
* グラフィック環境の初期化 (`fractol_init`) を呼び出します。
* イベントフックを設定 (`setup_hooks`) します。
* 最初の描画 (`fractol_render`) を行い、`mlx_loop`でイベントの待機ループを開始します。
* `int main(int argc, char **argv)`
    * **目的**: プログラム全体の実行フローを管理するエントリーポイント。
    * **処理**:
        1.  `validate_args`を呼び出し、コマンドライン引数が正しいか検証します。
        2.  `init_fractol`を呼び出し、ウィンドウやイメージ、各種変数を初期化します。
        3.  Julia集合の場合、引数で渡された値を`t_fractol`構造体に格納します。
        4.  `setup_hooks`を呼び出し、キーボードやマウスのイベントハンドラを登録します。
        5.  `render_fractol`で初期画面を描画し、`mlx_loop`でイベント待機状態に入ります。
    #### mlx_loop
    ```c
    mlx_loop(f.mlx);
    - イベントが発生するのを待ち続けます。（イベント待機）
    - イベントが発生すると、そのイベントを検知し、対応するイベントハンドラ関数を呼び出す。
    ```
        
### `src/init.c`
**初期化処理**を専門に行うファイルです。
* MiniLibXライブラリを初期化し、ウィンドウと描画用のイメージを作成します。
* `t_fractol`構造体の各変数をデフォルト値に設定します。
* `void init_fractol(t_fractol *f, int type)`
    * **目的**: `t_fractol`構造体とMiniLibX環境を初期化する。
    * **処理**:
        1.  `mlx_init`でグラフィックサーバーとの接続を確立します。
        2.  `mlx_new_window`と`mlx_new_image`でウィンドウと描画領域を作成します。
        3.  `mlx_get_data_addr`でイメージのメモリ情報を取得します。
        4.  ズーム率、オフセット、最大反復回数、ジュリアの初期パラメータなど、`t_fractol`構造体のメンバ変数をデフォルト値に設定します。
    #### fractol_init
    ```c
    void	fractol_init(t_fractol *f, int type)
    {
      //グラフィックシステムとの接続を確立
      f->mlx = mlx_init();
      //指定されたサイズ (WIDTH, HEIGHT) とタイトル ("Fractol") を持つ新しいウィンドウを画面に作成
      f->win = mlx_new_window(f->mlx, WIDTH, HEIGHT, "Fractol");
      //イメージバッファをメモリ上に作成。ピクセルはまずこのイメージに描かれ、最後にまとめてウィンドウに表示
      f->img = mlx_new_image(f->mlx, WIDTH, HEIGHT);
      //put_pixel関数で直接ピクセルデータを書き込むため、作成したイメージバッファの、メモリ上の生のアドレス情報を取得
      f->addr = mlx_get_data_addr(f->img, &f->bits_per_pixel,&f->line_length, &f->endian);
      f->zoom = 1.0;//ズーム倍率を等倍の1.0に設定
      f->offset_x = 0.0;//視点の中心を原点 (0,0) に設定
      f->offset_y = 0.0;//視点の中心を原点 (0,0) に設定
      f->max_iter = MAX_ITER;//計算の最大繰り返し回数設定
      f->color_shift = 0;//色のシフト量を0にリセット
      f->fractol_type = type;//フラクタルの種類を保存
      f->julia_c.re = -0.7;//ジュリア集合の有名なデフォルト値を設定
      f->julia_c.im = 0.27015;//ジュリア集合の有名なデフォルト値を設定
      f->mouse_x = WIDTH / 2;//マウスカーソルの位置の初期値を、画面の中央に設定
      <!-- f->mouse_y = HEIGHT / 2;//マウスカーソルの位置の初期値を、画面の中央に設定 
    }
    ```
    #### setup_hooks
    ```c
    void	setup_hooks(t_fractol *f)
    {
      mlx_hook(f->win, KEY_PRESS, KEY_PRESS_MASK, fractol_handle_key, f);
      //...
    }
    - mlx_hook(ウィンドウ, イベントの種類, マスク, 呼び出す関数, 関数に渡す情報);
    予約内容: 「ウィンドウ上でキーボードのキーが押されたら (KEY_PRESS)、fractol_handle_key関数を呼び出してください。」
    結果: ユーザーが矢印キーやESCキーなどを押すと、fractol_handle_key関数が実行され、視点の移動やプログラムの終了といった処理が行われます。
    ```

### `src/fractal_calculations.c`
フラクタルの**数学的な計算**の心臓部です。
* `mandelbrot`、`julia`、`burning_ship`といった各種フラクタルの漸化式を計算します。
* 複素数平面上の特定の点について、計算が発散するまでの繰り返し回数を返します。
* `int mandelbrot(t_complex c, int max_iter)`
    * **目的**: 点`c`がマンデルブロ集合に属するか判定する。
    * **処理**: 複素数`z`を0で初期化し、`z = z^2 + c`の計算を`max_iter`回繰り返します。途中で`z`の絶対値が2（2乗で4）を超えたら、その時点の繰り返し回数を返します。
    #### mandelbrot
    ```c
    int	mandelbrot(t_complex c, int max_iter)
    {
      //...
      double		escape;
      //...
      z.re = 0.0;
      z.im = 0.0;
      i = 0;
      while (i < max_iter)
      {
        escape = get_escape_value(z);
        if (escape > 4.0)//発散したとみなしてループを終了
          return (i);
        temp = z.re * z.re - z.im * z.im + c.re;
        z.im = 2.0 * z.re * z.im + c.im;
        z.re = temp;
        i++;
      }
      return (max_iter);
    }

    - z.re * z.re - z.im * z.im + c.re
    - 2.0 * z.re * z.im + c.im

    Zn+1 = Zn² + C

    Zn = x + yi
    x = z.re
    y = z.im
    Zn = z.re + Z.im i

    C = a + bi
    a = c.re
    b = c.im
    C = c.re + b.im i

    新しいx + 新しいyi = (x + yi)² + (a + bi) となる
    新しいx.re + 新しz.im i = (x.re + z.im i)² + (c.re + c.im i) となる

    Zn² = (x + yi)2
        = (x + yi) * (x + yi)
        = x² + xyi + yix + (yi)²
        = x² + 2xyi + y²i²
        i² = -1 なので
        = x² + 2xyi - y²
        = (x² - y²) + (2xy)i

    Zn² + C = ((x² - y²) + (2xy)i ) + (a + bi)
            = (x² - y² + a) + (2xy + b)i

    Zn+1 = (x² - y² + a) + (2xy + b)i

    新しい実部: x² - y² + a
    新しい虚部: 2xy + b

    temp = x² - y² + a
    temp = z.re * z.re - z.im * z.im + c.re;//完成

    z.im = 2xy + b
    z.im = 2.0 * z.re * z.im + c.im;//完成

    なぜ temp 変数が必要か？
    z.re = z.re * z.re - z.im * z.im + c.re; // ここで z.re が更新されてしまう
    z.im = 2.0 * z.re * z.im + c.im;         // この計算で使う z.re は、更新後の新しい値になってしまう
    z.imの計算には、更新前の古い z.reの値が必要
    ```

* `int julia(t_complex z, t_complex c, int max_iter)`
    * **目的**: 点`z`が、定数`c`から生成されるジュリア集合に属するか判定する。
    * **処理**: 計算ロジックはマンデルブロと同一ですが、初期値の`z`がピクセルの座標、`c`が定数である点が異なります。
    #### julia
    ```c
    int	julia(t_complex c, t_complex z, int max_iter)
    {
      //...
      double	escape;
      i = 0;
      while (i < max_iter)
      {
        escape = get_escape_value(z);
        if (escape > 4.0)
          return (i);
        temp = z.re * z.re - z.im * z.im + c.re;
        z.im = 2.0 * z.re * z.im + c.im;
        z.re = temp;
        i++;
      }
      return (max_iter);
    }
    - プログラムはmandelbrot関数と全く同じで、引数として渡されるzとcの役割
    - render_pixel関数が引数を渡すときにマンデルブロ関数への引数の渡し方とジュリア関数への引数の渡し方を反転させて渡している。
    iter = mandelbrot(c, f->max_iter);//c = c (Z = 0)
    iter = julia(f->julia_c, c, f->max_iter);//c = Zo, f->julia_c = c
    ```

* `int burning_ship(t_complex c, int max_iter)`
    * **目的**: 点`c`がバーニングシップ集合に属するか判定する。
    * **処理**: `z = z^2 + c`の計算時に、`z`の実部と虚部の**絶対値**を取ってから2乗の計算を行います。この変更が独特の形状を生み出します。
    #### burning_ship
    ```c
    int	burning_ship(t_complex c, int max_iter)
    {
      //...
      double		escape;
      z.re = 0.0;
      z.im = 0.0;
      i = 0;
      while (i < max_iter)
      {
        escape = get_escape_value(z);
        if (escape > 4.0)
          return (i);
        temp = z.re * z.re - z.im * z.im + c.re;
        z.im = 2.0 * fabs(z.re) * fabs(z.im) + c.im;
        z.re = temp;
        i++;
      }
      return (max_iter);
    }
    - 計算の途中で絶対値を取る
    z.im = 2.0 * fabs(z.re) * fabs(z.im) + c.im;
    計算中の複素数 z がどの象限にあっても、常に第1象限にあるかのように扱われるため、図形の対称性が崩れる

    ```

    #### get_escape_value
    ```c
    static double	get_escape_value(t_complex z)
    {
      return (z.re * z.re + z.im * z.im);
    }
    - 計算の効率を上げるための工夫
    - 数学的には、この関数は複素数 z の原点(0,0)からの距離の2乗を計算しています。
    - マンデルブロ集合の計算では、「Zの原点からの距離が2を超えたか」を判定する必要があります。
    正確な比較  : √(z.re² + z.im²) > 2
    効率的な比較: z.re² + z.im² > 4
    - この二つの式は数学的に同じだが、コンピュータにとって平方根の計算は非常に負荷が高い
    ```

### `src/render.c`
**描画処理**を担当します。
* ウィンドウのすべてのピクセルをスキャンし、各ピクセルに対応する複素数を計算します。
* `fractal_calculations.c`の関数を呼び出して得られた繰り返し回数に基づき、ピクセルの色を決定します。
* 最終的なイメージをウィンドウに表示します。
* `void render_fractol(t_fractol *f)`
    * **目的**: 現在の`t_fractol`の状態に基づいてフラクタルを再描画する。
    * **処理**:
        1.  `y`と`x`の二重ループで、ウィンドウの全ピクセルをスキャンします。
        2.  各ピクセル`(x, y)`の座標を、現在のズーム率とオフセットを考慮して複素数`c`に変換します。
        3.  `render_pixel`を呼び出し、そのピクセルの色を決定・描画させます。
        4.  すべてのピクセルの描画後、`mlx_put_image_to_window`で完成したイメージをウィンドウに表示します。
    #### render_fractol
    ```c
    void	fractol_render(t_fractol *f)
    {
      //...
      scale = 4.0 / (f->zoom * WIDTH);
      y = 0;
      while (y < HEIGHT)
      {
        x = 0;
        while (x < WIDTH)
        {
          c.re = (x - WIDTH / 2) * scale + f->offset_x;
          c.im = (y - HEIGHT / 2) * scale + f->offset_y;
          render_pixel(f, c, x, y);
          x++;
        }
        y++;
      }
      mlx_put_image_to_window(f->mlx, f->win, f->img, 0, 0);
    }

    - scale = 4.0 / (f->zoom * WIDTH);
    複素数平面の幅（4.0）を、ズーム後の仮想的な画面ピクセル数で割る
    ズームイン (f->zoomが大きくなる) → scaleの値は小さくなり、1ピクセルが表す範囲が狭まる（=拡大表示）。
    ズームアウト (f->zoomが小さくなる) → scaleの値は大きくなり、1ピクセルが表す範囲が広がる（=縮小表示）。

    - while (y < HEIGHT)
        while (x < WIDTH)
    画面上のすべてのピクセル(x, y)に対して、c.re = ...; c.im = ...; render_pixel(...); の3行が実行
    ```
    #### render_pixel
    ```c
    static void	put_color(t_fractol *f, int iter, int x, int y)
    {
      //...
      if (iter == f->max_iter)
        color = 0x000000;
      else
      {
        r = (int)(sin(0.1 * iter + f->color_shift) * 127 + 128);
        g = (int)(cos(0.1 * iter + f->color_shift) * 127 + 128);
        b = (int)(sin(0.1 * iter + f->color_shift + 3) * 127 + 128);
        color = create_rgb(r, g, b);
      }
      put_pixel_to_image(f, x, y, color);
    }

    - 	if (iter == f->max_iter)
        color = 0x000000;
    iterが、最大繰り返し回数max_iterと等しければ、その点は計算を最後まで繰り返しても発散しなかった、つまりフラクタル集合の内部にあることを意味し、黒で塗りつぶす。
    - 	else
        r = (int)(sin(0.1 * iter + f->color_shift) * 127 + 128);
        g = (int)(cos(0.1 * iter + f->color_shift) * 127 + 128);
        b = (int)(sin(0.1 * iter + f->color_shift + 3) * 127 + 128);
    それ以外は、発散するまでの速さ（iterの値）に応じて色付け
    sin/cosの出力（-1.0〜1.0）を、* 127 + 128することでRGBの色範囲（0〜255）に変換

    ```

### `src/event_handlers.c`
キーボードやマウスからの**ユーザー入力**を処理します。
* `mlx_hook`によって登録され、イベント発生時に呼び出されます。
* キー入力（移動、色変更、リセット、終了）やマウスホイール（ズーム）に応じて`t_fractol`構造体の状態を更新し、再描画をトリガーします。
* `int handle_key(int keycode, t_fractol *f)`
    * **目的**: キーボード入力を処理する。
    * **処理**: `keycode`に応じて`t_fractol`のオフセット（矢印キー）、色シフト（`C`キー）、またはズームやオフセットのリセット（`R`キー）の値を変更し、最後に`render_fractol`を呼び出して画面を更新します。`ESC`キーの場合は`close_window`を呼び出します。
    #### fractol_handle_key
    ```c
    int	fractol_handle_key(int keycode, t_fractol *f)
    {
      double	move_step;

      move_step = 1.0 / f->zoom;
      if (keycode == ESC)
        fractol_close_window(f);
      else if (keycode == LEFT)
        f->offset_x -= move_step;
      else if (keycode == RIGHT)
        f->offset_x += move_step;
      else if (keycode == UP)
        f->offset_y -= move_step;
      else if (keycode == DOWN)
        f->offset_y += move_step;
      else if (keycode == 'c' || keycode == 'C')
        fractol_shift_colors(f);
      else if (keycode == 'r' || keycode == 'R')
      {
        f->zoom = 1.0;
        f->offset_x = 0.0;
        f->offset_y = 0.0;
        f->color_shift = 0;
      }
      fractol_render(f);
      return (0);
    }
    - move_step = 1.0 / f->zoom;
    矢印キーで移動する場合の一歩の大きさをズーム率に反比例して設定
    - if (keycode == ESC)...
    それぞれ押されたキーに応じて処理
    ```

    #### fractol_shift_colors
    ```c
    void	fractol_shift_colors(t_fractol *f)
    {
      f->color_shift += 10;
      if (f->color_shift > 255)
        f->color_shift = 0;
      fractol_render(f);
    }
    - RGBの色成分は通常0から255の範囲で扱われる
    ```

* `int handle_mouse(int button, int x, int y, t_fractol *f)`
    * **目的**: マウスボタン（特にホイール）入力を処理する。
    * **処理**: マウスホイール操作（`button 4`または`5`）を検知すると、まずマウスカーソルの座標を複素数に変換します。その後、その点を中心にズームイン・アウトするように`f->zoom`と`f->offset_x/y`の値を変更し、`render_fractol`で再描画します。
    #### fractol_handle_mouse
    ```c
    int	fractol_handle_mouse(int button, int x, int y, t_fractol *f)
    {
      double	zoom_factor;
      double	mouse_re;
      double	mouse_im;

      zoom_factor = 1.5;
      if (button == ZOOM_IN || button == ZOOM_OUT)
      {
        //マウスカーソルのピクセル座標 (x, y) を、現在のズームとオフセットにおける複素数平面上の座標 (mouse_re, mouse_im)に変換
        mouse_re = (x - WIDTH / 2.0) * (4.0 / (f->zoom * WIDTH)) + f->offset_x;
        mouse_im = (y - HEIGHT / 2.0) * (4.0 / (f->zoom * HEIGHT))
          + f->offset_y;
        if (button == ZOOM_IN)
        {
          //現在の中心点とマウスカーソルとの間の距離を、ズーム率で縮める
          f->offset_x = mouse_re + (f->offset_x - mouse_re) / zoom_factor;
          f->offset_y = mouse_im + (f->offset_y - mouse_im) / zoom_factor;
          f->zoom *= zoom_factor;
        }
        else if (button == ZOOM_OUT)
        {
          //中心点とマウスカーソルの距離を広げる
          f->offset_x = mouse_re + (f->offset_x - mouse_re) * zoom_factor;
          f->offset_y = mouse_im + (f->offset_y - mouse_im) * zoom_factor;
          f->zoom /= zoom_factor;
        }
        fractol_render(f);
      }
      return (0);
    }

    ```
    
    #### fractol_handle_mouse_move
    ```c
    int	fractol_handle_mouse_move(int x, int y, t_fractol *f)
    {
      f->mouse_x = x;
      f->mouse_y = y;
      return (0);
    }
    ```

* `int close_window(t_fractol *f)`
    * **目的**: リソースを解放し、プログラムを安全に終了させる。
    * **処理**: `mlx_destroy_image`, `mlx_destroy_window`, `mlx_destroy_display`を順に呼び出してMiniLibX関連のメモリを解放し、`exit(0)`でプログラムを終了します。
    #### fractol_close_window
    ```c
    int	fractol_close_window(t_fractol *f)
    {
      if (f->img)
        mlx_destroy_image(f->mlx, f->img);
      if (f->win)
        mlx_destroy_window(f->mlx, f->win);
      if (f->mlx)
      {
        mlx_destroy_display(f->mlx);
        free(f->mlx);
      }
      exit(0);
    }
    - mlx_destroy_image
    イメージ
    - mlx_destroy_window
    ウィンドウ
    - mlx_destroy_display
    グラフィック接続
    ```

### `src/utils.c`
複数の場所から利用される**補助的な便利関数**をまとめたファイルです。
* 文字列から数値への変換 (`ft_atof`) や文字列比較 (`ft_strcmp`)。
* ピクセルをイメージに描画する低レベルな関数 (`put_pixel`)。
* エラー処理や使用方法の表示など。
* `void put_pixel(t_fractol *f, int x, int y, int color)`
    * **目的**: イメージ上の指定された座標`(x, y)`に特定の色`color`のピクセルを描画する。
    * **処理**: `f->addr`（イメージの先頭アドレス）からピクセルに対応するメモリアドレスを計算し、そのアドレスに色データを直接書き込みます

    #### create_rgb
    ```c
    int	create_rgb(int r, int g, int b)
    {
      return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
    }
    - & 0xff
    0xff = 11111111で確実に0から255までの範囲（8ビット）に収めるための処理
    - << 16, << 8,
    色成分ごとに左ビットシフトさせて、ビットが重ならないようにずらしてある
    R, G, Bの三つの独立した値を、MiniLibXライブラリが一つの色として解釈できる単一の整数値に効率的にまとめている
    ```

    #### put_pixel_to_image
    ```c
    void	put_pixel_to_image(t_fractol *f, int x, int y, int color)
    {
      char	*dst;

      if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
      {
        dst = f->addr + (y * f->line_length + x * (f->bits_per_pixel / 8));
        *(unsigned int *)dst = color;
      }
    }
    - dst = f->addr + (y * f->line_length + x * (f->bits_per_pixel / 8));
    描画したいピクセル(x,y)が、メモリ上のどの番地にあるかを正確に計算
    f->addr: イメージデータが格納されているメモリ領域の先頭アドレスです。
    y * f->line_length: 目的のピクセルがある行の開始アドレスを計算します。
    f->line_lengthは、画像1行分のデータがメモリ上で何バイトを占めるかを示す値です。これにy（行番号）を掛けることで、目的の行までジャンプします。
    x * (f->bits_per_pixel / 8): 目的のピクセルの、その行の中での横方向の位置を計算します。
    f->bits_per_pixelは1ピクセルを表現するのに何ビット使うか（通常は32ビット）を示します。これを8で割ることでバイト数に変換し、x（列番号）を掛けることで、行の先頭から目的のピクセルまでのオフセット（ずれ）を求めます。
    これらをすべて足し合わせることで、dstというポインタ変数に、ピクセル(x,y)の正確なメモリアドレスが格納されます。
    - *(unsigned int *)dst = color;
    ポインタが指し示している先のメモリにアクセスし、そこにcolorの値を代入します。
    ```

## 素朴な疑問
### Q.　度々出現する４．０は何？
- マンデルブロ集合やジュリア集合の興味深い部分は、ほとんどが複素数平面上の実部-2.0から+2.0、虚部-2.0から+2.0の範囲に収まっているため