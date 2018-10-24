https://github.com/Microsoft/TestAdapterForGoogleTest/issues/119
--> you can add the following to your preprocessor definitions to get gtest to work correctly.

GTEST_HAS_STD_TUPLE_
GTEST_HAS_TR1_TUPLE=0

This tells gtest to not use TR1 and to use the std::tuple instead