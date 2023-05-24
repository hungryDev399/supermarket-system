#include "pch.h"
#include"employee.h"
#include "cashier_interface.h"
#include <Windows.h>
#include "gpt_implementation.h"
#include <cstdlib>
//#include <sys/resource.h>

#include "cashier_db.h"

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
        if (GetAsyncKeyState(VK_CONTROL) & GetAsyncKeyState('T') & 0x8000)
        {
            std::cout <<std::endl<< "Starting GPT..." << std::endl;
            //system("start cmd /k C:\\Users\\moabd\\source\\repos\\gpt\\gpt.exe");
            //talkToGPT();
        }

        // Sleep for a short duration to avoid high CPU usage
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main() {

    std::thread macro_detection_thread(inputThread);
    // start of program

    startProgram();

	//end of program
    //change the g_runing variable so the function that is runung on the macro_detection_thread terminates, and then join back
	g_running.store(false);
    macro_detection_thread.join();
    std::cout << "Program end, press enter to close the program"<<std::endl;
    std::cin.get();
    std::cin.get();

    

    return 0;
}