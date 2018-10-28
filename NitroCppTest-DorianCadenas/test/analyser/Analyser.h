#pragma once
#ifndef ANALYSER_TEST_H
#define ANALYSER_TEST_H

#include <gtest/gtest.h>
#include "analyser/Analyser.h"

#define NAME_CLASS AnalyserTest

using namespace ShapeOverlay;

class AnalyserTest : public ::testing::Test {
protected:
	std::unique_ptr<Analyser> analyser;

	virtual void SetUp();
	virtual void TearDown();
};

#endif // !ANALYSER_TEST_H
