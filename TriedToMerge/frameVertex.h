#ifndef __FRAMEVERTEX_H__
#define __FRAMEVERTEX_H__

struct FrameVertex {
 public:
  // Constructors
  FrameVertex(bool _l, bool _r, bool _t, bool _b)
      : left(_l), right(_r), top(_t), bottom(_b) {}

  // Setters
  void setLeft(bool _l) { left = _l; }
  void setRight(bool _r) { right = _r; }
  void setTop(bool _t) { top = _t; }
  void setBottom(bool _b) { bottom = _b; }

  // Getters
  bool getLeft() const { return left; }
  bool getRight() const { return right; }
  bool getTop() const { return top; }
  bool getBottom() const { return bottom; }

 private:
  bool left = false, right = false, top = false, bottom = false;
};

#endif