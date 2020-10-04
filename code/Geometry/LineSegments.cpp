double lineDist(const P& a, const P& b, const P& p)
{
    return (double)(b-a).cross(p-a)/(b-a).dist();
}

pair<int, P> lineInter(P s1, P e1, P s2, P e2)
{
    auto d = (e1 - s1).cross(e2 - s2);
    if (d == 0) // if parallel
        return {-(s1.cross(e1, s2) == 0), P(0, 0)};
    auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
    return {1, (s1 * p + e1 * q) / d};
}

double segDist(P& s, P& e, P& p)
{
    if (s==e) return (p-s).dist();
    auto d = (e-s).dist2(), t = min(d,max(.0,(p-s).dot(e-s)));
    return ((p-s)*d-(e-s)*t).dist()/d;
}

vector<P> segInter(P a, P b, P c, P d)
{
   auto oa = c.cross(d, a), ob = c.cross(d, b),
        oc = a.cross(b, c), od = a.cross(b, d);
   // Checks if intersection is single non-endpoint point.
   if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0)
       return {(a * ob - b * oa) / (ob - oa)};
   set<P> s;
   if (onSegment(c, d, a)) s.insert(a);
   if (onSegment(c, d, b)) s.insert(b);
   if (onSegment(a, b, c)) s.insert(c);
   if (onSegment(a, b, d)) s.insert(d);
   return {all(s)};
}

bool onSegment(P s, P e, P p) {
    return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}
