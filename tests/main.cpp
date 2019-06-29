
#include <limits.h>
#include "minimalistprinter.h"


int main (int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  // Gets hold of the event listener list.
  ::testing::TestEventListeners& listeners = ::testing::UnitTest::GetInstance() -> listeners();
  // Replace the default listener
  delete listeners.Release (listeners.default_result_printer());
  // Add a listener to the end.  Google Test takes the ownership.
  MinimalistPrinter* mp = new MinimalistPrinter;
  listeners.Append (mp);
  int result = RUN_ALL_TESTS();

  delete listeners.Release (mp);
  return result;
}

