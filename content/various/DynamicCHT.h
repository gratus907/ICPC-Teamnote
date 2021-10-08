/**
 * Author: DHDroid
 * Date: 2021-10-08
 * Description : Dynamic Convex Hull Trick by DHDroid
 */
int CHT_MODE=1;
bool MAX_CHT = false;
ld x_min = -1e18, x_max = 1e18;

struct Line {
    ld slope, y, start;

    ld compute(ld x1) const {
        return slope*x1 + y;
    }

    bool operator<(const Line& l) const {
        if(CHT_MODE == 1)
            if(MAX_CHT)
                return l.slope > this->slope;
            else
                return l.slope < this->slope;
        else
            return l.start > this->start;
    }

    ld intersect(const Line& l) const {
        if(l.slope == slope)
            return x_max+1;
        return (l.y-y)/(slope-l.slope);
    }
};

struct CHT {
    set<Line> s;
    void insert(ld slope, ld y) {
        Line l{slope, y, 0};
        auto ptr = s.lower_bound(l);
        if(ptr != s.end()) {
            if(MAX_CHT && ptr->compute(ptr->start) >= l.compute(ptr->start))
                return;
            else if(!MAX_CHT && ptr->compute(ptr->start) <= l.compute(ptr->start))
                return;
        }
        decltype(ptr) sit = s.begin(), eit = s.end();
        for(auto i=ptr; i!=s.end(); i++) {
            auto next_it = next(i);
            ld snext = (next_it==s.end()) ? x_max : next_it->start;
            ld isct = i->intersect(l);
            if(isct > i->start && isct <= snext) {
                eit = i;
                break;
            }
        }
        ld start = x_min;
        for(auto i=ptr; i!=s.begin(); i--) {
            auto t_i = prev(i);
            ld si = (i==s.end()) ? x_max : i->start;
            ld isct = t_i->intersect(l);
            if(isct >= t_i->start && isct < si) {
                start = isct;
                sit = i;
                break;
            }
        }

        for(auto i=sit; i!=eit;) {
            auto tmp = next(i);
            s.erase(i);
            i = tmp;
        }

        if(eit != s.end()) {
            Line tmp_l = *eit;
            s.erase(eit);
            tmp_l.start = l.intersect(tmp_l);
            s.insert(tmp_l);
        }

        l.start = start;
        s.insert(l);
    }

    ld query(ld x) {
        CHT_MODE=2;
        auto l_ptr = s.lower_bound(Line{0., 0., x});
        l_ptr = prev(l_ptr);
        ld ret = l_ptr->compute(x);
        CHT_MODE=1;
        return ret;
    };
};