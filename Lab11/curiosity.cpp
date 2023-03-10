#include <iostream>
#include <string>
#include <vector>
#include <cstdlib> // for system()
#include <ctime> // for time() in srand( time(NULL) );
#include <iomanip> // for setw()
using namespace std;


class Mars
{
    private:
        vector< vector<char> > map_; // convention to put trailing underscore
        int dimX_, dimY_; // to indicate private data
    public:
        Mars(int dimX = 15, int dimY = 5);
        void init(int dimX, int dimY);
        void display() const;

        int getDimX() const;
        int getDimY() const;

        char getObject(int x, int y) const;
        void setObject(int x, int y, char ch);

        bool isEmpty(int x, int y);
        bool isInsideMap(int x, int y);
};

class Rover
{
    private:
        int x_, y_;
        char heading_; // either '^', '>', '<' or 'v'
    public:
        Rover();
        void land(Mars &mars);
        int getX() const;
        int getY() const;
        char getHeading() const;
};

Rover::Rover()
{
}

void Rover::land(Mars &mars)
{
    char possibleHeading[] = {'^', '>', '<', 'v'};
    x_ = rand() % mars.getDimX() + 1;
    y_ = rand() % mars.getDimY() + 1;
    heading_ = possibleHeading[rand() % 4];
    mars.setObject(x_, y_, heading_);
}

int Rover::getX() const
{
    return x_;
}

int Rover::getY() const
{
    return y_;
}

char Rover::getHeading() const
{
    return heading_;
}

void Mars::init(int dimX, int dimY)
{
    dimX_ = dimX;
    dimY_ = dimY;
    char objects[] = {' ', ' ', ' ', ' ', ' ', ' ', 'X', '#', '@', '$'};
    int noOfObjects = 10; // number of objects in the objects array
    // create dynamic 2D array using vector

    map_.resize(dimY_); // create empty rows
    for (int i = 0; i < dimY_; ++i)
    {
        map_[i].resize(dimX_); // resize each row
    }

    // put random characters into the vector array
    for (int i = 0; i < dimY_; ++i)
    {
        for (int j = 0; j < dimX_; ++j)
        {
            int objNo = rand() % noOfObjects;
            map_[i][j] = objects[objNo];
        }
    }
}

Mars::Mars(int dimX, int dimY)
{
    init(dimX, dimY);
}

int Mars::getDimX() const
{
    return dimX_;
}

int Mars::getDimY() const
{
    return dimY_;
}

void Mars::display() const
{
    // comment this out during testing
    // system("cls"); // OR system("clear"); for Linux / MacOS
    cout << " --__--__--__--__--__--__--__--_" << endl;
    cout << " = Curiosity, Welcome to Mars! =" << endl;
    cout << " __--__--__--__--__--__--__--__-" << endl;
    // for each row
    for (int i = 0; i < dimY_; ++i)
    {
        // display upper border of the row
        cout << "  ";
        for (int j = 0; j < dimX_; ++j)
        {
            cout << "+-";
        }
        cout << "+" << endl;
        // display row number
        cout << setw(2) << (dimY_ - i);
        // display cell content and border of each column
        for (int j = 0; j < dimX_; ++j)
        {
            cout << "|" << map_[i][j];
        }
        cout << "|" << endl;
    }
    // display lower border of the last row
    cout << "  ";
    for (int j = 0; j < dimX_; ++j)
    {
        cout << "+-";
    }
    cout << "+" << endl;
    // display column number
    cout << " ";
    for (int j = 0; j < dimX_; ++j)
    {
        int digit = (j + 1) / 10;
        cout << " ";
        if (digit == 0)
        cout << " ";
        else
        cout << digit;
    }
    cout << endl;
    cout << " ";
    for (int j = 0; j < dimX_; ++j)
    {
        cout << " " << (j + 1) % 10;
    }
    cout << endl << endl;
}

char Mars::getObject(int x, int y) const
{
    return map_[y-1][x-1];
}

void Mars::setObject(int x, int y, char ch )
{
    map_[y-1][x-1] = ch;
}

