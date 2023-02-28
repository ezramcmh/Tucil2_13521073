#include <iostream>
#include <cmath>
#include <ctime>
#include <cfloat>

using namespace std;

struct Point {
    double x, y, z;
};

double euclidean_distance(Point p1, Point p2) {
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    double dz = p1.z - p2.z;
    return sqrt(dx*dx + dy*dy + dz*dz);
}

double closest_pair(Point P[], int n, int& count) {
    if (n <= 3) {
        double min_dist = DBL_MAX;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                double d = euclidean_distance(P[i], P[j]);
                count++;
                if (d < min_dist) {
                    min_dist = d;
                }
            }
        }
        return min_dist;
    }

    int mid = n / 2;
    Point mid_point = P[mid];

    double dleft = closest_pair(P, mid, count);
    double dright = closest_pair(P + mid, n - mid, count);

    double d = min(dleft, dright);

    Point strip[n];
    int j = 0;
    for (int i = 0; i < n; i++) {
        if (abs(P[i].x - mid_point.x) < d) {
            strip[j] = P[i];
            j++;
        }
    }

    double min_strip = d;
    for (int i = 0; i < j; i++) {
        for (int k = i + 1; k < j && (strip[k].y - strip[i].y) < min_strip; k++) {
            double d_strip = euclidean_distance(strip[i], strip[k]);
            count++;
            if (d_strip < min_strip) {
                min_strip = d_strip;
            }
        }
    }
    return min(d, min_strip);
}

int main() {
    int n;
    int a;

    cout << "Pada program ini koordinat berada di rentang 0 < x,y,z < 10000" << endl;
    cout << "Minimal banyaknya titik yang dimasukkan 2 \n\n";
    cout << "Masukkan banyaknya titik: ";
    cin >> n;
    cout << endl;

    a = n;
    Point points[n];
    srand(time(0));
    for (int i = 0; i < n; i++) {
        points[i].x = ((float)rand()) / (float)RAND_MAX * 10000; 
        points[i].y = ((float)rand()) / (float)RAND_MAX * 10000; 
        points[i].z = ((float)rand()) / (float)RAND_MAX * 10000;
    }

    int count1 = 0;
    double min_distance = INFINITY;
    int i_min, j_min;
    
    clock_t strt = clock();
    for (int i = 0; i < a-1; i++) {
        for (int j = i+1; j < a; j++) {
            double dist = euclidean_distance(points[i], points[j]);
            count1++;
            if (dist < min_distance) {
                min_distance = dist;
                i_min = i;
                j_min = j;
            }
        }
    }
    clock_t stop = clock();

    clock_t start = clock();
    int count = 0;
    double min_dist = closest_pair(points, n, count);
    clock_t end = clock();

    cout << "Algoritma divide and conquer "<< endl ;
    cout << "Titik terdekat adalah ( " <<points[i_min].x << ", " << points[i_min].y << ", " << points[i_min].z << ") dan ("
        << points[j_min].x << ", " << points[j_min].y << ", " << points[j_min].z << ") dengan jarak : "<< min_distance << endl;
    cout << "Banyaknya operasi perhitungan: " << count << endl;
    cout << "Waktu eksekusi: " << double(end - start) / CLOCKS_PER_SEC * 1000 << " ms" << endl << endl;

    cout << "Algoritma Brute Force "<< endl ;
    cout << "Titik terdekat adalah ( " <<points[i_min].x << ", " << points[i_min].y << ", " << points[i_min].z << ") dan ("
        << points[j_min].x << ", " << points[j_min].y << ", " << points[j_min].z << ") dengan jarak : "<< min_distance << endl;
    cout << "Banyaknya operasi perhitungan: " << count1 << endl;
    cout << "Waktu eksekusi: " << double(stop-strt) / CLOCKS_PER_SEC * 1000 << " ms" << endl << endl;

    cout<< "Processor komputer yang digunakan AMD Ryzen 7 5800H ";
    return 0;
}
