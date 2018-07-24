/*
 * Author name: Xujia Ji
 * date: 03/05/2018
 * Citation: Ke Ye（kye@stevens.edu）
 */
#include <iostream>
#include <fstream>


using namespace std;


class Point {
public:
    double x,y;
    Point(double x=0, double y=0) : x(x), y(y) {}
};

class GrowArray{
private:
    Point* data;
    int capacity;
    int used;
    void grow(){
        capacity *= 2;
    }

public:
    GrowArray() : used(0), capacity(1) {
        data = new Point[capacity];
    }

    ~GrowArray(){
        delete[] data;
    }

    void addEnd(Point v){

        if(used >= capacity) {
            grow();
            Point *old = data;
            data = new Point[capacity];
            for (int i = 0; i < used; i++) {
                data[i] = old[i];
            }
            delete [] old;
        }
        data[used] = v;
        used++;

    }

    int size() const {
        return used;
    }

    Point& operator [](int index){
        return data[index];
    }
};

class ConvexHull{
private:
    GrowArray **grid;
    int size;
    double minX,minY,maxX,maxY;

public:
    ConvexHull(int s):size(s), minX(9999), minY(9999), maxX(-9999), maxY(-9999) {
        grid = new GrowArray* [size];
        for (int i = 0; i < size; i++) {
            grid[i] = new GrowArray[size];
        }
    }

    void read(const char* filename){
        GrowArray points;
        ifstream file(filename);
        double x,y;
        while(file>>x){

            file>>y;
            points.addEnd(Point(x,y));
            minY = min(minY,y);
            minX = min(minX,x);
            maxY = max(maxY,y);
            maxX = max(maxX,x);
        }
        file.close();
        double x1 = (maxX-minX)/size;
        double y1 = (maxY-minY)/size;
        for(int i = 0; i < points.size();i++){
            double tempX = points[i].x;
            double tempY = points[i].y;
            int col = (tempX-minX)/x1;
            int row = (tempY-minY)/y1;
            if(row == size) row =row -1;
            if(col == size) col =col-1;
            grid[row][col].addEnd(points[i]);
        }

    }
    void printAllListSizes(){
        for(int i = 0;i<size;i++){
            for(int j = 0;j<size;j++){
                cout<<grid[i][j].size() << ' ';
            }
            cout << endl;
        }

    }
    void printMinMax(){
        cout<<"minX "<<minX<<endl;
        cout<<"minY "<<minY<<endl;
        cout<<"maxX "<<maxX<<endl;
        cout<<"maxy "<<maxY<<endl;
    }
    void printPerimeterClockWiseOrder() {
        for(int j = 0; j < size; j++)
            cout << "P" << (j + 1) % (size + 1) << ": " << grid[0][j].size() << endl;
        for(int i = 1; i < size; i++)
            cout << "P" << (i + 1) * size << ": " <<grid[i][size - 1].size() << endl;
        for(int j = size - 2; j >= 0; j--)
            cout << "P" << (size - 1) * size + (j + 1) % (size + 1) << ": "<< grid[size - 1][j].size() << endl;
        for(int i = size - 2; i >= 1; i--)
            cout << "P" << (i * size) + 1 << ": " << grid[i][0].size() << endl;

    }
};


int main() {
    ConvexHull ch(14);
    ch.read("convexhullpoints.dat");
    ch.printAllListSizes(); // tell us how many are in each list
    ch.printMinMax(); // print minx, maxx, miny, maxy
    ch.printPerimeterClockWiseOrder();
    return 0;
}