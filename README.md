# Whatsapp_Analyzer

Run Online : 

https://replit.com/@KeshavSharma65/WAAnalyzer


Program to calculate Total / Average time , Number of messages etc. from a Whatsapp chat.


**Analyzing WhatsApp Chat Logs**

This Python script is designed to analyze WhatsApp chat logs saved in a text file format. It uses regular expressions to match the timestamp and messages in the chat, and calculates various statistics such as total time spent chatting, number of messages sent, messages sent by each person, and average messages per day.




**Setup**




1.  Clone the repository to your local machine.

2.  Install Python 3 or C++ if you haven't already.

3.  Extract the chat log file from WhatsApp as a text file.

4.  Copy the chat log text file to the same directory as the chat_analyzer.py file.

5.  Rename the chat log file to chat.txt or modify the filename variable in chat_analyzer.py to match the name of your chat log file.

6.  Run the program by executing the chat_analyzer.py file using Python.





**How to extract a chat log file from WhatsApp**




1.  Open WhatsApp on your mobile device.

2.  Go to the chat you want to extract and tap on the contact/group name at the top.

3.  Scroll down to "Export Chat" and tap on it.

4.  Choose "Without Media" to export only the text messages.

5.  Select the method to export the chat, such as email, cloud storage, or sharing to another app.

6.  Once the chat is exported, download the text file to your computer and follow the steps in the Setup section above.



Before running the script, make sure to set the filename variable to the path of the chat.txt file that you want to analyze. The chat.txt file should be a plain text file with one line per message, in the format:

````
mm/dd/yy, hh:mm - sender: message text
````
For example:
````
01/01/21, 12:01 - Alice: Hello
01/01/21, 12:02 - Bob: Hi
01/01/21, 12:03 - Alice: How are you?
````
Usage
To run the script, simply execute the Python file in a terminal:
Copy code
python analyze_chat.py
The script will output the following statistics:
````
Total time spent chatting
Total number of messages
Number of messages sent by each person
Average messages per day
````
For example:
````
Total time spent chatting: 0:32:00
Total number of messages: 10
Number of messages sent by each person:
Alice - 4
Bob - 3
Charlie - 3
Average messages per day: 3.33
````

Dependencies
````
This script requires the following Python packages:

re for regular expressions
datetime for working with timestamps and time intervals
````
License
This script is released under the MIT License. See the LICENSE file for more information.




