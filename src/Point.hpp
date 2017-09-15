class Point
{
    int hash;

public:
    int x, y;

    Point() : Point(-1, -1, -777)
    {}

    Point(int x, int y, int table_size)
    {
        this->x = x;
        this->y = y;
        this->hash = x * table_size + y;
    }

    friend bool operator ==(const Point& l, const Point& r)
    {
        return l.hash == r.hash;
    }

    friend bool operator <(const Point& l, const Point& r)
    {
        return l.hash < r.hash;
    }
};

std::vector<Point> get_neighbours(const int& x, const int& y, const int& table_size)
{
    std::vector<Point> coor;
    if (x > 0)
        coor.push_back(Point(x - 1, y, table_size));
    if (x < table_size - 1)
        coor.push_back(Point(x + 1, y, table_size));
    if (y > 0)
        coor.push_back(Point(x, y - 1, table_size));
    if (y < table_size - 1)
        coor.push_back(Point(x, y + 1, table_size));
    return coor;
}