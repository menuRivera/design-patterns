/*
You are given an example of an inheritance hierarchy which results in
Cartesian-product duplication.

Please refactor this hierarchy, giving the base class Shape  an initializer that
takes a Renderer  defined as

    struct Renderer
    {
      virtual string what_to_render_as() const = 0;
    }

as well as VectorRenderer and RasterRenderer.

The expectation is that each constructed object has a member called str()  that
returns its textual representation, for example,

Triangle(RasterRenderer()).str() // returns "Drawing Triangle as pixels"
 */

#include <iostream>
#include <string>
using namespace std;

struct Renderer {
  virtual string render_square() = 0;
  virtual string render_triangle() = 0;
};

struct VectorRenderer : Renderer {
  string render_square() override { return "Drawing Square as lines"; }
  string render_triangle() override { return "Drawing Triangle as lines"; }
};

struct RasterRenderer : Renderer {
  string render_square() override { return "Drawing Square as pixels"; }
  string render_triangle() override { return "Drawing Triangle as pixels"; }
};

struct Shape {
  Renderer &renderer;
  string name;
  Shape(Renderer &renderer, string name) : renderer{renderer}, name{name} {}
};

struct Triangle : Shape {
  Triangle(Renderer &renderer) : Shape(renderer, "Triangle") {}

  string str() const { return renderer.render_triangle(); }
};

struct Square : Shape {
  Square(Renderer &renderer) : Shape(renderer, "Square") {}
  string str() const { return renderer.render_square(); }
};

struct VectorSquare : Square {
  string str() const { return "Drawing " + name + " as lines"; }
};

struct RasterSquare : Square {
  string str() const { return "Drawing " + name + " as pixels"; }
};

// imagine e.g. VectorTriangle/RasterTriangle etc. here
