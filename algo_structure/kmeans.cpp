#include <vector>
#include <ctime>
using namespace std;

// bool equalCenters(vector<pair<int, int>> &ct1, vector<pair<int, int>> &ct2) {
//     int dissum = 0;
//     for (int i = 0; i < ct1.size(); ++i) {
//         dissum += distance(ct1[i], ct[2]);
//     }
//     return dissum < 1e-9;
// }


//     vector<pair<int, int>> prev_center;
//     do {
//         prev_center = cnt_center;
//         cnt_center = update(cnt_center);
//     }while (!equalCenters(prev_center, cnt_center));

struct Point {
    double x, y;
    int cluster;
    double minDis;

    Point():x(0.0), y(0.0), cluster(-1), minDis(__DBL_MIN__) {}
    Point(double x, double y):x(x),y(y),cluster(-1),minDis(__DBL_MIN__){}
    double distance(Point p) {
        return (p.x - x) * (p.x - x) + (p.y - y) * (p.y - y);
    }
};

vector<Point> read() {
    return {{}};
}

vector<Point> init_center(vector<Point> *points, int k) {
    vector<Point> centers;
    srand(time(0));
    for (int i = 0; i < k; ++i) {
        centers.push_back(points->at(rand()%k));
    }
    return centers;
}

void assign_points(vector<Point> &cnt_center, vector<Point> *points) {
    int i = 0;

    for (vector<Point>::iterator it = points->begin(); it != points->end(); ++it) {
        Point p = *it;
        for (auto c: cnt_center) {
            int clusterId = i ++;
            double dis = c.distance(p);
            if (dis < p.minDis) {
                p.minDis = dis;
                p.cluster = clusterId;
            }
        }
        *it = p;
    }
}

void compute_new_center(vector<int> &nPoints, vector<double> &sumX, vector<double> &sumY, vector<Point> *points, vector<Point> &cnt_center) {
    // iterate through all the points and increment the correct indices of the above vectors (based on the point’s cluster ID). 
    // Importantly, now is a convenient time to reset the minDist attribute of the point, so that the subsequent iteration works as intended.

    // Iterate over points to append data to centroids
    for (vector<Point>::iterator it = points->begin(); it != points -> end(); ++ it) {
        int clusterId = it -> cluster;
        nPoints[clusterId] += 1;
        sumX[clusterId] += it -> x;
        sumY[clusterId] += it -> y;

        it -> minDis = __DBL_MIN__; // reset distance
    }

    // traverse every c and compute the new center
    for (auto c: cnt_center) {
        int clusterId = c.cluster;
        c.x = sumX[clusterId] / nPoints[clusterId];
        c.y = sumY[clusterId] / nPoints[clusterId];
    }
}

void kMeans(vector<Point> *points, int epochs, int k) {
    // epochs is the number of iterations over which we will do our main k-means loop
    // k is the number of clusters.

    // a. 首先随机的从数据集合中选取个样本作为初始聚类的中心，记作，此时每个中心点对应的簇里都只有一个元素；
    vector<Point> cnt_center = init_center(points, k);
    for (int i = 0; i < epochs; ++i) {
        // b. 遍历每一个中心点，遍历数据集中的每一个样本，依次计算到个中心点的距离，并按照距离最小原则将该样本归类到最近的中心点对应的簇里；
        assign_points(cnt_center, points);

        // computing new centers
        vector<int> nPoints(k, 0); // points number
        vector<double> sumX(k, 0.0);
        vector<double> sumY(k, 0.0);
        // c. 遍历这个簇，重新计算它的中心点，方法就是计算簇里所有数据的均值，把这个均值看成是新的中心点；
        compute_new_center(nPoints, sumX, sumY, points, cnt_center);
    }

    // d. 重复b，c两个步骤，只到到达最大迭代次数或者每个簇的中心不再变化了为止。
}


int main() {
    vector<Point> points = read();
    int epochs;
    int k;
    kMeans(&points, epochs, k);
}