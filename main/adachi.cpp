#include "include//adachi.hpp"

#define MAZESIZE_X 32 // 迷路の大きさ(x方向)
#define MAZESIZE_Y 32 // 迷路の大きさ(y方向)
#define MASK_SEARCH 0x01
#define MASK_SECOND 0x03
#define CONV_SEN2WALL(w) ((w) ? WALL : NOWALL)

Search_task search_task;

void init_map(int x, int y)
{
	// 迷路の歩数Mapを初期化する。全体を0xff、引数の座標x,yは0で初期化する

	int i, j;

	for (i = 0; i < MAZESIZE_X; i++) // 迷路の大きさ分ループ(x座標)　
	{
		for (j = 0; j < MAZESIZE_Y; j++) // 迷路の大きさ分ループ(y座標)
		{
			map.size[i][j] = 255; // すべて255で埋める  ex)map[1][1] = 255,map[1][2] = 255, ...map[1][9] = 255,map[2][1] = 255...
		}
	}

	map.size[x][y] = 0; // ゴール座標の歩数を０に設定
}

void make_map(int x, int y, int mask) // 歩数マップを作成する
{
	// 座標x,yをゴールとした歩数Mapを作成する。
	// maskの値(MASK_SEARCH or MASK_SECOND)によって、
	// 探索用の歩数Mapを作るか、最短走行の歩数Mapを作るかが切り替わる
	int i, j;
	t_bool change_flag; // Map作成終了を見極めるためのフラグ

	init_map(x, y); // Mapを初期化する

	do
	{
		change_flag = FALSE;			 // 変更がなかった場合にはループを抜ける
		for (i = 0; i < MAZESIZE_X; i++) // 迷路の大きさ分ループ(x座標)
		{
			for (j = 0; j < MAZESIZE_Y; j++) // 迷路の大きさ分ループ(y座標)
			{
				if (map.size[i][j] == 255) // 255の場合は次へ
				{
					continue;
				}

				if (j < MAZESIZE_Y - 1) // 範囲チェック
				{
					if ((map.wall[i][j].north & mask) == NOWALL) // 壁がなければ(maskの意味はstatic_parametersを参照)
					{
						if (map.size[i][j + 1] == 255) // まだ値が入っていなければ
						{
							map.size[i][j + 1] = map.size[i][j] + 1; // 値を代入
							change_flag = TRUE;			   // 値が更新されたことを示す
						}
					}
				}

				if (i < MAZESIZE_X - 1) // 範囲チェック
				{
					if ((map.wall[i][j].east & mask) == NOWALL) // 壁がなければ
					{
						if (map.size[i + 1][j] == 255) // 値が入っていなければ
						{
							map.size[i + 1][j] = map.size[i][j] + 1; // 値を代入
							change_flag = TRUE;			   // 値が更新されたことを示す
						}
					}
				}

				if (j > 0) // 範囲チェック
				{
					if ((map.wall[i][j].south & mask) == NOWALL) // 壁がなければ
					{
						if (map.size[i][j - 1] == 255) // 値が入っていなければ
						{
							map.size[i][j - 1] = map.size[i][j] + 1; // 値を代入
							change_flag = TRUE;			   // 値が更新されたことを示す
						}
					}
				}

				if (i > 0) // 範囲チェック
				{
					if ((map.wall[i][j].west & mask) == NOWALL) // 壁がなければ
					{
						if (map.size[i - 1][j] == 255) // 値が入っていなければ
						{
							map.size[i - 1][j] = map.size[i][j] + 1; // 値を代入
							change_flag = TRUE;			   // 値が更新されたことを示す
						}
					}
				}
			}
		}

	} while (change_flag == TRUE); // 全体を作り終わるまで待つ
}

