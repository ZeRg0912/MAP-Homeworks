#include <iostream>
#include "Data.h"

int main() {
	Data first = { 4, 12.86, true};
	Data second(8, 25.72, false);

	std::cout << "BEFORE:\n";
	std::cout << "First object:\n";
	std::thread view_first_before(&Data::Print, first);
	view_first_before.join();

	std::cout << "Second object:\n";
	std::thread view_second_before(&Data::Print, second);
	view_second_before.join();

	// LOCK SWAP
	std::thread swap(&SwapLock, std::ref(first), std::ref(second));
	swap.join();

	std::cout << "\n\nAFTER SWAP LOCK:\n";
	std::cout << "First object:\n";
	std::thread view_first_after(&Data::Print, first);
	view_first_after.join();

	std::cout << "Second object:\n";
	std::thread view_second_after(&Data::Print, second);
	view_second_after.join();

	// SCOPED LOCK SWAP
	std::thread swap_scoped(&SwapScopedLock, std::ref(first), std::ref(second));
	swap_scoped.join();

	std::cout << "\n\nAFTER SWAP SCOPED LOCK:\n";
	std::cout << "First object:\n";
	std::thread view_first_after_scoped(&Data::Print, first);
	view_first_after_scoped.join();

	std::cout << "Second object:\n";
	std::thread view_second_after_scoped(&Data::Print, second);
	view_second_after_scoped.join();

	// UNIQUE LOCK
	std::thread swap_unique(&SwapUniqueLock, std::ref(first), std::ref(second));
	swap_unique.join();

	std::cout << "\n\nAFTER SWAP SCOPED LOCK:\n";
	std::cout << "First object:\n";
	std::thread view_first_after_unique(&Data::Print, first);
	view_first_after_unique.join();

	std::cout << "Second object:\n";
	std::thread view_second_after_unique(&Data::Print, second);
	view_second_after_unique.join();

	return 0;
}