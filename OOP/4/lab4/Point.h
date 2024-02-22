class Point
{
public:
    int x;
    int y;

    Point(int x_val, int y_val) : x(x_val), y(y_val) {}

    bool operator==(const Point &p) const
    {
        return x == p.x && y == p.y;
    }

    bool operator>(const Point &p) const
    {
        return (x * x + y * y) > (p.x * p.x + p.y * p.y);
    }

    bool operator<(const Point &p) const
    {
        return (x * x + y * y) < (p.x * p.x + p.y * p.y);
    }

    friend ostream &operator<<(ostream &os, const Point &p)
    {
        os << "Point(" << p.x << "," << p.y << ")";
        return os;
    }
};

template <int n, int m>
bool Pred1_1(const Point &p)
{
    return (p.x <= m && p.x >= -n) && (p.y <= m && p.y >= -n);
};