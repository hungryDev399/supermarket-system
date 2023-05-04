#include "pch.h"
#include"employee.h"
#include "cashier_interface.h"
#include <Windows.h>
//#include <sys/resource.h>

std::string admin_pass = "admin";
std::string admin_username = "admin";

// atomic bool for for stopping and starting the input detection process
std::atomic<bool> g_running(true);


/*void printMemory() {

        struct rusage usage;
        getrusage(RUSAGE_SELF, &usage);

        // Get the memory usage in bytes.
        long long memory_usage = usage.ru_maxrss;

        // Print the memory usage.
        std::cout << "Memory usage: " << memory_usage << " bytes\n";

    
}*/

// Thread function to continuously check for input
void inputThread()
{
    while (g_running.load())
    {
        // Check for Ctrl+L input
        if (GetAsyncKeyState(VK_CONTROL) & GetAsyncKeyState('L') & 0x8000)
        {
            std::cout <<std::endl<< "Doing something" << std::endl;
        }

        // Sleep for a short duration to avoid high CPU usage
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int mainn() {
    std::thread macro_detection_thread(inputThread);
    // start of program

	startCashierPov();






	//end of program
    //change the g_runing variable so the function that is runung on the macro_detection_thread terminates, and then join back
	g_running.store(false);
    macro_detection_thread.join();
    std::cout << "Done, press enter to close the program";
    std::cin.get();
    return 0;
}