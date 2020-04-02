//
// Created by Sanjana Sarkar on 3/31/20.
//

#include <bayes/InputTrainingData.h>

multimap <vector<vector<int>>, int>
InputTrainingData::pixels_to_features(multimap <vector<vector<char>>, int>
                                      images_and_labels) {
  multimap <vector<vector<int>>, int> images_and_labels_features;

  // Code for map iterator from http://www.cplusplus.com/forum/beginner/218111/
  for (auto iterateMap = images_and_labels.begin();
       iterateMap != images_and_labels.end(); iterateMap++) {

    vector<vector<char>> image = iterateMap->first;
    int label = iterateMap->second;

    vector<vector<int> > imageFeatures(kImageDimension,
                                       vector<int>(kImageDimension));

    for (int i = 0; i < kImageDimension; i++) {
      for (int j = 0; j < kImageDimension; j++) {
        char currentChar = image[i][j];
        int charValue = 0;

        if (currentChar == '+') {
          charValue = 1;
          imageFeatures[i][j] = charValue;
        } else if (currentChar == '#') {
          charValue = 1;
          imageFeatures[i][j] = charValue;
        } else if (currentChar == ' ') {
          imageFeatures[i][j] = charValue;
        }
      }
    }
    images_and_labels_features.insert(pair <vector<vector<int>>, int>
                                          (imageFeatures, label));
  }
  return images_and_labels_features;
}

multimap <vector<vector<char>>, int>
    InputTrainingData::read_training_files(string imagesFile,
        string labelsFile) {
  // Multimap to store images and labels read in from file
  multimap <vector<vector<char>>, int> images_and_labels;

  // Reading files
  ifstream readLabelFile;
  readLabelFile.open(labelsFile);
  string imageNumber;

  ifstream readImageFile;
  readImageFile.open(imagesFile);
  char imagePixelChar;

  // 2D Vector representing all pixels in 28 x 28 image
  vector<vector<char>> completeImage(kImageDimension,
      vector<char> (kImageDimension));

  while (getline(readLabelFile, imageNumber)) {
    int imageLabel;
    // Using stringstream to read labels in like an input stream
    stringstream readLabel(imageNumber);
    readLabel >> imageLabel;

    for (int i = 0; i < kImageDimension; i++) {
      for (int j = 0; j < kImageDimension; j++) {
        // Reading character in each pixel of image
        readImageFile.get(imagePixelChar);

        // If confronted with empty line
        if (imagePixelChar == '\n') {
        continue;
        }
        // Populating vector with characters that make up the image
          completeImage[i][j] = imagePixelChar;
      }
    }
    images_and_labels.insert(pair <vector<vector<char>>, int> (completeImage,
        imageLabel));
  }

  return images_and_labels;
}
#include "bayes/InputTrainingData.h"