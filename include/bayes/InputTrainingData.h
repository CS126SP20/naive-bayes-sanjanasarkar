//
// Created by Sanjana Sarkar on 3/31/20.
//

#ifndef NAIVEBAYES_INPUTTRAININGDATA_H
#define NAIVEBAYES_INPUTTRAININGDATA_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include <vector>

using namespace std;

class InputTrainingData {

 public:
  int kImageDimension = 28;
  /**
   * Method used to read in training data and put into a multimap based on
   * image and the number the image is supposed to represent
   *
   * @param imagesFile Training data file containing training images
   * @param labelsFile Training data file containing labels for images
   * @return Multimap containing training images and corresponding number
   */
  multimap <vector<vector<char>>, int> read_training_files(string imagesFile,
      string labelsFile);

  /**
   * Turning image pixels into features used for training model
   *
   * @param images_and_labels Multimap containing training images and labels
   * @return Multimap containing features for images and corresponding number
   */
  multimap <vector<vector<int>>, int>
  pixels_to_features(multimap <vector<vector<char>>, int> images_and_labels);
};

#endif  // NAIVEBAYES_INPUTTRAININGDATA_H
