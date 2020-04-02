//
// Created by Sanjana Sarkar on 4/1/20.
//

#include <bayes/TestingClassifier.h>

int TestingClassifier::compute_highest_posterior_probability(vector<vector<int>> image,
    map<int, vector<vector<double>>> featureProbabilities,
    map <int, double> classProbabilities) {
  // Calculating probability for each value in map using log formula given

  map<int, vector<vector<double>>> testFeatureProbabilities;
  for (int i = 0; i < kNumLabels; i++) {
    // Populate map to use for testing with feature probabilities
    vector<vector<double>> classProbability(kDimension,
        vector<double>(kDimension));

    testFeatureProbabilities.insert(pair <int, vector<vector<double>>>
        (i, classProbability));
  }

  for (auto & iterateProbabilities : featureProbabilities) {
    vector<vector<double>> computedProbabilities;

    // Populate vector with initial values
    for (int i = 0; i < kDimension; i++) {
      vector<double> currentIndex(kDimension, 0.0);
      computedProbabilities.push_back(currentIndex);
    }

    // Calculating feature probabilities of test image
    int label = iterateProbabilities.first;
    vector<vector<double>> probOfTrainingImages =
        iterateProbabilities.second;
    double probabilityOfTestFeature;
    for (int i = 0; i < kDimension; i++) {
      for (int j = 0; j < kDimension; j++) {
        if (image[i][j] == 0) {
          probabilityOfTestFeature = probOfTrainingImages[i][j];
          computedProbabilities[i][j] = probabilityOfTestFeature;
        } else if (image[i][j] == 1) {
          probabilityOfTestFeature = 1.0 - probOfTrainingImages[i][j];
          computedProbabilities[i][j] = probabilityOfTestFeature;
        }
      }
    }

    testFeatureProbabilities[label] = computedProbabilities;
  }

  // Initializing map with values
  map<int, double> posteriorProbabilityTesting;

  for (int i = 0; i < kNumLabels; i++) {
    double numToAssign = 0.0;
    posteriorProbabilityTesting.insert(pair <int, double> (i, numToAssign));
  }

  // Calculating posterior probabilities of features
  for (auto iterateMap = testFeatureProbabilities.begin();
      iterateMap != testFeatureProbabilities.end(); iterateMap++) {
    vector<vector<double>> currentProbabilityMap = iterateMap->second;

    int label = iterateMap->first;
    double posteriorProb = 0.0;
    double previousClass = 0.0;
    previousClass = classProbabilities[label];

    for (int i = 0; i < 28; i++) {
      for (int j = 0; j < 28; j++) {
        // Calculation of posterior probability
        double featureProb = currentProbabilityMap[i][j];
        posteriorProb += log(featureProb);
      }
    }

    posteriorProb += log(previousClass);
    posteriorProbabilityTesting[label] = abs(posteriorProb);
  }
  allPosteriorProbs.insert(pair <map<int,double>, vector<vector<int>>>
      (posteriorProbabilityTesting, image));

  int currentClass = 0;
  double maxProb = posteriorProbabilityTesting[0];

  for (int i = 0; i < posteriorProbabilityTesting.size(); i++) {
    if (posteriorProbabilityTesting[i] > maxProb) {
      maxProb = posteriorProbabilityTesting[i];
      currentClass = i;
    }
  }
  return currentClass;
}
multimap<vector<int>, vector<vector<int>>> TestingClassifier::test_classifier(
    multimap<int, vector<vector<int>>> image_labels_features,
    map<int, vector<vector<double>>> feature_probabilities,
    const map<int, double>& class_probabilities) {

  map<int, vector<vector<vector<int>>>> probabilityData;
  // Initializing map with values

  for (int i = 0; i < kNumLabels; i++) {
    vector<vector<vector<int>>> imgVector;
    probabilityData.insert(make_pair(i, imgVector));
  }

  int labelForClass = 0;
  vector<vector<int>> labelForImage;
  // For loop is adding values from image_labels_features to probabilityData
  // to use for computation
  for (auto & iterateFeatures : image_labels_features) {
    labelForClass = iterateFeatures.first;
    labelForImage = iterateFeatures.second;

    probabilityData[labelForClass].push_back(labelForImage);
  }

  // Uses map which used values of best estimate and actual label assigned to
  // image
  multimap<vector<int>, vector<vector<int>>> bestEstimates;

  // Analyzes each image in map
  for (auto & iterateMap : probabilityData) {
    int label = iterateMap.first;
    vector<vector<vector<int>>> imgVector = iterateMap.second;

    // Finding best estimate values for images
    for (int j = 0; j < imgVector.size(); j++) {
      vector<vector<int>> image = imgVector[j];
      int bestEstimateValue =
          compute_highest_posterior_probability(image,
              feature_probabilities,class_probabilities);
      vector<int> valOfClass;

      valOfClass.push_back(bestEstimateValue);
      valOfClass.push_back(label);

      bestEstimates.insert(pair <vector<int>,
          vector<vector<int>>>(valOfClass, image));
    }
  }
  return bestEstimates;
}
