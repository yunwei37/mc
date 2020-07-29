#include"PerlinNoise.h"
#include<cmath>

int permutation[] = { 151,160,137,91,90,15,                 // Hash lookup table as defined by Ken Perlin.  This is a randomly
	131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,    // arranged array of all numbers from 0-255 inclusive.
	190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
	88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
	77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
	102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
	135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
	5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
	223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
	129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
	251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
	49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
	138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180
};//转换表
int p[512] = { 0 };
double PerlinNoise3D(double x, double y, double z)
{
	int xi = (int)x & 255;                              // Calculate the "unit cube" that the point asked will be located in
	int yi = (int)y & 255;                              // The left bound is ( |_x_|,|_y_|,|_z_| ) and the right bound is that
	int zi = (int)z & 255;                              // plus 1.  Next we calculate the location (from 0.0 to 1.0) in that cube.
	double xf = x - (int)x;
	double yf = y - (int)y;
	double zf = z - (int)z;
	double u = fade(xf);
	double v = fade(yf);
	double w = fade(zf);
	int A = p[xi] + yi;
	int AA = p[A] + zi;
	int AB = p[A + 1] + zi;
	int B = p[xi + 1] + yi;
	int BA = p[B] + zi;
	int BB = p[B + 1] + zi;
	double tmp1 = lerp(u, grad(p[AA], x, y, z), grad(p[BA], x - 1, y, z));
	double tmp2 = lerp(u, grad(p[AB], x, y - 1, z), grad(p[BB], x - 1, y - 1, z));
	double tmp3 = lerp(v, tmp1, tmp2);
	tmp1 = lerp(u, grad(p[AA + 1], x, y, z - 1), grad(p[BA + 1], x - 1, y, z - 1));
	tmp2 = lerp(u, grad(p[AB + 1], x, y - 1, z - 1), grad(p[BB + 1], x - 1, y - 1, z - 1));
	double tmp4 = lerp(v, tmp1, tmp2);
	return lerp(w, tmp3, tmp4);
}
double fade(double t)//平滑
{
	return t * t * t * (t * (t * 6 - 15) + 10);
}
double lerp(double t, double a, double b)//插值
{
	return a + t * (b - a);
}
double grad(int hash, double x, double y, double z)//梯度
{
	switch (hash & 0xF) {
	case 0x0: return  x + y;
	case 0x1: return -x + y;
	case 0x2: return  x - y;
	case 0x3: return -x - y;
	case 0x4: return  x + z;
	case 0x5: return -x + z;
	case 0x6: return  x - z;
	case 0x7: return -x - z;
	case 0x8: return  y + z;
	case 0x9: return -y + z;
	case 0xA: return  y - z;
	case 0xB: return -y - z;
	case 0xC: return  y + x;
	case 0xD: return -y + z;
	case 0xE: return  y - x;
	case 0xF: return -y - z;
	default: return 0; // never happens
	}
}
void prepare()
{
	for (int i = 0; i < 256; i++) {
		p[i + 256] = p[i] = permutation[i];
	}
}


double Noise(int x, int y)    // 根据(x,y)获取一个初步噪声值
{
	int n = x + y * 57;
	n = (n << 13) ^ n;
	return (1.0 - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);
}

double SmoothedNoise(int x, int y)   //光滑噪声
{
	double corners = (Noise(x - 1, y - 1) + Noise(x + 1, y - 1) + Noise(x - 1, y + 1) + Noise(x + 1, y + 1)) / 16;
	double sides = (Noise(x - 1, y) + Noise(x + 1, y) + Noise(x, y - 1) + Noise(x, y + 1)) / 8;
	double center = Noise(x, y) / 4;
	return corners + sides + center;
}
double Cosine_Interpolate(double a, double b, double x)  // 余弦插值
{
	double ft = x * 3.1415927;
	double f = (1 - cos(ft)) * 0.5;
	return a * (1 - f) + b * f;
}

double InterpolatedNoise(double x, double y)   // 获取插值噪声
{
	int integer_X = int(x);
	double  fractional_X = x - integer_X;
	int integer_Y = int(y);
	float fractional_Y = y - integer_Y;
	double v1 = SmoothedNoise(integer_X, integer_Y);
	double v2 = SmoothedNoise(integer_X + 1, integer_Y);
	double v3 = SmoothedNoise(integer_X, integer_Y + 1);
	double v4 = SmoothedNoise(integer_X + 1, integer_Y + 1);
	double i1 = Cosine_Interpolate(v1, v2, fractional_X);
	double i2 = Cosine_Interpolate(v3, v4, fractional_X);
	return Cosine_Interpolate(i1, i2, fractional_Y);
}

double PerlinNoise2D(double x, double y, double persistence, int Number_Of_Octaves)    // 最终调用：根据(x,y)获得其对应的PerlinNoise值
{
	double total = 0;
	double p = persistence;
	int n = Number_Of_Octaves;
	for (int i = 0; i < n; i++)
	{
		double frequency = pow(2, i);
		double amplitude = pow(p, i);
		total = total + InterpolatedNoise(x * frequency, y * frequency) * amplitude;
	}
	return total;
}

double PNoiseSmoth2D(double x, double y, double persistence, int Number_Of_Octaves, double interval)
{
	double total = PerlinNoise2D(x, y, persistence, Number_Of_Octaves);
	total += PerlinNoise2D(x + interval, y, persistence, Number_Of_Octaves);
	total += PerlinNoise2D(x - interval, y, persistence, Number_Of_Octaves);
	total += PerlinNoise2D(x, y - interval, persistence, Number_Of_Octaves);
	total += PerlinNoise2D(x, y + interval, persistence, Number_Of_Octaves);
	return total / 5;
}
