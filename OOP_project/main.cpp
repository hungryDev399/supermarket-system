#include "pch.h"
#include"employee.h"
#include "cashier_interface.h"
#include <atomic>
#include <Windows.h>

std::string admin_pass = "admin";
std::string admin_username = "admin";

// atomic bool for for stopping and starting the input detection process
std::atomic<bool> g_running(true);



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
int main1() {
    std::thread macro_detection_thread(inputThread);
    // start of program

	startCashierPov();






	//end of program
    //change the g_runing variable so the function that is runung on the macro_detection_thread terminates, then join back.
	g_running.store(false);
    macro_detection_thread.join();
    std::cout << "Done, press enter to close the program";
    std::cin.get();
    return 0;
}