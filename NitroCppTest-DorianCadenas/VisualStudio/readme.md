In Visual Studio, there are two main configurations.
Under Debug or Release configuration, you should set the ShapeOverlay project as main project (init). It will execute the program.
Under Testing configuration, the project Test should be the main project. It will execute the test for the program.

==============================================================================

Flags added to configuration and why:

https://github.com/Microsoft/TestAdapterForGoogleTest/issues/119
--> you can add the following to your preprocessor definitions to get gtest to work correctly.

GTEST_HAS_STD_TUPLE_
GTEST_HAS_TR1_TUPLE=0

This tells gtest to not use TR1 and to use the std::tuple instead