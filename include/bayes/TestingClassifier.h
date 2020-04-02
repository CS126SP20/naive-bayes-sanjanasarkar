//
// Created by Sanjana Sarkar on 4/1/20.
//

#ifndef NAIVEBAYES_TESTINGCLASSIFIER_H
#define NAIVEBAYES_TESTINGCLASSIFIER_H

#include <vector>
#include <map>
#include "math.h"

using namespace std;

class TestingClassifier {
 private:
  const int kNumLabels = 10;
  const int kDimension = 28;

 public:
  multimap<map<int,double>, vector<vector<int>>> allPosteriorProbs;

  /**
   * Used to calculate the probability of each feature and then find the highest
   * probability
   *
   * @param image Image to be evaluated
   * @param featureProbabilities Map of feature probabilities
   * @param class_to_class_probability
   * @return
   */
  int compute_highest_posterior_probability(vector<vector<int>> image,
      map<int, vector<vector<double>> > featureProbabilities,
      map <int, double> classProbabilities);

  /**
   * Testing classifier and storing resulting values in map
   *
   * @param image_labels_features
   * @param feature_probabilities
   * @param class_probabilities
   * @return
   */
  multimap<vector<int>, vector<vector<int>>>
      test_classifier(multimap <int, vector<vector<int>>>
          image_labels_features, map<int, vector<vector<double>>>
              feature_probabilities, const map <int, double>&
                  class_probabilities);
};

#endif  // NAIVEBAYES_TESTINGCLASSIFIER_H
