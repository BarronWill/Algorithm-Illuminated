#include<bits/stdc++.h>

using namespace std;

struct Point{
    int x;
    int y;
};

double dist(const Point& a, const Point& b){
    int dx = (a.x - b.x);
    int dy = (a.y - b.y);
    return sqrt(dx*dx + dy*dy);
}

bool comparex(const Point& a, const Point& b){
    return a.x < b.x;
}

bool comparey(const Point& a, const Point& b){
    return a.y < b.y;
}

pair<Point,Point> ClosesetPairHelper(const vector<Point>& Px, const vector<Point>& Py){
    int n = Px.size();
    
    if(n == 2)  return make_pair(Px[0], Px[1]);
    if(n == 3){
        double dis1 = dist(Px[0], Px[1]);
        double dis2 = dist(Px[0], Px[2]);
        double dis3 = dist(Px[1], Px[2]);

        if(dis1<=dis2 && dis1<=dis3)  return make_pair(Px[0], Px[1]);
        else if(dis2<=dis1 && dis2<=dis3) return make_pair(Px[0], Px[2]);
        else return make_pair(Px[1], Px[2]);
    }

    int half = n/2;
    vector<Point> Lx (Px.begin(), Px.begin() + half);
    vector<Point> Ly (Px.begin(), Px.begin() + half);
    vector<Point> Rx (Px.begin() + half, Px.end());
    vector<Point> Ry (Px.begin() + half, Px.end());

    sort(Lx.begin(), Lx.end(), comparex);
    sort(Ly.begin(), Ly.end(), comparey);
    sort(Rx.begin(), Rx.end(), comparex);
    sort(Ry.begin(), Ry.end(), comparey);

    pair<Point,Point> RightPoints = ClosesetPairHelper(Rx, Ry);
    pair<Point,Point> LeftPoints = ClosesetPairHelper(Lx, Ly);
    double mindistance = min(dist(RightPoints.first, RightPoints.second), dist(LeftPoints.first, LeftPoints.second));

    pair<Point,Point> splitpair;
    vector<Point> Sy;
    int midx = Px[half].x;
    for(const Point& point : Py){
        if(abs(point.x - midx) < mindistance){
            Sy.push_back(point);
        }
    }

    for(int i = 0; i < Sy.size(); i++){
        //int StripPoints = min(7,n-i);
        for(int j = i+1; j<Sy.size() && Sy[j].y-Sy[i].y < mindistance; j++){
            if(dist(Sy[j],Sy[i]) < mindistance){
                mindistance = dist(Sy[j],Sy[i]);
                splitpair = make_pair(Sy[j],Sy[i]);  
            }
        }
    }

    if(dist(LeftPoints.first,LeftPoints.second) == mindistance) return LeftPoints;
    else if(dist(RightPoints.first,RightPoints.second) == mindistance) return RightPoints;
    else return splitpair;
}

pair<Point,Point> ClosestPair(const vector<Point>& points){
    vector<Point> Px (points.begin(), points.end());
    vector<Point> Py (points.begin(), points.end());

    sort(Px.begin(), Px.end(), comparex);
    sort(Py.begin(), Py.end(), comparey);

    for(const Point& points : Px){
        cout<<points.x<<" "<<points.y<<"\n";
    }

    return ClosesetPairHelper(Px,Py);
}

int main(){
    vector<Point> points = {{-2, -1}, {2, 3}, {6, 6}, {19, 20}};

    pair<Point, Point> closest = ClosestPair(points);

    cout << "Closest pair of points: (" << closest.first.x << ", " << closest.first.y << ") and ("
         << closest.second.x << ", " << closest.second.y << ")" << endl;

    return 0;
}