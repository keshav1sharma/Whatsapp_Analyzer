#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <unordered_map>
#include <ctime> // added header file

using namespace std;
using namespace std::chrono;

// Define a regular expression to match the timestamps and messages in the chat.txt file
regex message_regex("^([0-9]{1,2}/[0-9]{1,2}/[0-9]{2}, [0-9]{1,2}:[0-9]{2}) - (.*?): (.*)$");

int main() {
    // Set the filename of the chat.txt file
    string filename = "chat.txt";

    // Initialize variables to hold the start time of the chat, the last message time, and the total time spent chatting
    system_clock::time_point start_time;
    system_clock::time_point last_message_time;
    milliseconds total_time(0);

    // Initialize variables to hold the message count, the count of messages sent by a particular person, and the map of messages sent by each person
    int message_count = 0;
    unordered_map<string, int> person_count;
    unordered_map<string, vector<string> > person_messages; // fixed the error here

    // Open the chat.txt file
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Failed to open the file." << endl;
        return 1;
    }

    string line;
    while (getline(file, line)) {
        // Try to match the current line to the message regex
        smatch match;
        if (regex_match(line, match, message_regex)) {
            // If the current line contains a message, extract the timestamp, sender, and message
            string timestamp_str = match.str(1);
            string sender = match.str(2);
            string message = match.str(3);

            // Parse the timestamp string into a system_clock::time_point object
            tm timestamp_tm = {};
            strptime(timestamp_str.c_str(), "%m/%d/%y, %H:%M", &timestamp_tm); // use strptime instead of get_time
            system_clock::time_point timestamp = system_clock::from_time_t(mktime(&timestamp_tm));

            if (start_time == system_clock::time_point()) {
                // If this is the first message in the chat, set the start time
                start_time = timestamp;
                last_message_time = timestamp;
            }
            else {
                // If this is not the first message in the chat, check if the time gap between the current and last message is more than 5 minutes
                milliseconds time_gap = duration_cast<milliseconds>(timestamp - last_message_time);
                if (time_gap > milliseconds(5 * 60 * 1000)) {
                    // If the time gap is more than 5 minutes, add the time spent in the previous chat session to the total time spent chatting
                    total_time += duration_cast<milliseconds>(last_message_time - start_time);

                    // Set the start time of the next chat session to be the time of the current message
                    start_time = timestamp;
                }

                // Update the last message time to the current timestamp
                last_message_time = timestamp;
            }

            // Update the message count, the count of messages sent by the current person, and the map of messages sent by each person
            message_count++;
            person_count[sender]++;
            person_messages[sender].push_back(message);
        }
    }

    // If there are any remaining chat sessions, add the time spent in the last session to the total time spent chatting
    if (start_time != system_clock::time_point()) {
        total_time += duration_cast<milliseconds>(last_message_time - start_time);
    }

    // Calculate the average messages per day
    int days = duration_cast<duration<int, std::ratio<86400> > >(last_message_time - start_time).count() + 1; // fixed the error here
    double average_messages_per_day = static_cast<double>(message_count) / days;

    // Print the total time spent chatting, the message count, the count of messages sent by each person, and the average messages per day

    //Convert Seconds into HH/MM/SS
    int seconds = total_time.count() / 1000.0;
    int  hours = seconds / 3600;
    seconds -= hours * 3600;
    int minutes = seconds / 60;
    seconds -= minutes * 60;




    cout << "Total time spent chatting: " << hours << " hours, " << minutes << " minutes, " << seconds << " seconds" << endl;
    cout << "Total number of messages: " << message_count << endl;
    cout << "Number of messages sent by each person:" << endl;
    for (const auto& person : person_count) {
        cout << person.first << " - " << person.second << endl;
    }
    cout << "Average messages per day: " << average_messages_per_day << endl;

    return 0;
}
