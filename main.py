# Author: Keshav Sharma
# Date: May 11, 2023
# Description: A script to analyze a chat log and calculate the total time spent chatting,
# the message count, the count of messages sent by each person, and the average messages per day.

import re
from datetime import datetime, timedelta

# Set the filename of the chat.txt file
filename = "chat.txt"

# Define a regular expression to match the timestamps and messages in the chat.txt file
message_regex = re.compile(r'^(\d{1,2}/\d{1,2}/\d{2}, \d{1,2}:\d{2}) - (.*?): (.*)$')

# Initialize variables to hold the start time of the chat, the last message time, and the total time spent chatting
start_time = None
last_message_time = None
total_time = timedelta(0)

# Initialize variables to hold the message count, the count of messages sent by a particular person, and the dictionary of messages sent by each person
message_count = 0
person_count = {}
person_messages = {}

# Open the chat.txt file and read it line by line
with open(filename, 'r', encoding='utf-8') as f:
    for line in f:
        # Try to match the current line to the message regex
        match = message_regex.match(line)

        if match:
            # If the current line contains a message, extract the timestamp, sender, and message
            timestamp_str = match.group(1)
            sender = match.group(2)
            message = match.group(3)

            # Parse the timestamp string into a datetime object
            timestamp = datetime.strptime(timestamp_str, '%m/%d/%y, %H:%M')

            if start_time is None:
                # If this is the first message in the chat, set the start time
                start_time = timestamp
                last_message_time = timestamp
            else:
                # If this is not the first message in the chat, check if the time gap between the current and last message is more than 5 minutes
                time_gap = timestamp - last_message_time
                if time_gap > timedelta(minutes=5):
                    # If the time gap is more than 5 minutes, add the time spent in the previous chat session to the total time spent chatting
                    total_time += last_message_time - start_time

                    # Set the start time of the next chat session to be the time of the current message
                    start_time = timestamp

                # Update the last message time to the current timestamp
                last_message_time = timestamp

            # Update the message count, the count of messages sent by the current person, and the dictionary of messages sent by each person
            message_count += 1
            if sender not in person_count:
                person_count[sender] = 1
                person_messages[sender] = [message]
            else:
                person_count[sender] += 1
                person_messages[sender].append(message)

# If there are any remaining chat sessions, add the time spent in the last session to the total time spent chatting
if start_time is not None:
    total_time += last_message_time - start_time

# Calculate the average messages per day
days = (last_message_time - start_time).days + 1
average_messages_per_day = message_count / days

# Print the total time spent chatting, the message count, the count of messages sent by each person, and the average messages per day
print("Total time spent chatting:", total_time)
print("Total number of messages:", message_count)
print("Number of messages sent by each person:")
for person in person_count:
    print(person, "-", person_count[person])
print("Average messages per day:", average_messages_per_day)