bool Mars::isEmpty(int x, int y)
{
    Mars mars;
    return mars.getObject(x, y) ==  ' ';
}

bool Mars::isInsideMap(int x, int y)
{
    return x <= dimX_ && x > 0 && y <= dimY_ && y > 0;
}
void test1_1()
{
    Mars mars;
    mars.display();
}

void test1_3()
{
Mars mars;
// mars.display();
cout << "Dim X = " << mars.getDimX() << endl;
cout << "Dim Y = " << mars.getDimY() << endl;
}

void test1_4()
{
    Mars mars;
    mars.display();
    int x, y;
    char obj;
    x = 1; y = 1;
    obj = mars.getObject(x, y);
    cout << "Object at column " << x << " and row " << y << " is ["
    << obj << "]" << endl;
    x = 15; y = 2;
    obj = mars.getObject(x, y);
    cout << "Object at column " << x << " and row " << y << " is ["
    << obj << "]" << endl;
    x = 5; y = 5;
    obj = mars.getObject(x, y);
    cout << "Object at column " << x << " and row " << y << " is ["
    << obj << "]" << endl;
    x = 10; y = 2;
    obj = mars.getObject(x, y);
    cout << "Object at column " << x << " and row " << y << " is ["
    << obj << "]" << endl;
}

void test1_5()
{
    Mars mars;
    int x1 = 1, y1 = 1; char ch1 = 'A';
    int x2 = 15, y2 = 1; char ch2 = 'B';
    int x3 = 15, y3 = 5; char ch3 = 'C';
    int x4 = 1, y4 = 5; char ch4 = 'D';
    int x5 = 7, y5 = 3; char ch5 = 'E';
    mars.setObject(x1, y1, ch1);
    mars.setObject(x2, y2, ch2);
    mars.setObject(x3, y3, ch3);
    mars.setObject(x4, y4, ch4);
    mars.setObject(x5, y5, ch5);
    mars.display();
    cout << "The object " << ch1 << " should be at column "
    << x1 << " and row " << y1 << endl;
    cout << "The object " << ch2 << " should be at column "
    << x2 << " and row " << y2 << endl;
    cout << "The object " << ch3 << " should be at column "
    << x3 << " and row " << y3 << endl;
    cout << "The object " << ch4 << " should be at column "
    << x4 << " and row " << y4 << endl;
    cout << "The object " << ch5 << " should be at column "
    << x5 << " and row " << y5 << endl;
}

void test1_6()
{
    Mars mars;
    int x1 = 2, y1 = 4; char ch1 = 'Z';
    int x2 = 10, y2 = 3; char ch2 = ' ';
    mars.setObject(x1, y1, ch1);
    mars.setObject(x2, y2, ch2);
    mars.display();
    cout << boolalpha;
    cout << "Is (" << x1 << ", " << y1 << ") empty? Answer = "
    << mars.isEmpty(x1, y1) << endl;
    cout << "Is (" << x2 << ", " << y2 << ") empty? Answer = "
    << mars.isEmpty(x2, y2) << endl;
    int x3 = 15, y3 = 5;
    int x4 = 0, y4 = 3;
    cout << "Is (" << x3 << ", " << y3 << ") inside map? Answer = "
    << mars.isInsideMap(x3, y3) << endl;
    cout << "Is (" << x4 << ", " << y4 << ") inside map? Answer = "
    << mars.isInsideMap(x4, y4) << endl;
}

void test2_1()
{
    Mars mars;
    Rover curiosity;
    curiosity.land(mars);
    mars.display();
    cout << "Status of the rover:" << endl
    << " Location: (" << curiosity.getX() << ", " << curiosity.getY() << ")"
    << endl
    << " Heading: " << curiosity.getHeading() << endl;
}
int main()
{
    srand(1); // use this for fixed map during testing
    // srand(time(NULL)); // try this for random map
    //test1_1();
    //test1_3();
    //test1_4();
    //test1_5();
    //test1_6();
    test2_1();
}