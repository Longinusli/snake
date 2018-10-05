#define length 233

//地图
char g_arrBackground[25][48] = {
								"■■■■■■■■■■■■■■■■■■■■■■■\n",
								"■                                          ■\n",
								"■                                          ■\n",
								"■                                          ■\n",
								"■                                          ■\n",
								"■                                          ■\n",
								"■                                          ■\n",
								"■                                          ■\n",
								"■                                          ■\n",
								"■                                          ■\n",
								"■                                          ■\n",
								"■                                          ■\n",
								"■                                          ■\n",
								"■                                          ■\n",
								"■                                          ■\n",
								"■                                          ■\n",
								"■                                          ■\n",
								"■                                          ■\n",
								"■                                          ■\n",
								"■                                          ■\n",
								"■                                          ■\n",
								"■                                          ■\n",
								"■                                          ■\n",
								"■                                          ■\n",
								"■■■■■■■■■■■■■■■■■■■■■■■\n"
};

//蛇数组
int g_arrsnake[length][3] = { 0 };

//方向
enum { to_east = 2, to_west = -2, to_north = -1, to_south = 1 };

//蛇运动方向
int g_nsnakedir = to_west;

//食物判断
bool g_testfood = true;

//食物坐标
int aX, aY;

//蛇长度
int g_snakelength = 1;

//分数
int g_score = 0;

//刷新频率
int g_speed;

//玩家名字
char str[10];

