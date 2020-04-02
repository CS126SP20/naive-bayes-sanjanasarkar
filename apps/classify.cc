// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <gflags/gflags.h>

#include <string>
#include <cstdlib>
#include <iostream>
#include <bayes/TestingClassifier.h>
#include <bayes/TrainingClassifier.h>
#include <bayes/InputTrainingData.h>

int main(int argc, char** argv) {
  TrainingClassifier train;
  InputTrainingData input;
  TestingClassifier test;

  input.read_training_files(argv[1], argv[2]);
  input.pixels_to_features();
  train.compute_feature_probability();
  train.compute_class_probability();
  test.compute_highest_posterior_probability();
  cout << test.test_classifier();
}
