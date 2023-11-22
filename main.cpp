#include "include/DisplayApplication.h"
#include <memory>

int main()
{
	std::unique_ptr<DisplayApplication> application = std::make_unique<DisplayApplication>();
	application->run();
    return 0;
}
