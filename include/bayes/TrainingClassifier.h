//
// Created by Sanjana Sarkar on 4/1/20.
//

#ifndef NAIVEBAYES_TRAININGCLASSIFIER_H
#define NAIVEBAYES_TRAININGCLASSIFIER_H

#include <vector>
#include <map>

using namespace std;

class TrainingClassifier {
 private:
  const int kNumLabels = 10;
  const int kDimension = 28;
  const double kLaplaceConstant = 2.0;

 public:
  /**
   * Used to calculate feature probability
   *
   * @param image_label_features Map of image and label features
   * @return Map of feature probabilities
   */
  map<int, vector<vector<double>>>
      compute_feature_probability(const multimap <int, vector<vector<int>>>&
      image_label_features);

  /**
   * Used to calculate probability of classes
   *
   * @param image_label_features Raw image and label features
   * @return Map with class probabilities
   */
  map <int, double> compute_class_probability(multimap <int,
      vector< vector<int> >> image_label_features);
};

#endif  // NAIVEBAYES_TRAININGCLASSIFIER_H
