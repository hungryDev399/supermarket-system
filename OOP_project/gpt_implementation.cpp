#include "pch.h"
#include "openai.hpp"
#include <nlohmann/json.hpp>
#include "gpt_implementation.h"
using json = nlohmann::json;
void talkToGPT() {
    openai::start();
    json chat_json = R"(
    {
        "model": "gpt-3.5-turbo",
        "messages":[],
        "max_tokens": 3000,
        "temperature": 0
    }
    )"_json;
    while (1) {
        std::string message;
        std::cout << "Enter your message: ";
        std::getline(std::cin, message);
        if (message == "exit") {
			break;
		}
        message = "You are a customer service agent. Here is your prompt from the customer:" + message;

        chat_json["messages"].push_back({ {"role", "user"}, {"content", message} });
        auto chat = openai::chat().create(chat_json);
        auto out = chat.dump(0);
        const std::string response_content = out;
        // Parse the JSON string into a C++ object
        json parsed_data = json::parse(response_content);

        // Extract the message content from the object
        const std::string message_content = parsed_data["choices"][0]["message"]["content"];

        std::cout << message_content << std::endl;
    }
}