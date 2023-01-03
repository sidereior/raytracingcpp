#include <iostream>

int main() {
    const int image_width = 256;
    const int image_height = 256;
    //rows written top to bottom
    //pixels in each row written left to right
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    for(int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rprogress: " << ((int)((((image_height-1)/j)))/2.55) << ' ' << std::flush;
        for(int i = 0; i < image_width; ++i) {
            auto r = double(i) / (image_width-1);
            auto g = double(j) / (image_height-1);
            auto b = 0.25;
            int ir = 0;
            //static_cast<int>(255.999 * r);
            int ig = static_cast<int>(255.999 * g);
            int ib = static_cast<int>(255.999 * b);
            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
    std::cerr << "\ncomplete\n";
}