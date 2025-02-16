#include <iostream>

using namespace std;

struct Image {
  virtual void draw() = 0;
};

struct Bitmap : Image {
  Bitmap(const string &filename) {
    cout << "Loading bitmap from " << filename << endl;
  }
  void draw() override { cout << "Drawing bitmap" << endl; }
};

// proxy here
struct LazyBitmap : Image {
  LazyBitmap(const string &filename) : filename(filename) {}

  // loads the actual Bitmap only draw() is called
  void draw() override {
    if (!bmp) {
      bmp = new Bitmap(filename);
    }
    bmp->draw();
  }

private:
  string filename;
  Bitmap *bmp{nullptr};
};

int main() {
  // usage is the same
  // Bitmap bmp{"pokemon.png"};
  LazyBitmap bmp{"pokemon.png"};
  bmp.draw();
}
