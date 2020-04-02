//
// Created by Sanjana Sarkar on 3/31/20.
//

#include <bayes/InputTrainingData.h>

multimap <int, vector<vector<int>>>
InputTrainingData::pixels_to_features(multimap <int, vector<vector<char>>>
                                      images_and_labels) {
  multimap <int, vector<vector<int>>> images_and_labels_features;

  // Code for map iterator from http://www.cplusplus.com/forum/beginner/218111/
  for (auto iterateMap = images_and_labels.begin();
       iterateMap != images_and_labels.end(); iterateMap++) {

    int label = iterateMap->first;
    vector<vector<char>> image = iterateMap->second;

    vector<vector<int>> imageFeatures(kImageDimension,
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
    images_and_labels_features.insert(pair <int, vector<vector<int>>>
                                          (label, imageFeatures));
  }
  return images_and_labels_features;
}

multimap <int, vector<vector<char>>>
    InputTrainingData::read_training_files(const string& imagesFile,
        const string& labelsFile) {
  // Multimap to store images and labels read in from file
  multimap <int, vector<vector<char>>> images_and_labels;

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
    images_and_labels.insert(pair <int, vector<vector<char>>> (imageLabel,
        completeImage));
  }

  return images_and_labels;
}