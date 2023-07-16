#include<bits/stdc++.h>
//author NguyenVanViet
using namespace std;

struct Point {
    int x;
    int y;
};

// Function to calculate the Euclidean distance between two points
double calculateDistance(const Point& p1, const Point& p2) {
    int dx = p1.x - p2.x;
    int dy = p1.y - p2.y;
    return sqrt(dx * dx + dy * dy);
}

// Function to compare points based on x-coordinate
bool comparePointsX(const Point& p1, const Point& p2) {
    return p1.x < p2.x;
}

// Function to compare points based on y-coordinate
bool comparePointsY(const Point& p1, const Point& p2) {
    return p1.y < p2.y;
}

// Function to find the closest pair of points in a given vector
pair<Point, Point> closestPairHelper(const vector<Point>& Px, const vector<Point>& Py) {
    int n = Px.size();

    // Base case: when there are only two points
    if (n == 2) {
        return make_pair(Px[0], Px[1]);
    }

    // Base case: when there are three points
    if (n == 3) {
        double dist1 = calculateDistance(Px[0], Px[1]);
        double dist2 = calculateDistance(Px[1], Px[2]);
        double dist3 = calculateDistance(Px[0], Px[2]);

        if (dist1 <= dist2 && dist1 <= dist3) {
            return make_pair(Px[0], Px[1]);
        } else if (dist2 <= dist1 && dist2 <= dist3) {
            return make_pair(Px[1], Px[2]);
        } else {
            return make_pair(Px[0], Px[2]);
        }
    }

    // Divide the points into two halves
    int half = n / 2;
    vector<Point> Lx(Px.begin(), Px.begin() + half);
    vector<Point> Ly(Px.begin(), Px.begin() + half);
    vector<Point> Rx(Px.begin() + half, Px.end());
    vector<Point> Ry(Px.begin() + half, Px.end());

    // Sort the points by x-coordinate and y-coordinate
    sort(Lx.begin(), Lx.end(), comparePointsX);
    sort(Ly.begin(), Ly.end(), comparePointsY);
    sort(Rx.begin(), Rx.end(), comparePointsX);
    sort(Ry.begin(), Ry.end(), comparePointsY);

    // Recursive calls
    pair<Point, Point> leftPair = closestPairHelper(Lx, Ly);
    pair<Point, Point> rightPair = closestPairHelper(Rx, Ry);

    // Find the minimum distance and the corresponding points between the left and right pairs
    double minDistance = min(calculateDistance(leftPair.first, leftPair.second),
                             calculateDistance(rightPair.first, rightPair.second));
    pair<Point, Point> splitPair = {Point(),Point()};

    // Prepare the points for the strip
    vector<Point> Sy;
    int midX = Px[half].x;

    for (const Point& point : Py) {
        if (abs(point.x - midX) < minDistance) {
            Sy.push_back(point);
        }
    }

    // Find the closest split pair
    for (size_t i = 0; i < Sy.size(); ++i) {
        for (size_t j = i + 1; j < Sy.size() && (Sy[j].y - Sy[i].y) < minDistance; ++j) {
            double distance = calculateDistance(Sy[i], Sy[j]);
            minDistance = distance;
            splitPair = make_pair(Sy[i], Sy[j]);
        }
    }

    // Return the pair with the minimum distance
    if (calculateDistance(leftPair.first, leftPair.second) == minDistance) {
        return leftPair;
    } else if (calculateDistance(rightPair.first, rightPair.second) == minDistance) {
        return rightPair;
    } else {
        return splitPair;
    }
}

// Function to find the closest pair of points using the ClosestPair algorithm
pair<Point, Point> closestPair(const vector<Point>& points) {
    // Create copies of points sorted by x-coordinate and y-coordinate
    vector<Point> Px(points);
    vector<Point> Py(points);
    sort(Px.begin(), Px.end(), comparePointsX);
    sort(Py.begin(), Py.end(), comparePointsY);
    for(Point i : Px){
        cout<<i.x<<" "<<i.y<<"\n";
    }

    return closestPairHelper(Px, Py);
}

int main() {
    // Example usage
    vector<Point> points = {{119, 120}, {3, 40}, {5, 6}, {8, 9}, {19, 20}};

    pair<Point, Point> closest = closestPair(points);

    cout << "Closest pair of points: (" << closest.first.x << ", " << closest.first.y << ") and ("
         << closest.second.x << ", " << closest.second.y << ")" << endl;

    return 0;
}
