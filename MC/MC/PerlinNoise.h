#pragma once
#ifndef PERLIN_H
#define PERLIN_H

double PerlinNoise3D(double x, double y, double z);
double PerlinNoise2D(double x, double y,double persistence, int Number_Of_Octaves);
double fade(double t);//∆Ωª¨
double lerp(double t, double a, double b);//≤Â÷µ
double grad(int hash, double x, double y, double z);//Ã›∂»
void prepare();
#endif // !PERLIN_H
