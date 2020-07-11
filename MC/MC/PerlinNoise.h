#pragma once
#ifndef PERLIN_H
#define PERLIN_H

double PerlinNoise(double x, double y, double z);
double fade(double t);//∆Ωª¨
double lerp(double t, double a, double b);//≤Â÷µ
double grad(int hash, double x, double y, double z);//Ã›∂»
void prepare();
#endif // !PERLIN_H
