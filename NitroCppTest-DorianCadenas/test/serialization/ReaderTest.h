#pragma once
#ifndef READER_TEST_H
#define READER_TEST_H

#include <gtest/gtest.h>
#include <memory>
#include "shapes/ShapeFactory.h"

#define NAME_CLASS ReaderTest

using namespace IntersectionChecker;

class ReaderTest : public ::testing::Test {
protected:
	std::unique_ptr<ShapeFactory> factory;

	virtual void SetUp();
	virtual void TearDown();
};

#endif // !READER_TEST_H
