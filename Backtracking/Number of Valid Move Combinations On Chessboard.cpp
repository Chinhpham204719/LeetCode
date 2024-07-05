struct point {
  int x, y;
  bool operator==(const point& other) { return x == other.x && y == other.y; }
  bool operator!=(const point& other) { return x != other.x || y != other.y; }
  void moveTowards(const point& other) {
    x += x == other.x ? 0 : other.x > x ? 1 : -1;
    y += y == other.y ? 0 : other.y > y ? 1 : -1;
  }
};

vector<point> horizontalSteps = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
vector<point> diagonalSteps = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

class Solution {
 public:
  vector<point> positions;
 
  // `rook` takes the horizontal moves, `bishop` takes the diagonal ones
  // `queen` takes both horizontal and diagonal
  vector<point> getMoves(string piece, point p) {
    vector<point> res{{p.x, p.y}};

    if (piece == "rook" || piece == "queen") {
      for (auto step : horizontalSteps) {
        int i = p.x + step.x, j = p.y + step.y;
        while (i >= 0 && i < 8 && j >= 0 && j < 8) {
          res.push_back({i, j});
          i += step.x;
          j += step.y;
        }
      }
    }

    if (piece == "bishop" || piece == "queen") {
      for (auto step : diagonalSteps) {
        int i = p.x + step.x, j = p.y + step.y;
        while (i >= 0 && i < 8 && j >= 0 && j < 8) {
          res.push_back({i, j});
          i += step.x;
          j += step.y;
        }
      }
    }

    return res;
  }

  bool willIntersect(point a, point a2, point b, point b2) {
    // move each start position towards the end position and see if they intersect at any time
    while (a != a2 || b != b2) {
      a.moveTowards(a2);
      b.moveTowards(b2);

      if (a == b) return true;
    }

    return false;
  }

  bool isValidDestination(vector<point>& dest) {
    for (int i = 0; i < dest.size(); i++)
      for (int j = 0; j < i; j++)
        if (willIntersect(positions[i], dest[i], positions[j], dest[j])) return false;

    return true;
  }

  int dfs(int i, vector<string>& pieces, vector<point>& destination) {
    if (i == pieces.size()) {
      return isValidDestination(destination) ? 1 : 0;
    }

    int res = 0;
    for (auto move : getMoves(pieces[i], positions[i])) {
      destination[i] = move;
      res += dfs(i + 1, pieces, destination);
    }

    return res;
  }

  int countCombinations(vector<string>& pieces, vector<vector<int>>& pos) {
    for (int i = 0; i < pieces.size(); i++) positions.push_back({pos[i][0] - 1, pos[i][1] - 1});

    vector<point> destination(pieces.size());
    return dfs(0, pieces, destination);
  }
};
