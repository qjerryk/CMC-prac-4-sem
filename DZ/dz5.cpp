#include <iostream>
#include <string>
#include <array>
#include <exception>


class Figure {
 public:
  virtual bool move(const std::string &start, const std::string &end) = 0;
  virtual ~Figure() {}
 protected:
  int get_line(const std::string &coord) const {
    return coord[0] - 'a';
  }
  int get_row(const std::string &coord) const {
    return coord[1] - '1';
  }
};

class King: public Figure {
 public:
  bool move(const std::string &start, const std::string &end) {
    int start_pos[2];
    int end_pos[2];

    start_pos[0] = get_line(start);
    start_pos[1] = get_row(start);
    end_pos[0] = get_line(end);
    end_pos[1] = get_row(end);
    if (abs(start_pos[0] - end_pos[0]) <= 1 && abs(start_pos[1] - end_pos[1]) <= 1) {
      return true;
    }
    return false;
  }
};

class Queen: public Figure {
 public:
  bool move(const std::string &start, const std::string &end) {
    int start_pos[2];
    int end_pos[2];

    start_pos[0] = get_line(start);
    start_pos[1] = get_row(start);
    end_pos[0] = get_line(end);
    end_pos[1] = get_row(end);
    if ( (abs(start_pos[0] - end_pos[0]) == abs(start_pos[1] - end_pos[1])) || abs(start_pos[0] - end_pos[0]) == 0 || abs(start_pos[1] - end_pos[1]) == 0) {
      return true;
    }
    return false;
  }
};

class Knight: public Figure {
 public:
  bool move(const std::string &start, const std::string &end) {
    int start_pos[2];
    int end_pos[2];

    start_pos[0] = get_line(start);
    start_pos[1] = get_row(start);
    end_pos[0] = get_line(end);
    end_pos[1] = get_row(end);
    if ( (abs(start_pos[0] - end_pos[0]) == 2 && abs(start_pos[1] - end_pos[1]) == 1) || (abs(start_pos[0] - end_pos[0]) == 1 && abs(start_pos[1] - end_pos[1]) == 2)) {
      return true;
    }
    return false;
  }
};

class Bishop: public Figure {
 public:
  bool move(const std::string &start, const std::string &end) {
    int start_pos[2];
    int end_pos[2];

    start_pos[0] = get_line(start);
    start_pos[1] = get_row(start);
    end_pos[0] = get_line(end);
    end_pos[1] = get_row(end);

    if (abs(start_pos[0] - end_pos[0]) == abs(start_pos[1] - end_pos[1])) {
      return true;
    }
    return false;
  }
};

class Rook: public Figure {
 public:
  bool move(const std::string &start, const std::string &end) {
    int start_pos[2];
    int end_pos[2];

    start_pos[0] = get_line(start);
    start_pos[1] = get_row(start);
    end_pos[0] = get_line(end);
    end_pos[1] = get_row(end);
    if (abs(start_pos[0] - end_pos[0]) == 0 || abs(start_pos[1] - end_pos[1]) == 0) {
      return true;
    }
    return false;
  }
};


class Parser {
 private:
  std::string fig;
  std::string start;
  std::string end;
 public:
  std::array<std::string, 3> read_move(void) {
    std::getline(std::cin, fig, ' ');
    std::getline(std::cin, start, ' ');
    std::getline(std::cin, end, '\n');
    std::array<std::string, 3> args {fig, start, end};
    return  args;
  }
};

class ChessChecker {
 private:
  std::string fig;
  std::string start;
  std::string end;
  Figure *arr[5];
 public:
  ChessChecker(void) {
    arr[0] = new King();
    arr[1] = new Queen();
    arr[2] = new Knight();
    arr[3] = new Bishop();
    arr[4] = new Rook();
  }
  void get_command() {
    Parser p;
    std::array<std::string, 3> args = p.read_move();
    fig = args[0];
    start = args[1];
    end = args[2];

  }
  int get_fig() const {
    if (fig == "K") {
      return 0;
    }
    if (fig == "Q") {
      return 1;
    }
    if (fig == "N") {
      return 2;
    }
    if (fig == "B") {
      return 3;
    }
    if (fig == "R") {
      return 4;
    }
    return -1;
  }
  bool check_coords (void) const {
    if (start.size() != 2 || end.size() != 2) {
      return false;
    }
    if (start[0] < 'a' || start[0] > 'h' || end[0] < 'a' || end[0] > 'h' || start[1] < '1' || start[1] > '8' || end[1] < '1' || end[1] > '8') {
      return false;
    }
    int ind = get_fig();
    if (ind < 0) {
      return false;
    }
    return (arr[ind])->move(start, end);
  }
  ~ChessChecker() {
    for (int i = 0; i < 5; ++i) {
      delete arr[i];
    }
  }
};

int main(void) {
  ChessChecker checker;
  checker.get_command();
  std::cout << (checker.check_coords()? "YES": "NO") << std::endl;
  return 0;
}