// Copyright (c) 2020 [Your Name]. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <bayes/classifier.h>
#include <apps/classify.cc>
#include <bayes/InputTrainingData.h>

InputTrainingData input;

TEST_CASE("Accuracy", "[program ability]") {
  classify obj;
  double minAccuracy = 0.6;
  CHECK(obj.main >= minAccuracy);
}

// Checks to see if a valid file has been passed
TEST_CASE("Valid File Head", "[file]") {
  bool ans = input.read_training_files('/Users/sanjanasarkar/CLionProjects/naivebayes-sanjanasarkar/data/traininglabels');
  REQUIRE(ans == false);
}

// Program should ignore blank line in test file
TEST_CASE("Ignore blank line", "[file]") {
  input.read_training_files('/Users/sanjanasarkar/CLionProjects/naivebayes-sanjanasarkar/data/traininglabels');
  REQUIRE(input.read_training_files() == null);
}
