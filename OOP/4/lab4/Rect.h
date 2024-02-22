
class Rect {
public:
    int x, y;

    Rect(int x, int y) : x(x), y(y) {}

    double distanceFromOrigin() const {
        return std::sqrt(x * x + y * y);
    }
};