void set_wall(int x, int y) // 壁情報を記録
{
	// 引数の座標x,yに壁情報を書き込む
	int n_write = 0, s_write = 0, e_write = 0, w_write = 0;

	// 自分の方向に応じて書き込むデータを生成
	// CONV_SEN2WALL()はmacro.hを参照
	switch (mypos.dir)
	{
	case NORTH: // 北を向いている時

		n_write = CONV_SEN2WALL(w_sens.is_wall.FR || w_sens.is_wall.FL); // 前壁の有無を判断
		e_write = CONV_SEN2WALL(w_sens.is_wall.R);					   // 右壁の有無を判断
		w_write = CONV_SEN2WALL(w_sens.is_wall.L);					   // 左壁の有無を判断
		s_write = NOWALL;										   // 後ろは必ず壁がない

		break;

	case EAST: // 東を向いているとき

		e_write = CONV_SEN2WALL(w_sens.is_wall.FR || w_sens.is_wall.FL); // 前壁の有無を判断
		s_write = CONV_SEN2WALL(w_sens.is_wall.R);					   // 右壁の有無を判断
		n_write = CONV_SEN2WALL(w_sens.is_wall.L);					   // 左壁の有無を判断
		w_write = NOWALL;										   // 後ろは必ず壁がない

		break;

	case SOUTH: // 南を向いているとき

		s_write = CONV_SEN2WALL(w_sens.is_wall.FR || w_sens.is_wall.FL); // 前壁の有無を判断
		w_write = CONV_SEN2WALL(w_sens.is_wall.R);					   // 右壁の有無を判断
		e_write = CONV_SEN2WALL(w_sens.is_wall.L);					   // 左壁の有無を判断
		n_write = NOWALL;										   // 後ろは必ず壁がない

		break;

	case WEST: // 西を向いているとき

		w_write = CONV_SEN2WALL(w_sens.is_wall.FR || w_sens.is_wall.FL); // 前壁の有無を判断
		n_write = CONV_SEN2WALL(w_sens.is_wall.R);					   // 右壁の有無を判断
		s_write = CONV_SEN2WALL(w_sens.is_wall.L);					   // 左壁の有無を判断
		e_write = NOWALL;										   // 後ろは必ず壁がない

		break;
	}

	map.wall[x][y].north = n_write; // 実際に壁情報を書き込み
	map.wall[x][y].south = s_write; // 実際に壁情報を書き込み
	map.wall[x][y].east = e_write;	// 実際に壁情報を書き込み
	map.wall[x][y].west = w_write;	// 実際に壁情報を書き込み

	if (y < MAZESIZE_Y - 1) // 範囲チェック
	{
		map.wall[x][y + 1].south = n_write; // 反対側から見た壁を書き込み
	}

	if (x < MAZESIZE_X - 1) // 範囲チェック
	{
		map.wall[x + 1][y].west = e_write; // 反対側から見た壁を書き込み
	}

	if (y > 0) // 範囲チェック
	{
		map.wall[x][y - 1].north = s_write; // 反対側から見た壁を書き込み
	}

	if (x > 0) // 範囲チェック
	{
		map.wall[x - 1][y].east = w_write; // 反対側から見た壁を書き込み
	}
}

t_bool is_unknown(int x, int y) // 指定された区画が未探索か否かを判断する関数 未探索:TRUE　探索済:false
{
	// 座標x,yが未探索区間か否かを調べる

	if ((map.wall[x][y].north == UNKNOWN) || (map.wall[x][y].east == UNKNOWN) || (map.wall[x][y].south == UNKNOWN) || (map.wall[x][y].west == UNKNOWN))
	{				 // どこかの壁情報が不明のままであれば
		return TRUE; // 未探索
	}
	else
	{
		return FALSE; // 探索済
	}
}

int get_priority(int x, int y, t_direction dir) // そのマスの情報から、優先度を算出する
{
	// 座標x,yと、向いている方角dirから優先度を算出する

	// 未探索が一番優先度が高い.(4)
	// それに加え、自分の向きと、行きたい方向から、
	// 前(2)横(1)後(0)の優先度を付加する。

	int priority; // 優先度を記録する変数

	priority = 0;

	if (mypos.dir == dir) // 行きたい方向が現在の進行方向と同じ場合
	{
		priority = 2;
	}
	else if (((4 + mypos.dir - dir) % 4) == 2) // 行きたい方向が現在の進行方向と逆の場合
	{
		priority = 0;
	}
	else // それ以外(左右どちらか)の場合
	{
		priority = 1;
	}

	if (is_unknown(x, y) == TRUE)
	{
		priority += 4; // 未探索の場合優先度をさらに付加
	}

	return priority; // 優先度を返す
}

