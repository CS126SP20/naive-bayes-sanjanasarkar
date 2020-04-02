//
// Created by Sanjana Sarkar on 4/1/20.
//

#include <bayes/TrainingClassifier.h>

map <int, double> TrainingClassifier::compute_class_probability(multimap <int,
    vector< vector<int>>> image_label_features) {
  map <int, double> classProbabilities;

  int numMatchingLabels;

  for (auto iterateMap = image_label_features.begin();
       iterateMap != image_label_features.end(); iterateMap++) {
    // Determine number of equal labels
    int label = iterateMap->first;
    numMatchingLabels = image_label_features.count(label);

    int trainSize = image_label_features.size();
    // Compute class probability for current label
    double classProbability = static_cast<double>(numMatchingLabels) /
                              (double) (trainSize);
    // Populate map with computed class probabilities
    classProbabilities.insert(pair <int, double> (label, classProbability));
  }
  return classProbabilities;
}

map<int, vector<vector<double>>>
    TrainingClassifier::compute_feature_probability(const multimap <int, vector<vector<int>>>&
        image_label_features) {
  // Initialize the map with values
  map<int, vector<vector<double>>> featureProbability;

  for (int i = 0; i < kNumLabels; i++) {
    vector<vector<double>> labelProbability;
    featureProbability.insert(pair <int, vector<vector<double>>>
        (i, labelProbability));
  }

  // Determine probability of each feature in an image being a certain
  // label (1-10) and store in map
  map<int, vector<vector<vector<int>>>> imageData;
  // Initialize map
  for (int i = 0; i < kNumLabels; i++) {
    vector<vector<vector<int>>> imageVector;
    imageData.insert(pair <int, vector<vector<vector<int>>>> (i, imageVector));
  }

  vector<vector<int>> classImage;
  int classLabel = 0;
  // Add values to map
  for (const auto & image_label_feature : image_label_features) {
    classLabel = image_label_feature.first;
    classImage = image_label_feature.second;
    imageData[classLabel].push_back(classImage);
  }

  for (auto & iterateMap : imageData) {
    vector<vector<int>> numBackgroundPixels;

    for (int i = 0; i < kDimension; i++) {
      vector<int> pixel(kDimension, 0);
      numBackgroundPixels.push_back(pixel);
    }

    vector<vector<vector<int> >> imgVector = iterateMap.second;
    for (auto currentImage : imgVector) {
      for (int i = 0; i < kDimension; i++) {
        for (int j = 0; j < kDimension; j++) {
          if (currentImage[i][j] == 0) {
            numBackgroundPixels[i][j]++;
          }
        }
      }
    }

    vector<vector<double>> probabilitiesOfClasses;
    // Populate vector with probability of each class
    for (auto & iterateProbabilityMap : featureProbability) {
      int classToEvaluate = iterateProbabilityMap.first;
      probabilitiesOfClasses = iterateProbabilityMap.second;

      for (int i = 0; i < kDimension; i++) {
        vector<double> probVal(kDimension, 0.0);
        probabilitiesOfClasses.push_back(probVal);
      }

      // Calculate probability in every feature location
      for (int i = 0; i < 28; i++) {
        for (int j = 0; j < 28; j++) {
          int numPixels = numBackgroundPixels[i][j];
          double probOfFeature = static_cast<double>
              (kLaplaceConstant + numPixels) / (double) (2 * kLaplaceConstant +
                imgVector.size());
          probabilitiesOfClasses[i][j] = probOfFeature;
        }
      }
      featureProbability[classToEvaluate] = probabilitiesOfClasses;
    }
  }
    return featureProbability;
}
#include "bayes/TrainingClassifier.h"
