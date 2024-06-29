class Solution {
public:

    bool reachingPoints(int sx, int sy, int tx, int ty) {
        if(sx>tx || sy>ty)return false;     //can naver reach target if already ahead of it
        else if(sx==tx && ty==sy){      //both are coordinates of same point
            return true;
        }
        while(tx>sx && ty>sy){
            if(tx>ty) tx=tx%ty;
            else    ty=ty%tx;
        }
        if ((tx==sx) && (ty-sy)%sx == 0)return true;
        else if ((ty==sy) && (tx-sx)%sy == 0)return true;
        return false;
    }
};
