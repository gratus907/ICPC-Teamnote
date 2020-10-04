template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template <class T>
struct Point {
    typedef Point P_;
    T x, y;
    explicit Point(T x=0, T y=0) : x(x), y(y) {}
    bool operator<(P_ p) const { return tie(x,y) < tie(p.x,p.y); }
    bool operator==(P_ p) const { return tie(x,y)==tie(p.x,p.y); }
    P_ operator+(P_ p) const { return P_(x+p.x, y+p.y); }
    P_ operator-(P_ p) const { return P_(x-p.x, y-p.y); }
    P_ operator*(T d) const { return P_(x*d, y*d); }
    P_ operator/(T d) const { return P_(x/d, y/d); }
    T dot(P_ p) const { return x*p.x + y*p.y; }
    T cross(P_ p) const { return x*p.y - y*p.x; }
    T cross(P_ a, P_ b) const { return (a-*this).cross(b-*this); }
    T dist2() const { return x*x + y*y; }
    double dist() const { return sqrt((double)dist2()); }
    // angle to x-axis in interval [-pi, pi]
    double angle() const { return atan2(y, x); }
    P_ unit() const { return *this/dist(); } // makes dist()=1
    P_ perp() const { return P_(-y, x); } // rotates +90 degrees
    P_ normal() const { return perp().unit(); }
    // returns point rotated 'a' radians ccw around the origin
    P_ rotate(double a) const {
        return P_(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
    friend ostream& operator<<(ostream& os, P_ p) {
        return os << "(" << p.x << "," << p.y << ")"; }
};
