//
// Created by thomas on 24/03/23.
//
/*
 * This file is just an utility to create the test files to test the formal corectness of the
 * histogram equalization function.
 */
#include "image.h"
#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

/*
 * Function to create two images, one grayscale and one color, to test the histogram equalization.
 * The images will have a flat histogram, i.e. a linear gradient from 0 to 255,
 * so the equalized image should be a uniform image.
 */
void create_hist_eq_test_files() {
    Image im(16, 16, 1);
    Image im_color(16, 16, 3);
    int count = 0;
    for (int j = 0; j < im.h; j++) {
        for (int i = 0; i < im.w; i++) {
            cout << count / 255.0 << endl;
            im.set_pixel(i, j, 0, count / 255.0);
            im_color.set_pixel(i, j, 0, count / 255.0);
            im_color.set_pixel(i, j, 1, count / 255.0);
            im_color.set_pixel(i, j, 2, count / 255.0);
            count++;
        }
    }
    Matrix im_mat = imageToMatrix(im, 0, 0, 0); // c'è un'inversione inserita da Leo
    cout << im_mat << endl;
    cv::Mat cv_im = Mat(im.h, im.w, CV_32FC1, im.data);
    cout << "CV mat grey: " << endl << cv_im << endl;
    cv::Mat cv_im_color = Mat(im_color.h, im_color.w, CV_32FC1, im_color.data);

    cv_im *= 255.0;
    cv_im_color *= 255.0;
    vector<int> compression_params;
    compression_params.push_back(100);
    // questa la salva bene
    cv::imwrite("data/equalized_grey_cv.jpg", cv_im, compression_params);
    cv::imwrite("data/equalized_color_cv.jpg", cv_im_color, compression_params);
    // queste le salva male.... :(
    save_png(im, "data/equalized_gray");
    save_image(im, "data/equalized_gray");
    save_png(im_color, "data/equalized_color");
    save_image(im_color, "data/equalized_color");
}

void test_cv_vs_stb() {
    Image im1 = load_image("data/dog.jpg");
    cv::Mat im2 = cv::imread("data/dog.jpg");


}

int main() {
    create_hist_eq_test_files();
    return 0;
}