int get_nextdir(int x, int y, int mask, t_direction *dir)
{
	// ゴール座標x,yに向かう場合、今どちらに行くべきかを判断する。
	// 探索、最短の切り替えのためのmaskを指定、dirは方角を示す
	int little, priority, tmp_priority; // 最小の値を探すために使用する変数

	make_map(x, y, mask); // 歩数Map生成
	little = 255;		  // 最小歩数を255歩(mapがunsigned char型なので)に設定

	priority = 0; // 優先度の初期値は0

	// maskの意味はstatic_parameter.hを参照
	if ((map.wall[mypos.x][mypos.y].north & mask) == NOWALL) // 北に壁がなければ
	{
		tmp_priority = get_priority(mypos.x, mypos.y + 1, NORTH); // 優先度を算出
		if (map.size[mypos.x][mypos.y + 1] < little)					  // 一番歩数が小さい方向を見つける
		{
			little = map.size[mypos.x][mypos.y + 1]; // ひとまず北が歩数が小さい事にする
			*dir = NORTH;						// 方向を保存
			// now_dir = north;
			priority = tmp_priority; // 優先度を保存
		}
		else if (map.size[mypos.x][mypos.y + 1] == little) // 歩数が同じ場合は優先度から判断する
		{
			if (priority < tmp_priority) // 優先度を評価
			{
				*dir = NORTH; // 方向を更新
				// now_dir = north;
				priority = tmp_priority; // 優先度を保存
			}
		}
	}

	if ((map.wall[mypos.x][mypos.y].east & mask) == NOWALL) // 東に壁がなければ
	{
		tmp_priority = get_priority(mypos.x + 1, mypos.y, EAST); // 優先度を算出
		if (map.size[mypos.x + 1][mypos.y] < little)					 // 一番歩数が小さい方向を見つける
		{
			little = map.size[mypos.x + 1][mypos.y]; // ひとまず東が歩数が小さい事にする
			*dir = EAST;						// 方向を保存
			// now_dir = east;
			priority = tmp_priority; // 優先度を保存
		}
		else if (map.size[mypos.x + 1][mypos.y] == little) // 歩数が同じ場合、優先度から判断
		{
			if (priority < tmp_priority) // 優先度を評価
			{
				*dir = EAST; // 方向を保存
				// now_dir = east;
				priority = tmp_priority; // 優先度を保存
			}
		}
	}

	if ((map.wall[mypos.x][mypos.y].south & mask) == NOWALL) // 南に壁がなければ
	{
		tmp_priority = get_priority(mypos.x, mypos.y - 1, SOUTH); // 優先度を算出
		if (map.size[mypos.x][mypos.y - 1] < little)					  // 一番歩数が小さい方向を見つける
		{
			little = map.size[mypos.x][mypos.y - 1]; // ひとまず南が歩数が小さい事にする
			*dir = SOUTH;						// 方向を保存
			// now_dir = south;
			priority = tmp_priority; // 優先度を保存
		}
		else if (map.size[mypos.x][mypos.y - 1] == little) // 歩数が同じ場合、優先度で評価
		{
			if (priority < tmp_priority) // 優先度を評価
			{
				*dir = SOUTH; // 方向を保存
				// now_dir = south;
				priority = tmp_priority; // 優先度を保存
			}
		}
	}

	if ((map.wall[mypos.x][mypos.y].west & mask) == NOWALL) // 西に壁がなければ
	{
		tmp_priority = get_priority(mypos.x - 1, mypos.y, WEST); // 優先度を算出
		if (map.size[mypos.x - 1][mypos.y] < little)					 // 一番歩数が小さい方向を見つける
		{
			little = map.size[mypos.x - 1][mypos.y]; // 西が歩数が小さい
			*dir = WEST;						// 方向を保存
			// now_dir = west;
			priority = tmp_priority; // 優先度を保存
		}
		else if (map.size[mypos.x - 1][mypos.y] == little) // 歩数が同じ場合、優先度で評価
		{
			*dir = WEST; // 方向を保存
			// now_dir = west;
			priority = tmp_priority; // 優先度を保存
		}
	}

	return ((int)((4 + *dir - mypos.dir) % 4)); // どっちに向かうべきかを返す。
												// 演算の意味はmytyedef.h内のenum宣言から。
}

void search_adachi(int gx, int gy)
{
	// 引数gx,gyに向かって足立法で迷路を探索する
	t_direction glob_nextdir; // 次に向かう方向を記録する変数

	switch (get_nextdir(gx, gy, MASK_SEARCH, &glob_nextdir)) // 次に行く方向を戻り値とする関数を呼ぶ
	{
	case FRONT:
		search_task.run_half();
		break;

	case RIGHT:
		search_task.turn_right();
		break;

	case LEFT:
		search_task.turn_left();
		break;

	case REAR:
		search_task.turn_half();
		break;
	}

	mypos.dir = glob_nextdir; // 方向を更新

	// 向いた方向によって自分の座標を更新する
	switch (mypos.dir)
	{
	case NORTH:
		mypos.y++; // 北を向いた時はY座標を増やす
		break;

	case EAST:
		mypos.x++; // 東を向いた時はX座標を増やす
		break;

	case SOUTH:
		mypos.y--; // 南を向いた時はY座標を減らす
		break;

	case WEST:
		mypos.x--; // 西を向いたときはX座標を減らす
		break;
	}

	while ((mypos.x != gx) || (mypos.y != gy))
	{ // ゴールするまで繰り返す

		set_wall(mypos.x, mypos.y); // 壁をセット

		switch (get_nextdir(gx, gy, MASK_SEARCH, &glob_nextdir)) // 次に行く方向を戻り値とする関数を呼ぶ
		{
		case FRONT:
			search_task.run();

			break;

		case RIGHT:
			search_task.stop();
			search_task.turn_right();
			search_task.run_half();
			break;

		case LEFT:
			search_task.stop();
			search_task.turn_left();
			search_task.run_half();

			break;

		case REAR:
			search_task.stop();
			search_task.turn_half();
			search_task.run_half();
			break;
		}

		mypos.dir = glob_nextdir; // 方向を更新

		// 向いた方向によって自分の座標を更新する
		switch (mypos.dir)
		{
		case NORTH:
			mypos.y++; // 北を向いた時はY座標を増やす
			break;

		case EAST:
			mypos.x++; // 東を向いた時はX座標を増やす
			break;

		case SOUTH:
			mypos.y--; // 南を向いた時はY座標を減らす
			break;

		case WEST:
			mypos.x--; // 西を向いたときはX座標を減らす
			break;
		}
	}
	set_wall(mypos.x, mypos.y); // 壁をセット

	search_task.stop();
}

void make_search_task(void *pvparam){
    while (1)
    {
        search_adachi(0, 0);
        //vtaskDelay(1);
    }
    
}
