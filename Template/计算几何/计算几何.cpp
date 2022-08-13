// 计算几何 模板
*#include
#include <math.h>
#include
#define eps 1e-8
#define zero(x) (((x)>0?(x):-(x))<eps)
#define pi acos(-1.0)
struct point
{
double x, y;
};
struct line
{
point a, b;
};
struct point3
{
double x, y, z;
};
struct line3
{
point3 a, b;
};
struct plane3
{
point3 a, b, c;
};
//计算cross product (P1-P0)x(P2-P0)
double xmult(point p1, point p2, point p0)
{
return (p1.x - p0.x)(p2.y - p0.y) - (p2.x - p0.x)(p1.y - p0.y);
}
//计算dot product (P1-P0).(P2-P0)
double dmult(point p1, point p2, point p0)
{
return (p1.x - p0.x)(p2.x - p0.x) + (p1.y - p0.y)(p2.y - p0.y);
}
//计算cross product U . V
point3 xmult(point3 u, point3 v)
{
point3 ret;
ret.x = u.yv.z - v.yu.z;
ret.y = u.zv.x - u.xv.z;
ret.z = u.xv.y - u.yv.x;
return ret;
}
//计算dot product U . V
double dmult(point3 u, point3 v)
{
return u.xv.x + u.yv.y + u.zv.z;
}
//两点距离
double distance(point p1, point p2)
{
return sqrt((p1.x - p2.x)(p1.x - p2.x) + (p1.y - p2.y)(p1.y - p2.y));
}
//判三点共线
bool dots_inline(point p1, point p2, point p3)
{
return zero(xmult(p1, p2, p3));
}
//判点是否在线段上,包括端点
bool dot_online_in(point p, line l)
{
return zero(xmult(p, l.a, l.b)) && (l.a.x - p.x)(l.b.x - p.x) < eps && (l.a.y - p.y)(l.b.y - p.y) < eps;
}
//判点是否在线段上,不包括端点
bool dot_online_ex(point p, line l)
{
return dot_online_in(p, l) && (!zero(p.x - l.a.x) || !zero(p.y - l.a.y)) && (!zero(p.x - l.b.x) || !zero(p.y - l.b.y));
}
//判两点在线段同侧,点在线段上返回0
bool same_side(point p1, point p2, line l)
{
return xmult(l.a, p1, l.b)*xmult(l.a, p2, l.b) > eps;
}
//判两点在线段异侧,点在线段上返回0
bool opposite_side(point p1, point p2, line l)
{
return xmult(l.a, p1, l.b)*xmult(l.a, p2, l.b) < -eps;
}
//判两直线平行
bool parallel(line u, line v)
{
return zero((u.a.x - u.b.x)(v.a.y - v.b.y) - (v.a.x - v.b.x)(u.a.y - u.b.y));
}
//判两直线垂直
bool perpendicular(line u, line v)
{
return zero((u.a.x - u.b.x)(v.a.x - v.b.x) + (u.a.y - u.b.y)(v.a.y - v.b.y));
}
//判两线段相交,包括端点和部分重合
bool intersect_in(line u, line v)
{
if (!dots_inline(u.a, u.b, v.a) || !dots_inline(u.a, u.b, v.b))
return !same_side(u.a, u.b, v) && !same_side(v.a, v.b, u);
return dot_online_in(u.a, v) || dot_online_in(u.b, v) || dot_online_in(v.a, u) || dot_online_in(v.b, u);
}
//判两线段相交,不包括端点和部分重合
bool intersect_ex(line u, line v)
{
return opposite_side(u.a, u.b, v) && opposite_side(v.a, v.b, u);
}
//计算两直线交点,注意事先判断直线是否平行!
//线段交点请另外判线段相交(同时还是要判断是否平行!)
point intersection(line u, line v)
{
point ret = u.a;
double t = ((u.a.x - v.a.x)(v.a.y - v.b.y) - (u.a.y - v.a.y)(v.a.x - v.b.x)) / ((u.a.x - u.b.x)(v.a.y - v.b.y) - (u.a.y - u.b.y)(v.a.x - v.b.x));
ret.x += (u.b.x - u.a.x)t;
ret.y += (u.b.y - u.a.y)t;
return ret;
}
point intersection(point u1, point u2, point v1, point v2)
{
point ret = u1;
double t = ((u1.x - v1.x)(v1.y - v2.y) - (u1.y - v1.y)(v1.x - v2.x)) / ((u1.x - u2.x)(v1.y - v2.y) - (u1.y - u2.y)(v1.x - v2.x));
ret.x += (u2.x - u1.x)*t;
ret.y += (u2.y - u1.y)*t;
return ret;
}
//点到直线上的最近点
point ptoline(point p, line l)
{
point t = p;
t.x += l.a.y - l.b.y, t.y += l.b.x - l.a.x;
return intersection(p, t, l.a, l.b);
}
//点到直线距离
double disptoline(point p, line l)
{
return fabs(xmult(p, l.a, l.b)) / distance(l.a, l.b);
}
//点到线段上的最近点
point ptoseg(point p, line l)
{
point t = p;
t.x += l.a.y - l.b.y, t.y += l.b.x - l.a.x;
if (xmult(l.a, t, p)xmult(l.b, t, p) > eps)
return distance(p, l.a) < distance(p, l.b) ? l.a : l.b;
return intersection(p, t, l.a, l.b);
}
//点到线段距离
double disptoseg(point p, line l)
{
point t = p;
t.x += l.a.y - l.b.y, t.y += l.b.x - l.a.x;
if (xmult(l.a, t, p)xmult(l.b, t, p) > eps)
return distance(p, l.a) < distance(p, l.b) ? distance(p, l.a) : distance(p, l.b);
return fabs(xmult(p, l.a, l.b)) / distance(l.a, l.b);
}
//矢量V 以P 为顶点逆时针旋转angle 并放大scale 倍
point rotate(point v, point p, double angle, double scale)
{
point ret = p;
v.x -= p.x, v.y -= p.y;
p.x = scalecos(angle);
p.y = scalesin(angle);
ret.x += v.xp.x - v.yp.y;
ret.y += v.xp.y + v.yp.x;
return ret;
}
//计算三角形面积,输入三顶点
double area_triangle(point p1, point p2, point p3)
{
return fabs(xmult(p1, p2, p3)) / 2;
}
//计算三角形面积,输入三边长
double area_triangle(double a, double b, double c)
{
double s = (a + b + c) / 2;
return sqrt(s(s - a)(s - b)(s - c));
}
//计算多边形面积,顶点按顺时针或逆时针给出
double area_polygon(int n, point p)
{
double s1 = 0, s2 = 0;
int i;
for (i = 0; i < n; i++)
s1 += p[(i + 1)%n].yp[i].x, s2 += p[(i + 1)%n].yp[(i + 2)%n].x;
return fabs(s1 - s2) / 2;
}
//计算圆心角lat 表示纬度,-90<=w<=90,lng 表示经度
//返回两点所在大圆劣弧对应圆心角,0<=angle<=pi
double angle(double lng1, double lat1, double lng2, double lat2)
{
double dlng = fabs(lng1 - lng2)*pi / 180;
while (dlng >= pi + pi)
dlng -= pi + pi;
if (dlng > pi)
dlng = pi + pi - dlng;
lat1 *= pi / 180, lat2 *= pi / 180;
return acos(cos(lat1)*cos(lat2)*cos(dlng) + sin(lat1)sin(lat2));
}
//计算距离,r 为球半径
double line_dist(double r, double lng1, double lat1, double lng2, double lat2)
{
double dlng = fabs(lng1 - lng2)pi / 180;
while (dlng >= pi + pi)
dlng -= pi + pi;
if (dlng > pi)
dlng = pi + pi - dlng;
lat1 = pi / 180, lat2 = pi / 180;
return rsqrt(2 - 2 * (cos(lat1)cos(lat2)cos(dlng) + sin(lat1)sin(lat2)));
}
//计算球面距离,r 为球半径
inline double sphere_dist(double r, double lng1, double lat1, double lng2, double lat2)
{
return rangle(lng1, lat1, lng2, lat2);
}
//外心
point circumcenter(point a, point b, point c)
{
line u, v;
u.a.x = (a.x + b.x) / 2;
u.a.y = (a.y + b.y) / 2;
u.b.x = u.a.x - a.y + b.y;
u.b.y = u.a.y + a.x - b.x;
v.a.x = (a.x + c.x) / 2;
v.a.y = (a.y + c.y) / 2;
v.b.x = v.a.x - a.y + c.y;
v.b.y = v.a.y + a.x - c.x;
return intersection(u, v);
}
//内心
point incenter(point a, point b, point c)
{
line u, v;
double m, n;
u.a = a;
m = atan2(b.y - a.y, b.x - a.x);
n = atan2(c.y - a.y, c.x - a.x);
u.b.x = u.a.x + cos((m + n) / 2);
u.b.y = u.a.y + sin((m + n) / 2);
v.a = b;
m = atan2(a.y - b.y, a.x - b.x);
n = atan2(c.y - b.y, c.x - b.x);
v.b.x = v.a.x + cos((m + n) / 2);
v.b.y = v.a.y + sin((m + n) / 2);
return intersection(u, v);
}
//垂心
point perpencenter(point a, point b, point c)
{
line u, v;
u.a = c;
u.b.x = u.a.x - a.y + b.y;
u.b.y = u.a.y + a.x - b.x;
v.a = b;
v.b.x = v.a.x - a.y + c.y;
v.b.y = v.a.y + a.x - c.x;
return intersection(u, v);
}
//重心
//到三角形三顶点距离的平方和最小的点
//三角形内到三边距离之积最大的点
point barycenter(point a, point b, point c)
{
line u, v;
u.a.x = (a.x + b.x) / 2;
u.a.y = (a.y + b.y) / 2;
u.b = c;
v.a.x = (a.x + c.x) / 2;
v.a.y = (a.y + c.y) / 2;
v.b = b;
return intersection(u, v);
}
//费马点
//到三角形三顶点距离之和最小的点
point fermentpoint(point a, point b, point c)
{
point u, v;
double step = fabs(a.x) + fabs(a.y) + fabs(b.x) + fabs(b.y) + fabs(c.x) + fabs(c.y);
int i, j, k;
u.x = (a.x + b.x + c.x) / 3;
u.y = (a.y + b.y + c.y) / 3;
while (step > 1e-10)
{
for (k = 0; k < 10; step /= 2, k++)
{
for (i = -1; i <= 1; i++)
{
for (j = -1; j <= 1; j++)
{
v.x = u.x + stepi;
v.y = u.y + stepj;
if (distance(u, a) + distance(u, b) + distance(u, c) > distance(v, a) + distance(v, b) + distance(v, c))
{
u = v;
}
}
}
}
}
return u;
}
//矢量差 U - V
point3 subt(point3 u, point3 v)
{
point3 ret;
ret.x = u.x - v.x;
ret.y = u.y - v.y;
ret.z = u.z - v.z;
return ret;
}
///三维///
//取平面法向量
point3 pvec(plane3 s)
{
return xmult(subt(s.a, s.b), subt(s.b, s.c));
}
point3 pvec(point3 s1, point3 s2, point3 s3)
{
return xmult(subt(s1, s2), subt(s2, s3));
}
//两点距离,单参数取向量大小
double distance(point3 p1, point3 p2)
{
return sqrt((p1.x - p2.x)(p1.x - p2.x) + (p1.y - p2.y)(p1.y - p2.y) + (p1.z - p2.z)(p1.z - p2.z));
}
//向量大小
double vlen(point3 p)
{
return sqrt(p.xp.x + p.yp.y + p.zp.z);
}
//判三点共线
bool dots_inline(point3 p1, point3 p2, point3 p3)
{
return vlen(xmult(subt(p1, p2), subt(p2, p3))) < eps;
}
//判四点共面
bool dots_onplane(point3 a, point3 b, point3 c, point3 d)
{
return zero(dmult(pvec(a, b, c), subt(d, a)));
}
//判点是否在线段上,包括端点和共线
bool dot_online_in(point3 p, line3 l)
{
return zero(vlen(xmult(subt(p, l.a), subt(p, l.b)))) && (l.a.x - p.x)(l.b.x - p.x) < eps && (l.a.y - p.y)(l.b.y - p.y) < eps && (l.a.z - p.z)(l.b.z - p.z) < eps;
}
//判点是否在线段上,不包括端点
bool dot_online_ex(point3 p, line3 l)
{
return dot_online_in(p, l) && (!zero(p.x - l.a.x) || !zero(p.y - l.a.y) || !zero(p.z - l.a.z)) && (!zero(p.x - l.b.x) || !zero(p.y - l.b.y) || !zero(p.z - l.b.z));
}
//判点是否在空间三角形上,包括边界,三点共线无意义
bool dot_inplane_in(point3 p, plane3 s)
{
return zero(vlen(xmult(subt(s.a, s.b), subt(s.a, s.c))) - vlen(xmult(subt(p, s.a), subt(p, s.b))) - vlen(xmult(subt(p, s.b), subt(p, s.c))) - vlen(xmult(subt(p, s.c), subt(p, s.a))));
}
//判点是否在空间三角形上,不包括边界,三点共线无意义
bool dot_inplane_ex(point3 p, plane3 s)
{
return dot_inplane_in(p, s) && vlen(xmult(subt(p, s.a), subt(p, s.b))) > eps && vlen(xmult(subt(p, s.b), subt(p, s.c))) > eps && vlen(xmult(subt(p, s.c), subt(p, s.a))) > eps;
}
//判两点在线段同侧,点在线段上返回0,不共面无意义
bool same_side(point3 p1, point3 p2, line3 l)
{
return dmult(xmult(subt(l.a, l.b), subt(p1, l.b)), xmult(subt(l.a, l.b), subt(p2, l.b))) > eps;
}
//判两点在线段异侧,点在线段上返回0,不共面无意义
bool opposite_side(point3 p1, point3 p2, line3 l)
{
return dmult(xmult(subt(l.a, l.b), subt(p1, l.b)), xmult(subt(l.a, l.b), subt(p2, l.b))) < -eps;
}
//判两点在平面同侧,点在平面上返回0
bool same_side(point3 p1, point3 p2, plane3 s)
{
return dmult(pvec(s), subt(p1, s.a))dmult(pvec(s), subt(p2, s.a)) > eps;
}
bool same_side(point3 p1, point3 p2, point3 s1, point3 s2, point3 s3)
{
return dmult(pvec(s1, s2, s3), subt(p1, s1))dmult(pvec(s1, s2, s3), subt(p2, s1)) > eps;
}
//判两点在平面异侧,点在平面上返回0
bool opposite_side(point3 p1, point3 p2, plane3 s)
{
return dmult(pvec(s), subt(p1, s.a))dmult(pvec(s), subt(p2, s.a)) < -eps;
}
bool opposite_side(point3 p1, point3 p2, point3 s1, point3 s2, point3 s3)
{
return dmult(pvec(s1, s2, s3), subt(p1, s1))dmult(pvec(s1, s2, s3), subt(p2, s1)) < -eps;
}
//判两直线平行
bool parallel(line3 u, line3 v)
{
return vlen(xmult(subt(u.a, u.b), subt(v.a, v.b))) < eps;
}
//判两平面平行
bool parallel(plane3 u, plane3 v)
{
return vlen(xmult(pvec(u), pvec(v))) < eps;
}
//判直线与平面平行
bool parallel(line3 l, plane3 s)
{
return zero(dmult(subt(l.a, l.b), pvec(s)));
}
bool parallel(point3 l1, point3 l2, point3 s1, point3 s2, point3 s3)
{
return zero(dmult(subt(l1, l2), pvec(s1, s2, s3)));
}
//判两直线垂直
bool perpendicular(line3 u, line3 v)
{
return zero(dmult(subt(u.a, u.b), subt(v.a, v.b)));
}
//判两平面垂直
bool perpendicular(plane3 u, plane3 v)
{
return zero(dmult(pvec(u), pvec(v)));
}
//判直线与平面平行
bool perpendicular(line3 l, plane3 s)
{
return vlen(xmult(subt(l.a, l.b), pvec(s))) < eps;
}
//判两线段相交,包括端点和部分重合
bool intersect_in(line3 u, line3 v)
{
if (!dots_onplane(u.a, u.b, v.a, v.b))
return 0;
if (!dots_inline(u.a, u.b, v.a) || !dots_inline(u.a, u.b, v.b))
return !same_side(u.a, u.b, v) && !same_side(v.a, v.b, u);
return dot_online_in(u.a, v) || dot_online_in(u.b, v) || dot_online_in(v.a, u) || dot_online_in(v.b, u);
}
//判两线段相交,不包括端点和部分重合
bool intersect_ex(line3 u, line3 v)
{
return dots_onplane(u.a, u.b, v.a, v.b) && opposite_side(u.a, u.b, v) && opposite_side(v.a, v.b, u);
}
//判线段与空间三角形相交,包括交于边界和(部分)包含
bool intersect_in(line3 l, plane3 s)
{
return !same_side(l.a, l.b, s) && !same_side(s.a, s.b, l.a, l.b, s.c) && !same_side(s.b, s.c, l.a, l.b, s.a) && !same_side(s.c, s.a, l.a, l.b, s.b);
}
//判线段与空间三角形相交,不包括交于边界和(部分)包含
bool intersect_ex(line3 l, plane3 s)
{
return opposite_side(l.a, l.b, s) && opposite_side(s.a, s.b, l.a, l.b, s.c) && opposite_side(s.b, s.c, l.a, l.b, s.a) && opposite_side(s.c, s.a, l.a, l.b, s.b);
}
//计算两直线交点,注意事先判断直线是否共面和平行!
//线段交点请另外判线段相交(同时还是要判断是否平行!)
point3 intersection(line3 u, line3 v)
{
point3 ret = u.a;
double t = ((u.a.x - v.a.x)(v.a.y - v.b.y) - (u.a.y - v.a.y)(v.a.x - v.b.x))
/ ((u.a.x - u.b.x)(v.a.y - v.b.y) - (u.a.y - u.b.y)(v.a.x - v.b.x));
ret.x += (u.b.x - u.a.x)t;
ret.y += (u.b.y - u.a.y)t;
ret.z += (u.b.z - u.a.z)t;
return ret;
}
//计算直线与平面交点,注意事先判断是否平行,并保证三点不共线!
//线段和空间三角形交点请另外判断
point3 intersection(line3 l, plane3 s)
{
point3 ret = pvec(s);
double t = (ret.x(s.a.x - l.a.x) + ret.y(s.a.y - l.a.y) + ret.z(s.a.z - l.a.z)) / (ret.x(l.b.x - l.a.x) + ret.y(l.b.y - l.a.y) + ret.z(l.b.z - l.a.z));
ret.x = l.a.x + (l.b.x - l.a.x)t;
ret.y = l.a.y + (l.b.y - l.a.y)t;
ret.z = l.a.z + (l.b.z - l.a.z)t;
return ret;
}
point3 intersection(point3 l1, point3 l2, point3 s1, point3 s2, point3 s3)
{
point3 ret = pvec(s1, s2, s3);
double t = (ret.x(s1.x - l1.x) + ret.y(s1.y - l1.y) + ret.z(s1.z - l1.z)) /
(ret.x(l2.x - l1.x) + ret.y(l2.y - l1.y) + ret.z(l2.z - l1.z));
ret.x = l1.x + (l2.x - l1.x)*t;
ret.y = l1.y + (l2.y - l1.y)*t;
ret.z = l1.z + (l2.z - l1.z)t;
return ret;
}
//计算两平面交线,注意事先判断是否平行,并保证三点不共线!
line3 intersection(plane3 u, plane3 v)
{
line3 ret;
ret.a = parallel(v.a, v.b, u.a, u.b, u.c) ? intersection(v.b, v.c, u.a, u.b, u.c) : intersection(v.a, v.b, u.a, u.b, u.c);
ret.b = parallel(v.c, v.a, u.a, u.b, u.c) ? intersection(v.b, v.c, u.a, u.b, u.c) : intersection(v.c, v.a, u.a, u.b, u.c);
return ret;
}
line3 intersection(point3 u1, point3 u2, point3 u3, point3 v1, point3 v2, point3 v3)
{
line3 ret;
ret.a = parallel(v1, v2, u1, u2, u3) ? intersection(v2, v3, u1, u2, u3) : intersection(v1, v2, u1, u2, u3);
ret.b = parallel(v3, v1, u1, u2, u3) ? intersection(v2, v3, u1, u2, u3) : intersection(v3, v1, u1, u2, u3);
return ret;
}
//点到直线距离
double ptoline(point3 p, line3 l)
{
return vlen(xmult(subt(p, l.a), subt(l.b, l.a))) / distance(l.a, l.b);
}
//点到平面距离
double ptoplane(point3 p, plane3 s)
{
return fabs(dmult(pvec(s), subt(p, s.a))) / vlen(pvec(s));
}
//直线到直线距离
double linetoline(line3 u, line3 v)
{
point3 n = xmult(subt(u.a, u.b), subt(v.a, v.b));
return fabs(dmult(subt(u.a, v.a), n)) / vlen(n);
}
//两直线夹角cos 值
double angle_cos(line3 u, line3 v)
{
return dmult(subt(u.a, u.b), subt(v.a, v.b)) / vlen(subt(u.a, u.b)) / vlen(subt(v.a, v.b));
}
//两平面夹角cos 值
double angle_cos(plane3 u, plane3 v)
{
return dmult(pvec(u), pvec(v)) / vlen(pvec(u)) / vlen(pvec(v));
}
//直线平面夹角sin 值
double angle_sin(line3 l, plane3 s)
{
return dmult(subt(l.a, l.b), pvec(s)) / vlen(subt(l.a, l.b)) / vlen(pvec(s));
}
//凸包
int ConvexHull(point p,int n,point ch)//Andrew
{
int m = 0;
for(int i = 0;i < n;i++)
{
while(m>1&&Cross(ch[m-1] - ch[m-2],p[i]-ch[m-2]) <= 0) m–;
//如果发现更好的点把之前凸包内的点吐出
ch[m++] = p[i];
}
int k = m;
for(int i=n-2;i >= 0;i–)
{
while(m > k && Cross(ch[m-1]-ch[m-2],p[i]-ch[m-2]) <= 0) m–;
ch[m++] = p[i];
}
if(n>1)
m–;
return m;
}
叉积为负 点在线段的左侧
叉积为正 点在线段的右侧
先用凸包找到最大的多边形然后再计算多边形面积
计算多边形面积使点按逆时针或顺时针排序
