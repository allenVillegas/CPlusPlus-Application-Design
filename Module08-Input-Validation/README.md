Name: Allen Villegas

Course: CIS 25 - Programming Using C++

Application: Program that asks for user's birth date that features input validation
             and rejects non-digits, non-negative integers, decimals, and empty answers

Completed: Module 8

How to use: Simply run the code and enter your answer when prompted

----------------------------------------------------------------------------------------------------------------------

Module 9:
In ATMSim.cpp program, I could incorporate an AI-powered activity monitor

What the feature would do: AI would detect and flag suspicious activity such as:
- Excessive spending or withdrawals within short amount of time
- Sudden transfers to unusual accounts

What data it would need:
-transactions.txt holds current account's activity logs; modified with to add current date and time
- PIN is not sent, only current account's transactions

What the user would see:
- New menu option labeled "Suspicious Activity"
- AI would analyze previous activity and judge based on user's normal pattern and explains why it's unusual
    - Example: User normally withdraws amounts under $100 or occasionally withdraws a large amount
- If nothing unusual happened it would say: "No suspicious activity found"
- If there was three large withdrawals within a short amount of time it would flag it as:
    - "Alert: 3 large withdrawals within 1 minute:
        - $400.00 - 2026-11-05 12:50:03
        - $400.00 - 2026-11-05 12:50:39
        - $400.00 - 2026-11-05 12:51:01
    - You never withdraw this amount. If this was not you, please contact your bank."
- If user normally sends transfers to account 1004, but then suddenly transfers large amount to 1005, would flag:
    - "Alert: Sudden transfer of $5000.00 to account 1005
    - You have never sent transfers to this account. If this was not you, please contact your bank."

Where it would fit in program:
- "class ActivityMonitor" reads last 50 lines of transactions.txt for current account, creates prompt, then calls API
- Change to ATM class by adding "case 7" in "sessionMenu()" which call "monitor.flagActivity(current->getNumber())" and prints result
- Since C++ does not feature built-in HTTP, use library such as libcurl to use HTTP and call API
- Only runs when user chooses the option and would say "Analyzing..."
- AI could have false positives, but task is to solely inform and advise, not take action
