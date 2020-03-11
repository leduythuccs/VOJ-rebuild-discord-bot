#include <spoj.h>
//#include <cassert>
#include <cstdio>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
using namespace std;

/*
FILE *spoj_p_in, *spoj_t_out, *spoj_score;
#define PIN "01.in"
#define TOUT "01.out"
#define SCORE "result.txt"

void spoj_init()
{
	spoj_p_in=fopen(PIN, "r");
	spoj_t_out=fopen(TOUT, "r");
	spoj_score=fopen(SCORE, "w");
}

#define spoj_assert assert
*/

#define EPSILON 0.000001
#define MAXN 1600

class Line
{
public:
	Line() {
		a = b = c = 0;
	};
	void set(double px1,double py1, double px2, double py2){
		a = py2 - py1;
		b = px1 - px2;
		c = (py1*(px2-px1) - px1*(py2-py1));

	};
	double cal(double x,double y)
	{
		return a*x+b*y+c;
	}
	int getSide(double x, double y) {
		double d = a*x+b*y+c;
		
		if (d<-EPSILON) return -1;
		else if (d>EPSILON) return 1;
		else return 0;
	}
	// ax+by+c = 0
	double a,b,c;
};

class Polygon
{
public:

	Polygon() {
		vnum = 0;
	};
	
	void addVertex(double ax,double ay) {
		x[vnum] = ax;
		y[vnum] = ay;
		vnum++;
	}
	
	void clear() {
		vnum = 0;
	}
	
	double area() {
		double ret = 0;
		
		for(int i = 0; i < vnum; i++) {
			ret += (x[i] - x[(i+1)%vnum])*(y[i]+y[(i+1)%vnum]);
		}
		
		return abs(ret)/2;
	}

	double area1() {
		double ret = 0;
		
		for(int i = 0; i < vnum; i++) {
			ret += (x[i] - x[(i+1)%vnum])*(y[i]+y[(i+1)%vnum]);
		}
		
		return ret;
	}
	
	void print() {
		cout << "--------" << endl;
		for(int i = 0; i < vnum; i++) {
			cout << x[i] << " " << y[i] << endl;
		}
		cout << "--------" << endl;
	}

	int vnum;
	double x[MAXN];
	double y[MAXN];
};

void calculateIntersection(double aa,double cc, double bb,double dd,double x1,double y1,double x2,double y2,double &xg,double &yg)
{
	double ms,ts,t;
	ms = (x2-x1)*(dd-cc) - (y2-y1)*(bb-aa);
	ts = (dd-cc)*(aa-x1) + (bb-aa)*(y1-cc);
	t = ts/ms;
	xg = x1 + t*(x2-x1);
	yg = y1 + t*(y2-y1);
}

Polygon clipPolygon(Polygon p, double aa,double bb,double cc,double dd, int sign0)
{
	Polygon result;
	Line aLine;
	aLine.set(aa, bb, cc, dd);
	double sign1,sign2;
	double x1,x2,y1,y2,xg,yg;

	for (int i=0; i< p.vnum; i++) {
		x1 = p.x[i];
		y1 = p.y[i];
		x2 = p.x[(i + 1) %p.vnum];
		y2 = p.y[(i + 1) %p.vnum];

		sign1 = aLine.cal(x1,y1)*sign0;
		sign2 = aLine.cal(x2,y2)*sign0;

		if (sign1*sign2 < 0) calculateIntersection(aa,bb,cc,dd,x1,y1,x2,y2,xg,yg);

		if (sign1 > EPSILON) {
			if (sign2 > EPSILON) {
				result.addVertex(x2,y2);
			}
			else if (sign2 < -EPSILON) {
				result.addVertex(xg,yg);
			}
			else {
			// ==0
				result.addVertex(x2,y2);
			}
		}
		else if (sign1 < -EPSILON) {
			if (sign2 > EPSILON) {
				result.addVertex(xg,yg);
				result.addVertex(x2,y2);
			}
			else if (sign2 < -EPSILON) {
			}
			else {
			// ==0
				result.addVertex(x2,y2);
			}
		}
		else {
			// ==0
			if (sign2 > EPSILON) {
				result.addVertex(x2,y2);
			}
			else if (sign2 < -EPSILON) {
			}
			else {
			// ==0
				result.addVertex(x2,y2);
			}
		}
	}
	return result;
}

string CCW(double x0, double y0, double x1, double y1, double x2, double y2) {
	double a1, b1, a2, b2, t;
	
	a1 = x1-x0;
	b1 = y1-y0;
	a2 = x2-x0;
	b2 = y2-y0;
	t = a1*b2 - a2*b1;
	
	if (abs(t) < EPSILON) return "STRAIGHT";
	else if (t > 0) return "LEFT";
	else return "RIGHT";
}

void trungtruc(double Ax, double Ay, double Bx, double By, double &Cx, double &Cy, double &Dx, double &Dy) {
	double deltaX = Ax - Bx;
	double deltaY = Ay - By;
	
	double Ox = (Ax + Bx) / 2;
	double Oy = (Ay + By) / 2;
	
	Cx = Ox + deltaY;
	Cy = Oy - deltaX;
	
	Dx = Ox - deltaY;
	Dy = Oy + deltaX;	
}

int n;
vector<double> toadoX, toadoY;
double dom[22];

int main() {
	spoj_init();
		
	toadoX.resize(22, 0);
	toadoY.resize(22, 0);
	int N = 11;
	
	
	//Opponent
	for (int i = 0; i < N; i++) fscanf(spoj_p_in, "%lf%lf", &toadoX[i], &toadoY[i]);
	//England
	for (int i = N; i < 2*N; i++) {
		int AA, BB;
		spoj_assert(fscanf(spoj_t_out, "%d%d", &AA, &BB));
		toadoX[i] = AA;
		toadoY[i] = BB;
		spoj_assert(-EPSILON <= toadoX[i] && toadoX[i] <= 120 + EPSILON);
		spoj_assert(-EPSILON <= toadoY[i] && toadoY[i] <= 90 + EPSILON);
	}
		
	for (int i = 0; i < N; i++)
		for (int j = N; j < 2*N; j++) 
			spoj_assert((fabs(toadoX[i] - toadoX[j]) > EPSILON) || (fabs(toadoY[i] - toadoY[j]) > EPSILON));
		
	double EnglandArea = 0;
	double OppArea = 0;
	
	for (int i = 0; i < 2*N; i++) {
		//cout << i << endl;
		Polygon P;
		P.addVertex(0, 0);
		P.addVertex(0, 90);
		P.addVertex(120, 90);
		P.addVertex(120, 0);

		
		for (int j = 0; j < 2*N; j++) if (i != j) {
			double Ax, Ay, Bx, By;
			trungtruc(toadoX[i], toadoY[i], toadoX[j], toadoY[j], Ax, Ay, Bx, By);			
			Line d;
			d.set(Ax, Ay, Bx, By);
			P = clipPolygon(P, Ax, Ay, Bx, By, d.getSide(toadoX[i], toadoY[i]));			
		}
//		cout << setprecision (5) << P.area() << endl;
		if (i < N) OppArea += P.area();
		else EnglandArea += P.area();
	}
		
	double P = EnglandArea / (OppArea + EnglandArea);
	//cout << P << endl;
	
	if (P <= 0.5) fprintf(spoj_score, "0"); else
	if (P >= 0.75) fprintf(spoj_score, "4"); else {
		fprintf(spoj_score, "%0.6lf", 1 + 48 * (P - 0.5) * (P - 0.5));
	}
	
	return 0;
}
